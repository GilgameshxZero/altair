#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string cur, fin, zip[51];
bool visit[51];
int ac, t, n, m;

struct Node
{
	vector<pair<string, int>> next;
};

Node node[51];

string DFS (int s)
{
	if (visit[s] == true)
		return "";

	visit[s] = true;
	fin += zip[s];

	//Add all neighbors to list.
	if (s != 0)
	{
		for (int a = 0;a < node[s].next.size ();a++)
		{
			node[0].next.push_back (make_pair (zip[node[s].next[a].second], node[s].next[a].second));
		}

		sort (node[0].next.begin (), node[0].next.end ());
	}

	//Choose smallest neighbor.
	while (node[0].next.size () != 0)
	{
		int p = node[0].next[0].second;
		node[0].next.erase (node[0].next.begin ());
		DFS (p);
	}

	return "";
}

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	ac = 0;
	zip[0] = "";
	cin >> t;

	for (int x = 0;x < t;x++)
	{
		cin >> n >> m;
		cur = "";
		fin = "";

		for (int a = 0;a < 51;a++)
		{
			node[a].next.clear ();
			visit[a] = false;
		}

		for (int a = 1;a <= n;a++)
			cin >> zip[a];

		for (int a = 0, b, c;a < m;a++)
		{
			cin >> b >> c;
			node[b].next.push_back (make_pair (zip[c], c));
			node[c].next.push_back (make_pair (zip[b], b));
		}

		for (int a = 1;a <= n;a++)
			node[0].next.push_back (make_pair (zip[a], a));

		sort (node[0].next.begin (), node[0].next.end ());

		DFS (0);
		cout << "Case #" << x + 1 << ": " << fin << "\n";
	}

	return 0;
}