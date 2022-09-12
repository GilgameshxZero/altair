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
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

unsigned long long n, m, sr[100001], pres[100001], prea[100001];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input1.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	prea[0] = pres[0] = 0;
	for (int a = 1;a <= n;a++)
	{
		cin >> sr[a];
		prea[a] = prea[a - 1] + sr[a];
	}

	sort (sr + 1, sr + n + 1);
	for (int a = 1;a <= n;a++)
		pres[a] = pres[a - 1] + sr[a];

	cin >> m;
	for (int a = 0, b, c, d;a < m;a++)
	{
		cin >> b >> c >> d;
		if (b == 1) cout << prea[d] - prea[c - 1] << "\n";
		if (b == 2) cout << pres[d] - pres[c - 1] << "\n";
	}

	return 0;
}