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

ll CntInv (vector<int>& xr, int f, int l) //inclusive
{
	if (f == l)
		return 0;
	else
	{
		int mid = (f + l) / 2;
		ll r = CntInv (xr, f, mid);
		r += CntInv (xr, mid + 1, l);
		vector<int> copy;
		copy.resize (l - f + 1);

		for (int a = 0, b = 0, c = 0;a < copy.size ();a++)
		{
			if (f + b <= mid && (c + mid + 1 > l || xr[f + b] < xr[c + mid + 1]))
				copy[a] = xr[b++ + f];
			else
				copy[a] = xr[c++ + mid + 1],
				r += mid - f + 1 - b;
		}

		for (int a = f;a <= l;a++)
			xr[a] = copy[a - f];

		return r;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin); freopen ("output.txt", "w", stdout);

	int n, q;
	vector<int> x;

	cin >> n >> q;
	x.resize (n);
	for (int a = 0;a < n;a++)
		cin >> x[a];

	//Count inversions
	ll inv = CntInv (x, 0, n - 1);
	inv &= 1;

	for (int a = 0;a < q;a++)
		inv ^= 1,
		cout << inv << "\n";

	return 0;
}