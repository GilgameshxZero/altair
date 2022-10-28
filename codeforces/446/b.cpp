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

int mat[1000][1000];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, m, k, p;
	cin >> n >> m >> k >> p;
	for (int a = 0;a < n;a++)
		for (int b = 0;b < m;b++)
			cin >> mat[a][b];

	priority_queue<long long> pqr, pqc;

	//start with all on row, then move to all on col
	for (int a = 0;a < n;a++)
	{
		long long sum = 0;
		for (int b = 0;b < m;b++)
			sum += mat[a][b];
		pqr.push (sum);
	}
	for (int a = 0;a < m;a++)
	{
		long long sum = 0;
		for (int b = 0;b < n;b++)
			sum += mat[b][a];
		pqc.push (sum);
	}

	long long ans, tot = 0, t2 = 0;
	stack<long long> rs;
	for (int a = 0;a < k;a++)
	{
		rs.push (pqr.top ());
		tot += pqr.top ();
		pqr.push (pqr.top () - m * p);
		pqr.pop ();
	}

	//loop through 0-k for distribution
	ans = tot;
	for (int a = 1;a <= k;a++)
	{
		tot -= rs.top ();
		rs.pop ();
		t2 += pqc.top ();
		pqc.push (pqc.top () - n * p);
		pqc.pop ();
		ans = max (ans, tot + t2 - (long long)(k - a) * a * p);
	}

	cout << ans;

	return 0;
}