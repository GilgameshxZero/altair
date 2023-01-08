/*
Preps a tree with N nodes for LCA queries. Preprocessing takes NlogN time, and each query will take logN time.
It is assumed the root is at node 0.
*/
#include <vector>

using namespace std;

int n;
int max_lvl = 0, dig = 0; //(binary digits in max_lvl) + 1; number of ancestor values to store
vector< vector<int> > edge;
vector< vector<int> > ances; //store one more than needed just in case
vector<int> lvl; //lvl (depth) of each node
vector<int> par; //parent of node

//preprocess to find depths and parents
void PrepSP (int cur, int last)
{
	par[cur] = last;

	for (int a = 0;a < edge[cur].size ();a++)
	{
		if (edge[cur][a] == last)
			continue;
		lvl[edge[cur][a]] = lvl[cur] + 1;
		PrepSP (edge[cur][a], cur);
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

int main ()
{
	PrepSP (0, -1);

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

	//Use LCA any way you want beyond this point.

	return 0;
}