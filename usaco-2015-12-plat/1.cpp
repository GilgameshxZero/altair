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

typedef long long ll;

//HL & fenwick

int n, k, ans = 0;
vector< vector<int> > edge;
vector<int> par, //parent of node
	path_id, //the path node is on
	path_loc, //the position of the node on its path
	ssize, //subtree size
	lvl, //lvl (depth) of each node
	path_beg; //0th node of each path
vector< vector<int> > path; //fenwick trees for each path
int max_lvl = 0, dig = 0; //(binary digits in max_lvl) + 1; number of ancestor values to store
vector< vector<int> > ances; //store one more than needed just in case

//preprocess to find parents and subtree sizes
void PrepSP (int cur, int last)
{
	par[cur] = last;
	ssize[cur] = 1;

	for (int a = 0; a < edge[cur].size (); a++)
	{
		if (edge[cur][a] == last)
			continue;
		lvl[edge[cur][a]] = lvl[cur] + 1;
		PrepSP (edge[cur][a], cur);
		ssize[cur] += ssize[edge[cur][a]];
	}
}

void PrepHL (int cur, bool heavy) //current node in dfs and whether the edge to its parent is heavy
{
	for (int a = 0; a < edge[cur].size (); a++)
	{
		if (edge[cur][a] == par[cur])
			continue;
		if (2 * ssize[edge[cur][a]] > ssize[cur]) //child is heavy
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
	if (lvl[x] < lvl[y]) //keep lvl[x] >= lvl[y]
		swap (x, y);

	//find the ancestor of x at the same lvl as y
	for (int a = dig - 1; a >= 0; a--)
		if (lvl[x] - (1 << a) >= lvl[y])
			x = ances[x][a];

	if (x == y)
		return x;

	for (int a = dig - 1; a >= 0; a--)
		if (ances[x][a] != -1 && ances[x][a] != ances[y][a])
			x = ances[x][a], y = ances[y][a];

	return ances[x][0];
}

void FenAdd (vector<int>& fen, int k, int x)
{
	for (; x < fen.size (); x += (x & -x))
		fen[x] += k;
}

int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (; x > 0; x -= (x & -x))
		r += fen[x];
	return r;
}

//plant k patches along the path to root from x
void PlantToRoot (vector<int>& path_id, vector<int>& path_loc, vector< vector<int> >& path, vector<int>& path_beg, int k, int x)
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
	ios_base::sync_with_stdio (false);
	freopen ("maxflow.in", "r", stdin);
	freopen ("maxflow.out", "w", stdout);

	cin >> n >> k;

	edge.resize (n);
	par.resize (n);
	path_id.resize (n);
	path_loc.resize (n);
	lvl.resize (n);
	ssize.resize (n);

	for (int a = 1, b, c; a < n; a++)
	{
		cin >> b >> c;
		edge[b - 1].push_back (c - 1);
		edge[c - 1].push_back (b - 1);
	}

	PrepSP (0, -1);
	path_id[0] = 0;
	path_loc[0] = 1;
	path.push_back (vector<int> (2, 0));
	path_beg.push_back (-1);
	PrepHL (0, true);

	//calculate LCA sparse table
	for (int a = 0; a < n; a++)
		max_lvl = max (max_lvl, lvl[a]);
	for (; (max_lvl >> dig) > 0; dig++);

	ances = vector< vector<int> > (n, vector<int> (++dig));

	for (int a = 0; a < n; a++)
		ances[a][0] = par[a];
	for (int a = 1; a < dig; a++) //find all 2^a ancestors
	{
		for (int b = 0; b < n; b++)
		{
			if (ances[b][a - 1] == -1)
				ances[b][a] = -1;
			else
				ances[b][a] = ances[ances[b][a - 1]][a - 1];
		}
	}

	for (int a = 0, b, c, d; a < k; a++)
	{
		cin >> b >> c;
		b--;
		c--;
		PlantToRoot (path_id, path_loc, path, path_beg, 1, b);
		PlantToRoot (path_id, path_loc, path, path_beg, 1, c);

		d = LCA (b, c);
		PlantToRoot (path_id, path_loc, path, path_beg, -2, d);
		FenAdd (path[path_id[d]], 1, path_loc[d]);
		FenAdd (path[path_id[d]], -1, path_loc[d] + 1); //path_loc[d] may be out of range but FenAdd will just ignore
	}

	//get max milk
	for (int a = 0; a < n; a++)
	{
		ans = max (ans, FenSum (path[path_id[a]], path_loc[a]));
	}

	cout << ans << '\n';

	return 0;
}