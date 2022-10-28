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

int n, x, fen[200002], h[100001];

void Add (int pos, int x)
{
	pos += 100001;
	for (;pos < 200002;pos += pos & -pos)
		fen[pos] += x;
}

int Get (int pos)
{
	int r = 0;
	pos += 100001;
	for (;pos > 0;pos -= pos & -pos)
		r += fen[pos];
	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	/*std::freopen ("file_name.in", "r", stdin);
	std::freopen ("file_name.out", "w", stdout);*/
	std::ifstream in ("median.in");
	std::ofstream out ("median.out");

	memset (fen, 0, sizeof (fen));
	in >> n >> x;

	int t;
	Add (0, 1);
	h[0] = 0;
	for (int a = 0;a < n;a++)
	{
		in >> t;
		h[a + 1] = h[a] + (t >= x) * 2 - 1;
		Add (h[a + 1], 1);
	}

	long long ans = 0;
	for (int a = 0;a < n;a++)
	{
		ans += n - a - Get (h[a] - 1);
		Add (h[a], -1);
	}

	out << ans << "\n";

	return 0;
}