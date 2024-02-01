/*
Here edge can contain all edges of the bipartite graph, as long as each node has distinct ID. Match will only mark matches from one set of the bipartite graph.
*/
#include <bitset>
#include <vector>

using namespace std;

bool Augment (bitset<250>& vis, vector< vector<int> >& edge, vector<int>& match, int x)
{
	for (int a = 0;a < edge[x].size ();a++)
	{
		if (!vis[edge[x][a]])
		{
			vis[edge[x][a]] = true;
			if (match[edge[x][a]] == -1 || Augment (vis, edge, match, match[edge[x][a]]))
			{
				match[edge[x][a]] = x;
				return true;
			}
		}
	}

	return false;
}

int main ()
{
	int n, m;
	vector< vector<int> > edge;

	//Initialize edge and n. m should be the size of one set of the graph

	vector<int> match;
	bitset<250> vis;
	int ans = 0;
	match.resize (n, -1);
	for (int a = 0;a < m;a++)
	{
		vis.reset ();
		ans += Augment (vis, edge, match, id[a]); //id[a] will represent the id of the `a`th node in set m
	}
}