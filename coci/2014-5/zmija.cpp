#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

string grid[1000];
int mna[1001], mxa[1001], cnt[1000], tot; //goes from bot to top

int main ()
{
	//freopen ("in.txt", "r", stdin); freopen ("out.txt", "w", stdout);

	int R, C;
	cin >> R >> C;

	for (int a = 0;a < 1001;a++)
		mna[a] = C - 1;
	memset (mxa, 0, sizeof (mxa));
	memset (cnt, 0, sizeof (cnt));
	tot = 0;

	for (int a = 0;a < R;a++)
	{
		cin >> grid[a];
		for (int b = 0;b < C;b++)
			if (grid[a][b] == 'J')
				mna[R - 1 - a] = min (mna[R - 1 - a], b),
				mxa[R - 1 - a] = max (mxa[R - 1 - a], b),
				cnt[R - 1 - a]++,
				tot++;
	}

	int ans = -1, cur = 0, coll = 0;
	mna[R] = mna[R - 1];
	mxa[R] = mxa[R - 1];
	
	for (int a = 0;a < R;a++)
	{
		if (a % 2 == 0)
			ans += max (max (mxa[a], mxa[a + 1]) - cur, 0),
			cur = cur + max (max (mxa[a], mxa[a + 1]) - cur, 0);
		else
			ans += max (cur - min (mna[a], mna[a + 1]), 0),
			cur -= max (cur - min (mna[a], mna[a + 1]), 0);
		coll += cnt[a];
		ans++;
		if (coll == tot)
			break;
	}

	cout << ans;

	return 0;
}