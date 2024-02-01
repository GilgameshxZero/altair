/*
Decomposes the tree with N nodes into disjoint paths. Light paths are on their own, and heavy chains are joined in one path. Each path is represented by a fenwick tree in this implementation, which can and should be adapted to use.
It is assumed the root is at node 0.
*/
#include <vector>

using namespace std;

int n;
vector< vector<int> > edge;
vector<int> par, //parent of node
	path_id, //the path node is on
	path_loc, //the position of the node on its path
	size, //subtree size
	path_beg; //0th node of each path
vector< vector<int> > path; //fenwick trees for each path

//preprocess to find parents and subtree sizes
void PrepSP (int cur, int last)
{
	par[cur] = last;
	size[cur] = 1;

	for (int a = 0;a < edge[cur].size ();a++)
	{
		if (edge[cur][a] == last)
			continue;
		PrepSP (edge[cur][a], cur);
		size[cur] += size[edge[cur][a]];
	}
}

//preprocess for heavy-light
void PrepHL (int cur, bool heavy) //current node in dfs and whether the edge to its parent is heavy
{
	for (int a = 0;a < edge[cur].size ();a++)
	{
		if (edge[cur][a] == par[cur])
			continue;
		if (2 * size[edge[cur][a]] > size[cur]) //child is heavy
		{
			if (heavy) //extend current path
			{
				path_id[edge[cur][a]] = path_id[cur];
				path_loc[edge[cur][a]] = path_loc[cur] + 1;
				path[path_id[cur]].push_back (0);
				PrepHL (edge[cur][a], true);
			}
			else //create new path
			{
				path_id[edge[cur][a]] = path.size ();
				path_loc[edge[cur][a]] = 1;
				path.push_back (vector<int> (2, 0));
				path_beg.push_back (cur);
				PrepHL (edge[cur][a], true);
			}
		}
		else //light, create new path
		{
			path_id[edge[cur][a]] = path.size ();
			path_loc[edge[cur][a]] = 1;
			path.push_back (vector<int> (2, 0));
			path_beg.push_back (cur);
			PrepHL (edge[cur][a], false);
		}
	}
}

int main ()
{
	PrepSP (0, -1);
	path_id[0] = 0; //root node is located on a path, but it officially has no position in the fenwick tree (since 0 is ignored)
	path_loc[0] = 0;
	path.push_back (vector<int> (1, 0));
	path_beg.push_back (-1);
	PrepHL (0, true);

	return 0;
}