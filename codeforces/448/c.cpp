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

const int INF = 2e9;
int h[5000], n;

//each base case only encountered once
//guaranteed all in range [l, r] are > x
int Eval (int l, int r, int x)
{
	if (l == r)
		return 1;
	else if (l > r)
		return 0;

	//get lowest
	vector<int> low;
	int mn = INF;
	for (int a = l;a <= r;a++)
	{
		if (h[a] == mn)
			low.push_back (a);
		else if (h[a] < mn)
		{
			low.clear ();
			mn = h[a];
			low.push_back (a);
		}
	}

	//only verts?
	if (mn - x >= r - l + 1)
		return r - l + 1;

	int rtrn = mn - x, last = l;
	for (int a = 0;a < low.size ();a++)
	{
		if (rtrn >= r - l + 1)
			return r - l + 1;
		rtrn += Eval (last, low[a] - 1, mn);
		last = low[a] + 1;
	}
	
	if (rtrn >= r - l + 1)
		return r - l + 1;
	rtrn += Eval (last, r, mn);
	return min (r - l + 1, rtrn);
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> h[a];

	cout << Eval (0, n - 1, 0) << "\n";

	return 0;
}