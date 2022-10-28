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

vector< vector<int> > edge;
vector<int> ind, lowlink;
stack<int> s;
bitset<400> instack;
int cind, n, m, cscc, reach[400];

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
			reach[cscc]++;
			instack[s.top ()] = false;
			s.pop ();
		}

		reach[cscc]++;
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

	cin >> n >> m;
	cind = cscc = 0;
	memset (reach, 0, sizeof (reach));
	lowlink.resize (n * m);
	ind.resize (n * m);
	edge.resize (n * m);
	instack.reset ();

	for (int a = 0;a < n * m;a++)
		ind[a] = lowlink[a] = -1;
	
	string temp;
	cin >> temp;
	for (int a = 0;a < n;a++)
	{
		if (temp[a] == '>')
			for (int b = a * m;b < a * m + m - 1;b++)
				edge[b].push_back (b + 1);
		else
			for (int b = a * m + m - 1;b > a * m;b--)
				edge[b].push_back (b - 1);
	}
	cin >> temp;
	for (int a = 0;a < m;a++)
	{
		if (temp[a] == 'v')
			for (int b = a;b < n * m - m;b += m)
				edge[b].push_back (b + m);
		else
			for (int b = a + m;b < n * m;b += m)
				edge[b].push_back (b - m);
	}

	Tarjan (0);
	if (reach[0] == n * m)
		cout << "YES";
	else
		cout << "NO";

	return 0;
}