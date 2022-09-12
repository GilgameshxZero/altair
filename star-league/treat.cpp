//Solution by Yang Yan
//DFS
#include <iostream>
#include <cstdio>
#include <vector>
#include <bitset>

using namespace std;

void FindCycle (vector<int>& next, vector<int>& dist, bitset<100000>& vis, bitset<100000>& instack, int cur)
{
	if (vis[cur])
	{
		if (instack[cur]) //this is on the current DFS stack, so calculate cycles
		{
			//first find the length of the cycle
			int k = next[cur];
			dist[cur] = 1;
			while (k != cur)
				k = next[k],
				dist[cur]++;

			//then update all nods in cycle with this len
			k = next[cur];
			while (k != cur)
				dist[k] = dist[cur],
				k = next[k];

			return;
		}
		else //from another DFS stack, break out
			return;
	}

	vis[cur] = true;
	instack[cur] = true;
	FindCycle (next, dist, vis, instack, next[cur]);
}

void FindAns (vector<int>& next, vector<int>& dist, int cur)
{
	if (dist[cur] != 0)
		return;

	FindAns (next, dist, next[cur]);
	dist[cur] = dist[next[cur]] + 1;
}

int main ()
{
	freopen ("treat.in", "r", stdin);
	freopen ("treat.out", "w", stdout);

	int n;
	cin >> n;

	vector<int> next (n);
	vector< vector<int> > back (n);
	for (int a = 0;a < n;a++)
	{
		cin >> next[a];
		back[--next[a]].push_back (a);
	}

	//DFS for cycles
	bitset<100000> vis, instack;
	vector<int> dist (n, 0);
	vis.reset ();
	for (int a = 0;a < n;a++)
		instack.reset (),
		FindCycle (next, dist, vis, instack, a);

	//DFS from every node until we hit a known distance
	for (int a = 0;a < n;a++)
		FindAns (next, dist, a),
		cout << dist[a] << "\n";

	return 0;
}