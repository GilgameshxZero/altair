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

const ll MOD = 1e9 + 7;
ll sp[5000][5000];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	string s;
	cin >> s;

	for (int a = 0; a < 5000; a++)
		sp[0][a] = 1;

	for (int a = 1; a < n; a++)
	{
		for (int b = 0; b < 5000; b++)
		{
			if (b > a)
			{
				sp[a][b] = sp[a][b - 1];
				continue;
			}

			if (b != 0)
				sp[a][b] = sp[a - b - 1][b - 1];
			else
				sp[a][b] = 0;

			if (a - b - 1 - b >= 0 && s.substr (a - b - 1 - b, b + 1) < s.substr (a - b, b + 1))
				sp[a][b] = sp[a - b - 1][b];

			if (b != 0)
				sp[a][b] = (sp[a][b] + sp[a][b - 1]) % MOD;
		}
	}

	cout << sp[n - 1][4999];

	return 0;
}