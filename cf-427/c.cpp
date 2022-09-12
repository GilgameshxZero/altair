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
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

//tarjans to find scc. for each scc min cost of node and the # of the min cost node
int n, cscc, cind, cost[100000], ind[100000], lowlink[100000], mincost[100000], nummin[100000];
bool instack[100000];
vector<int> edge[100000];
stack<int> s;

void Tarjan (int x)
{
	ind[x] = cind++; //first time visit
	lowlink[x] = ind[x];
	s.push (x); //so we can find sccs effectively
	instack[x] = true;

	//see if any children have links backward. if unvisited, visit. if on the current stack, then eval lowlink; if not, then ignore, because it belongs to another scc.
	for (int a = 0;a < edge[x].size ();a++)
	{
		if (ind[edge[x][a]] == -1)
		{
			Tarjan (edge[x][a]);
			lowlink[x] = min (lowlink[x], lowlink[edge[x][a]]);
		}
		else if (instack[edge[x][a]])
			lowlink[x] = min (lowlink[x], lowlink[edge[x][a]]);
	}

	if (lowlink[x] == ind[x]) //we cant go farther back, so this is the conclusion of an scc. pop off stack until we reach x to get scc
	{
		while (s.top () != x)
		{
			if (cost[s.top ()] < mincost[cscc])
			{
				mincost[cscc] = cost[s.top ()];
				nummin[cscc] = 1;
			}
			else if (cost[s.top ()] == mincost[cscc])
				nummin[cscc]++;

			instack[s.top ()] = false;
			s.pop ();
		}

		if (cost[s.top ()] < mincost[cscc])
		{
			mincost[cscc] = cost[s.top ()];
			nummin[cscc] = 1;
		}
		else if (cost[s.top ()] == mincost[cscc])
			nummin[cscc]++;

		s.pop ();
		instack[x] = false;
		cscc++;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> cost[a];
	int x;
	cin >> x;
	for (int a = 0, b, c;a < x;a++)
	{
		cin >> b >> c;
		edge[b - 1].push_back (c - 1);
	}

	for (int a = 0;a < n;a++)
		mincost[a] = 1e9 + 1;

	memset (ind, -1, sizeof (ind));
	for (int a = 0;a < n;a++)
		if (ind[a] == -1)
			Tarjan (a);

	long long ans1 = 0;
	for (int a = 0;a < cscc;a++)
		ans1 += mincost[a];

	long long ans2 = 1;
	for (int a = 0;a < cscc;a++)
		ans2 = (ans2 * nummin[a]) % (1000000007);

	cout << ans1 << " " << ans2 << "\n";

	return 0;
}