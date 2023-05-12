/*
ID: yangchess1
PROG: schlnet
LANG: C++
*/
#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

stack<int> s;
vector<int> in[101], out[101];
int n, curind, curscc, indice[101], lowlink[101], scc[101], root[101];
bool instack[101];

void Flood (int x, int val)
{
	if (root[x] == val)
		return;

	root[x] = val;
	for (int a = 0;a < out[x].size ();a++)
		Flood (out[x][a], val);
}

void Tarjan (int x)
{
	indice[x] = curind;
	lowlink[x] = curind;
	s.push (x);
	instack[x] = true;
	curind++;

	for (int a = 0;a < out[x].size ();a++)
	{
		if (indice[out[x][a]] == 0)
		{
			Tarjan (out[x][a]);
			lowlink[x] = min (lowlink[x], lowlink[out[x][a]]);
		}
		else if (instack[out[x][a]])
			lowlink[x] = min (lowlink[x], lowlink[out[x][a]]);
	}

	if (lowlink[x] == indice[x])
	{
		int top;
		do
		{
			top = s.top ();
			s.pop ();
			instack[top] = false;
			scc[top] = curscc;
		} while (top != x);

		curscc++;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);
	std::freopen ("schlnet.in", "r", stdin);
	std::freopen ("schlnet.out", "w", stdout);

	cin >> n;
	for (int a = 1;a <= n;a++)
	{
		int b;
		cin >> b;
		for (;b != 0;cin >> b)
		{
			out[a].push_back (b);
			in[b].push_back (a);
		}
	}

	memset (indice, 0, sizeof (indice));
	memset (scc, 0, sizeof (scc));
	memset (instack, false, sizeof (instack));

	//Part 1.
	for (int a = 1;a <= n;a++)
		root[a] = a;

	for (int a = 1;a <= n;a++)
		for (int b = 0;b < out[a].size ();b++)
			Flood (out[a][b], root[a]);

	int ans1 = 0;
	for (int a = 1;a <= n;a++)
		ans1 += (root[a] == a);

	cout << ans1 << "\n";

	//Part 2. Find SCC.
	curind = curscc = 1;
	for (int a = 1;a <= n;a++)
		if (indice[a] == 0)
			Tarjan (a);

	if (curscc == 2)
	{
		cout << "0\n";
		return 0;
	}

	bool adj[101][101]; //Adjacency matrix for SCCs.
	memset (adj, 0, sizeof (adj));

	for (int a = 1;a <= n;a++)
		for (int b = 0;b < out[a].size ();b++)
			adj[scc[a]][scc[out[a][b]]] = true;

	int x = 0, y = 0; //Number of SCCs with indegree = 0, outdegree = 0.
	for (int a = 1;a < curscc;a++)
	{
		int c = 0, d = 0;
		for (int b = 1;b < curscc;b++)
		{
			if (a != b)
			{
				if (adj[b][a])
					c++;
				if (adj[a][b])
					d++;
			}
		}

		if (c == 0)
			x++;
		if (d == 0)
			y++;
	}

	cout << max (x, y) << "\n";

	return 0;
}