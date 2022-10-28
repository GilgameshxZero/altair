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

int n, kit[100000][2], away[100000], cnt[100000];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input1.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	scanf ("%i", &n);
	memset (cnt, 0, sizeof (cnt));
	for (int a = 0;a < n;a++)
	{
		scanf ("%i%i", &kit[a][0], &kit[a][1]);
		cnt[kit[a][0]]++;
	}

	for (int a = 0;a < n;a++)
		printf ("%i %i\n", n - 1 + cnt[kit[a][1]], n - 1 - cnt[kit[a][1]]);

	return 0;
}