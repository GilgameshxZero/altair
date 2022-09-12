#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <bitset>
#include <queue>
using namespace std;

struct Match
{
	int id[2], score[2];
};

int GetInt (string &s, int spos, int &rtrn) //spos = start parsing pos
{
	while (s[spos] != ',' && spos < s.length ())
	{
		rtrn = rtrn * 10 + s[spos] - '0';
		spos++;
	}

	return spos + 1;
}

bool Close (double a, double b)
{
	const static double EPS = 1e-7;
	return abs (a - b) < EPS;
}

void GetChild (vector< vector<int> > &graph, bitset<20> &list, int start) //DFS on graph with no cycle
{
	for (int a = 0;a < 20;a++)
		if (graph[start][a] == 1 && list[a] != true)
			list[a] = true,
			GetChild (graph, list, a);
}

void GetPar (vector< vector<int> > &graph, bitset<20> &list, int start) //DFS on graph with no cycle, in reverse dir
{
	for (int a = 0;a < 20;a++)
		if (graph[a][start] == 1 && list[a] != true)
			list[a] = true,
			GetPar (graph, list, a);
}

int main ()
{
	string dir, t;
	cout << "Place the results file in the current directory.\nMake sure team IDs are within [0, 19].\nEnter its name (w/ file extension): ";
	cin >> dir;

	ifstream in;
	ofstream out;
	in.open (dir);

	vector<Match> match;
	vector< pair<int, int> > wintot (20); //(2 * games won + games tied, 2 * games played) for each team
	vector<int> totscore (20); //total score for each team
	int cmatch = 0, curpos;

	while (true)
	{
		getline (in, t, '\n');
		if (t.length () < 5) //length too small, end of file
			break;
		match.push_back (Match ());
		curpos = 0;
		curpos = GetInt (t, curpos, match[cmatch].id[0]); //assume IDs are from 0-19
		curpos = GetInt (t, curpos, match[cmatch].id[1]);
		curpos = GetInt (t, curpos, match[cmatch].score[0]);
		curpos = GetInt (t, curpos, match[cmatch].score[1]);

		wintot[match[cmatch].id[0]].second += 2;
		wintot[match[cmatch].id[1]].second += 2;
		if (match[cmatch].score[1] > match[cmatch].score[0])
			wintot[match[cmatch].id[1]].first += 2;
		else if (match[cmatch].score[1] < match[cmatch].score[0])
			wintot[match[cmatch].id[0]].first += 2;
		else //tie
			wintot[match[cmatch].id[0]].first += 1,
			wintot[match[cmatch].id[1]].first += 1;

		totscore[match[cmatch].id[0]] += match[cmatch].score[0];
		totscore[match[cmatch].id[1]] += match[cmatch].score[1];

		cmatch++;
	}

	vector< pair<double, int> > best[2]; //best & worst teams by both criterions
	for (int a = 0;a < 20;a++)
	{
		if (wintot[a].second == 0)
			continue;

		best[0].push_back (make_pair ((double)wintot[a].first / wintot[a].second, a));
		best[1].push_back (make_pair ((double)totscore[a] / wintot[a].second, a));
	}

	sort (best[0].begin (), best[0].end ());
	sort (best[1].begin (), best[1].end ());
	cout << "\nPreliminary results:";

	for (int k = 0;k < 2;k++)
	{
		cout << "\nCriterion " << k + 1 << " ";
		if (k == 0)
			cout << "(wins per game)";
		else
			cout << "(points per game)";
		cout << " List of teams from best to worst:\n";

		for (int a = best[k].size () - 1;a >= 0;a--)
			cout << best[k][a].second + 1 << " ";
	}

	cout << "\n\nCriterion 3 (every edge in graph is a game, and they are added one by one, with the more dominant wins added in first, to create a topological graph to find best and worst teams)\nList of teams from best to worst:";

	vector< pair<double, pair<int, int> > > edge;
	for (int a = 0, b = 0;a < match.size ();a++)
	{
		edge.push_back (pair<double, pair<int, int> > ());
		edge[b].first = (double)max (match[a].score[0], match[a].score[1]) / (match[a].score[0] + match[a].score[1]);
		if (match[a].score[0] > match[a].score[1])
			edge[b].second = make_pair (match[a].id[0], match[a].id[1]);
		else if (match[a].score[0] < match[a].score[1])
			edge[b].second = make_pair (match[a].id[1], match[a].id[0]);
		else //disregard ties
			edge.pop_back (), b--;
		b++;
	}

	sort (edge.begin (), edge.end ()); //from least dominant to most dominant edges

	vector< vector<int> > graph (20, vector<int>(20, 0)); //0 means undecided edge, 1 means forward edge, 2 means backward edge
	bitset<20> ch, par;
	bool flag;

	for (int a = edge.size () - 1;a >= 0;a--) //add edges in as long as they don't conflict previous edges
	{
		if (graph[edge[a].second.first][edge[a].second.second] != 0)
			continue; //if an edge exists then we don't have to consider adding this one

		graph[edge[a].second.first][edge[a].second.second] = 1;
		graph[edge[a].second.second][edge[a].second.first] = 2;
		ch.reset ();
		GetChild (graph, ch, edge[a].second.first);
		par.reset ();
		GetPar (graph, par, edge[a].second.second);

		//if any child has a forward edge to a par, then addition of current edge is invalid. otherwise, add edges between all parents and all children
		flag = false;
		for (int b = 0;b < 20;b++)
		{
			if (ch[b] == false)
				continue;
			for (int c = 0;c < 20;c++)
			{
				if (par[c] == false)
					continue;
				if (graph[b][c] == 1)
				{
					flag = true;
					break;
				}
			}

			if (flag)
				break;
		}

		if (flag)
			continue;

		//connect all pars to children
		for (int b = 0;b < 20;b++)
		{
			if (ch[b] == false)
				continue;
			for (int c = 0;c < 20;c++)
			{
				if (par[c] == false)
					continue;
				graph[c][b] = 1;
				graph[b][c] = 2;
			}
		}
	}

	vector<int> topoq; //queue and answer of topological sort
	int qpos = 0;

	vector<int> cedge (20); //count of how many edges lead out
	for (int a = 0;a < 20;a++)
	{
		for (int b = 0;b < 20;b++)
			if (graph[a][b] == 1)
				cedge[a]++;
	}

	for (int a = 0;a < 20;a++)
	{
		if (cedge[a] == 0) //0 edges coming out, worst team
			topoq.push_back (a);
	}

	for (;qpos < 20;qpos++)
	{
		//remove all edges leading into topoq[qpos] and add new 0's to topoq
		for (int a = 0;a < 20;a++)
		{
			if (graph[a][topoq[qpos]])
			{
				graph[a][topoq[qpos]] = 0;
				cedge[a]--;
				if (cedge[a] == 0)
					topoq.push_back (a);
			}
		}
	}

	cout << "\n";
	for (int a = 19;a >= 0;a--)
	{
		if (wintot[topoq[a]].second == 0) //if they haven't played a game don't list them here
			continue;
		cout << topoq[a] + 1 << " ";
	}

	cout << "\n\nPress enter to exit...";
	cin.ignore (100, '\n');
	cin.get ();

	return 0;
}