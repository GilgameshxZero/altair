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

int sp[501][501], pt[2][500][501];
bool sq[500][500];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int h, w;
	cin >> h >> w;

	memset (sq, 0, sizeof (sq));
	string ts;
	for (int a = 0; a < h; a++)
	{
		cin >> ts;
		for (int b = 0; b < w; b++)
			if (ts[b] == '.')
				sq[a][b] = true;
	}

	memset (pt, 0, sizeof (pt));
	for (int a = 1; a < h; a++)
	{
		if (sq[a - 1][0] == sq[a][0] && sq[a - 1][0] == true)
			pt[0][a][1] = 1;
		else
			pt[0][a][1] = 0;

		for (int b = 2; b <= w; b++)
		{
			pt[0][a][b] = pt[0][a][b - 1];
			if (sq[a - 1][b - 1] == sq[a][b - 1] && sq[a - 1][b - 1] == true)
				pt[0][a][b]++;
		}
	}

	for (int a = 1; a < w; a++)
	{
		if (sq[0][a - 1] == sq[0][a] && sq[0][a] == true)
			pt[1][a][1] = 1;
		else
			pt[1][a][1] = 0;

		for (int b = 2; b <= h; b++)
		{
			pt[1][a][b] = pt[1][a][b - 1];
			if (sq[b - 1][a - 1] == sq[b - 1][a] && sq[b - 1][a - 1] == true)
				pt[1][a][b]++;
		}
	}

	memset (sp, 0, sizeof (sp));
	for (int a = 1; a <= h; a++)
	{
		for (int b = 1; b <= w; b++)
		{
			sp[a][b] = sp[a - 1][b] + sp[a][b - 1] - sp[a - 1][b - 1];
			if (a != 1 && sq[a - 1][b - 1] == sq[a - 2][b - 1] && sq[a - 1][b - 1] == true)
				sp[a][b]++;
			if (b != 1 && sq[a - 1][b - 1] == sq[a - 1][b - 2] && sq[a - 1][b - 1] == true)
				sp[a][b]++;
		}
	}

	int q, r1, c1, r2, c2, ans;
	cin >> q;
	for (int a = 0; a < q; a++)
	{
		cin >> r1 >> c1 >> r2 >> c2;
		r1--;
		c1--;
		ans = sp[r2][c2] - sp[r2][c1] - sp[r1][c2] + sp[r1][c1];
		ans -= pt[0][r1][c2] - pt[0][r1][c1];
		ans -= pt[1][c1][r2] - pt[1][c1][r1];
		cout << ans << '\n';
	}

	return 0;
}