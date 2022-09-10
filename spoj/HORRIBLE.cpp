#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
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

void FenAdd (vector<ll> &fen, int ind, ll k)
{
	for (;ind < fen.size ();ind += (ind & -ind))
		fen[ind] += k;
}

ll FenSum (vector<ll> &fen, int ind)
{
	ll r = 0;
	for (;ind > 0;ind -= (ind & -ind))
		r += fen[ind];
	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int T;
	cin >> T;

	for (int a = 0;a < T;a++)
	{
		int N, C;
		cin >> N >> C;
		vector<ll> fen1 (100002, 0), fen2 (100002, 0);

		for (int b = 0;b < C;b++)
		{
			int c;
			cin >> c;

			if (c == 0)
			{
				ll d, e, f;
				cin >> d >> e >> f;
				FenAdd (fen1, d, f);
				FenAdd (fen1, e + 1, -f);
				FenAdd (fen2, d, f * (d - 1));
				FenAdd (fen2, e + 1, -f * e);
			}
			else
			{
				ll d, e;
				cin >> d >> e;
				cout << FenSum (fen1, e) * e - FenSum (fen2, e) - (FenSum (fen1, d - 1) * (d - 1) - FenSum (fen2, d - 1)) << "\n";
			}
		}
	}

	return 0;
}