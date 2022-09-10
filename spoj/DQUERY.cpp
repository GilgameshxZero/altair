#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;

//sweepline fenwick with last pos of #

int n, x[30000], last[1000000], fen[30001], q, ans[200000];
pair< pair<int, int> , int> y[200000]; //end, beg

int Sum (int k)
{
	int r = 0;
	for (;k > 0;k -= k & -k)
		r += fen[k];
	return r;
}

void Add (int k, int i)
{
	for (;k <= 30000;k += k & -k)
		fen[k] += i;
}

int main ()
{
	ios_base::sync_with_stdio (false);
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> x[a];
	cin >> q;
	for (int a = 0;a < q;a++)
		cin >> y[a].first.second >> y[a].first.first,
		y[a].second = a;

	sort (y, y + q);
	memset (fen, 0, sizeof (fen));
	memset (last, 0, sizeof (last));

	for (int a = 0, b = 0;b < q;)
	{
		if (y[b].first.first == a)
		{
			ans[y[b].second] = Sum (30000) - Sum (y[b].first.second - 1);
			b++;
		}
		else
		{
			if (last[x[a]] != 0)
				Add (last[x[a]], -1);
			last[x[a]] = a + 1;
			Add (last[x[a]], 1);
			a++;
		}
	}

	for (int a = 0;a < q;a++)
		cout << ans[a] << "\n";

	return 0;
}