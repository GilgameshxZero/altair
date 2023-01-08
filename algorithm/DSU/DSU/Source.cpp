/*	DSU (Disjoint-Set Union)/Union-Find: group nodes and determine if two nodes are in the same group.
	Optimization 1: Path Compression.
	Optimization 2: Union by Rank (size of group is stored as negative of root's "parent").
*/
#include <iostream>
#include <string>
using namespace std;

const int MAXN = 100000;
int par[MAXN];

int Find (int x)
{
	if (par[x] < 0) return x;
	return par[x] = Find (par[x]);
}

void Union (int x, int y)
{
	int i = Find (x), j = Find (y);

	if (i == j) return;
	if (-par[i] >= -par[j])
		par[i] += par[j],
		par[j] = i;
	else
		par[j] += par[i],
		par[i] = j;
}

int main ()
{
	int x, y;
	string command;
	cout << "MAXN: " << MAXN << "\n"
		<< "Commands: union, find, size, par\n\n";

	for (int a = 0;a < MAXN;a++)
		par[a] = -1;

	cin >> command;
	
	while (command != "exit")
	{
		if (command == "union")
			cin >> x >> y,
			Union (x, y);
		else if (command == "find")
			cin >> x,
			cout << Find (x) << "\n";
		else if (command == "size")
			cin >> x,
			cout << -par[Find (x)] << "\n";
		else if (command == "par")
			cin >> x,
			cout << par[x] << "\n";
		cin >> command;
	}

	return 0;
}