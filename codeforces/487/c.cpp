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

int n;
int POW (int a, int b)
{
	if (b == 0)
		return 1;
	if (b % 2 == 0)
	{
		int k = POW (a, b / 2);
		return ((long long)k * k) % n;
	}
	else
	{
		int k = POW (a, b / 2);
		return ((long long)k * k * a) % n;
	}
}

int Inv (int x)
{
	return POW (x, n - 2);
}

	bool taken[100005];
int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;

	if (n == 1)
	{
		cout << "YES\n1";
		return 0;
	}
	//prime
	for (int a = 2;a < n;a++)
		if (n % a == 0)
		{
			cout << "NO";
			return 0;
		}

	cout << "YES\n1\n";
	vector< pair<int, int> > x;
	for (int a = 2;a < n - 1;a++)
		if (!taken[a])
			x.push_back (make_pair (a, Inv (a))),
			taken[Inv(a)] = true;

	int mul = 1;
	for (int a = 0;a < x.size ();a++)
	{
		if ((long long)mul * x[a].first % n == n - 1)
			swap (x[a].first, x[a].second);
		mul *= x[a].first;
	}

	for (int a = 0;a < x.size ();a++)
		cout << x[a].first << "\n";
	cout << n - 1 << "\n";
	for (int a = x.size () - 1;a >= 0;a--)
		cout << x[a].second << "\n";
	cout << n;

	return 0;
}