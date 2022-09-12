#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Query
{
	char type;
	int p1, p2; //parameters

	Query (char t, int a, int b)
	{
		type = t;
		p1 = a;
		p2 = b;
	}
};

struct Node
{
	int par, //index of parent node, may be -1
		num, //number on edge to parent
		dep; //depth of node

	Node (int p, int n, int d)
	{
		par = p;
		num = n;
		dep = d;
	}
};

int LCA (const vector< vector<int> >& anc, const vector<Node>& tree, int x, int y)
{
	//make x and y the same depth first
	if (tree[x].dep < tree[y].dep)
		swap (x, y);

	for (int a = anc[x].size () - 1;a >= 0;a--)
		if (tree[anc[x][a]].dep >= tree[y].dep)
			x = anc[x][a];

	if (x == y)
		return x;

	//binary search for LCA
	for (int a = anc[x].size () - 1;a >= 0;a--)
		if (anc[x][a] != anc[y][a])
			x = anc[x][a],
			y = anc[y][a];

	return tree[x].par;
}

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n;
	cin >> n;

	//process all commands before queries
	vector<Node> tree (1, Node (0, -1, 0)); //parent is itself to faciliate LCA
	vector<int> ref (n + 1); //the node each stack points to
	ref[0] = 0;
	vector<Query> q;
	for (int a = 0, b, c;a < n;a++)
	{
		char x;
		cin >> x;
		if (x == 'a')
		{
			cin >> b;
			tree.push_back (Node (ref[b], a + 1, tree[ref[b]].dep + 1));
			ref[a + 1] = tree.size () - 1;
		}
		else if (x == 'b')
		{
			cin >> b;
			q.push_back (Query ('b', b, -1)); //save to be evaluated later
			ref[a + 1] = tree[ref[b]].par;
		}
		else //x == 'c'
		{
			cin >> b >> c;
			q.push_back (Query ('c', b, c));
			ref[a + 1] = ref[b];
		}
	}

	//precalculate LCA arrays
	vector< vector<int> > anc (tree.size (), vector<int>(20)); //calculate up to the 2^19th ancestor of each node
	for (int a = 0;a < tree.size ();a++)
		anc[a][0] = tree[a].par;
	for (int a = 1;a < 20;a++)
		for (int b = 0;b < tree.size ();b++)
			anc[b][a] = anc[anc[b][a - 1]][a - 1];

	//process queries
	for (int a = 0;a < q.size ();a++)
	{
		if (q[a].type == 'b')
			cout << tree[ref[q[a].p1]].num << "\n";
		else //q[a].type == 'c'
			cout << tree[LCA (anc, tree, ref[q[a].p1], ref[q[a].p2])].dep << "\n";
	}

	return 0;
}