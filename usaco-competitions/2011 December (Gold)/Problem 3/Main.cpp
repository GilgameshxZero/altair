/*
Heavy-light decomp the tree into distinct paths. Augment each path (heavy and light) with a differential fenwick tree.
Use LCA sparse array to add patches of grass.
*/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector< vector<int> > edge;
vector<int> par, //parent of node
	path_id, //the path node is on
	path_loc, //the position of the node on its path
	size, //subtree size
	lvl, //lvl (depth) of each node
	path_beg; //0th node of each path
vector< vector<int> > path; //fenwick trees for each path
int max_lvl = 0, dig = 0; //(binary digits in max_lvl) + 1; number of ancestor values to store
vector< vector<int> > ances; //store one more than needed just in case

//preprocess to find parents and subtree sizes
void PrepSP (int cur, int last)
{
	par[cur] = last;
	size[cur] = 1;

	for (int a = 0;a < edge[cur].size ();a++)
	{
		if (edge[cur][a] == last)
			continue;
		lvl[edge[cur][a]] = lvl[cur] + 1;
		PrepSP (edge[cur][a], cur);
		size[cur] += size[edge[cur][a]];
	}
}

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

int LCA (int x, int y)
{
	if (lvl[x] < lvl[y]) //keep lvl[x] <= lvl[y]
		swap (x, y);

	//find the ancestor of x at the same lvl as y
	for (int a = dig - 1;a >= 0;a--)
		if (lvl[x] - (1 << a) >= lvl[y])
			x = ances[x][a];

	if (x == y)
		return x;

	for (int a = dig - 1;a >= 0;a--)
		if (ances[x][a] != -1 && ances[x][a] != ances[y][a])
			x = ances[x][a], y = ances[y][a];

	return ances[x][0];
}

void FenAdd (vector<int>& fen, int k, int x)
{
	for (;x < fen.size ();x += (x & -x))
		fen[x] += k;
}

int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (;x > 0;x -= (x & -x))
		r += fen[x];
	return r;
}

//plant k patches along the path to root from x
void PlantToRoot (vector<int>& path_id, vector<int>& path_loc, vector< vector<int> >& path, vector<int>& path_beg, 
				  int k, int x)
{
	while (x != -1)
	{
		FenAdd (path[path_id[x]], k, 1);
		FenAdd (path[path_id[x]], -k, path_loc[x] + 1); //path_loc[x] may be out of range but FenAdd will just ignore
		x = path_beg[path_id[x]];
	}
}

int main ()
{
	freopen ("grassplant.in", "r", stdin);
	freopen ("grassplant.out", "w", stdout);

	cin >> n >> m;

	edge.resize (n);
	par.resize (n);
	path_id.resize (n);
	path_loc.resize (n);
	lvl.resize (n);
	size.resize (n);

	for (int a = 1, b, c;a < n;a++)
	{
		cin >> b >> c;
		edge[b - 1].push_back (c - 1);
		edge[c - 1].push_back (b - 1);
	}

	PrepSP (0, -1);
	path_id[0] = 0; //root node is located on a path, but it officially has no position in the fenwick tree (since 0 is ignored)
	path_loc[0] = 0;
	path.push_back (vector<int> (1, 0));
	path_beg.push_back (-1);
	PrepHL (0, true);

	//calculate LCA sparse table
	for (int a = 0;a < n;a++)
		max_lvl = max (max_lvl, lvl[a]);
	for (;(max_lvl >> dig) > 0;dig++);

	ances = vector< vector<int> > (n, vector<int> (++dig));

	for (int a = 0;a < n;a++)
		ances[a][0] = par[a];
	for (int a = 1;a < dig;a++) //find all 2^a ancestors
	{
		for (int b = 0;b < n;b++)
		{
			if (ances[b][a - 1] == -1)
				ances[b][a] = -1;
			else
				ances[b][a] = ances[ances[b][a - 1]][a - 1];
		}
	}
	
	for (int a = 0, b, c;a < m;a++)
	{
		char x;
		cin >> x >> b >> c;
		b--;
		c--;
		if (x == 'P')
		{
			//plant 1 grass from b to root, 1 from c to root, then -2 from lca (b, c) to root
			PlantToRoot (path_id, path_loc, path, path_beg, 1, b);
			PlantToRoot (path_id, path_loc, path, path_beg, 1, c);
			PlantToRoot (path_id, path_loc, path, path_beg, -2, LCA (b, c));
		}
		else //query
		{
			//make `b` the child (if it isn't already)
			if (par[c] == b)
				swap (b, c);

			//sum all previous fenwick entrees on b's path up to b
			cout << FenSum (path[path_id[b]], path_loc[b]) << "\n";
		}
	}

	return 0;
}