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

vector<ll> bales;

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("haybales.in", "r", stdin);
	std::freopen ("haybales.out", "w", stdout);

	int n, q;
	cin >> n >> q;

	bales.resize (n);
	for (int a = 0; a < n; a++)
		cin >> bales[a];

	ll d, ans;
	string s;
	for (int a = 0, b, c; a < q; a++)
	{
		cin >> s;

		if (s == "M")
		{
			cin >> b >> c;
			ans = 1e18;
			for (int x = b - 1; x < c; x++)
				ans = min (ans, bales[x]);
			cout << ans << '\n';
		}
		else if (s == "P")
		{
			cin >> b >> c >> d;
			for (int x = b - 1; x < c; x++)
				bales[x] += d;
		}
		else if (s == "S")
		{
			cin >> b >> c;
			ans = 0;
			for (int x = b - 1; x < c; x++)
				ans += bales[x];
			cout << ans << '\n';
		}
	}

	return 0;
}