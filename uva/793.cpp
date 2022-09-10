#define _CRT_SECURE_NO_WARNINGS

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

vector<int> par;

int Find (int i)
{
	if (par[i] < 0)
		return i;
	else
		return par[i] = Find (par[i]);
}

void Union (int i, int j)
{
	int x = Find (i), y = Find (j);
	if (x == y)
		return;
	else
	{
		if (-par[x] >= -par[y])
			par[y] = x,
			par[x] = par[x] + par[y];
		else
			par[x] = y,
			par[y] = par[x] + par[y];
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int t;
	cin >> t;

	for (int a = 0;a < t;a++)
	{
		if (a != 0)
			cout << "\n";

		int x, y;
		x = y = 0;

		int n;
		cin >> n;

		string s;
		getline (cin, s);
		par.clear ();
		par.resize (n, -1);

		while (true)
		{
			s = "";
			getline (cin, s);
			if (s.length () < 3)
				break;

			stringstream ss;
			ss << s;

			char c;
			ss >> c;
			int i, j;
			ss >> i >> j;
			i--;
			j--;

			if (c == 'c')
				Union (i, j);
			else
			{
				bool k = (Find (i) == Find (j));
				x += k;
				y += !k;
			}
		}

		cout << x << "," << y << "\n";
	}

	return 0;
}