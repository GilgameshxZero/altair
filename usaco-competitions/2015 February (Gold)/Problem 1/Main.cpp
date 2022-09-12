#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int FenSum (vector<int> &fen, int k, const int MOD)
{
	int r = 0;
	for (;k > 0;k -= (k & -k))
		r = (r + fen[k]) % MOD;
	return r;
}

void FenAdd (vector<int> &fen, int x, int k, const int MOD)
{
	for (;k < fen.size ();k += (k & -k))
		fen[k] = (fen[k] + x) % MOD;
}

int BSIncInc (vector<int> &arr, int x)
{
	int low = 0, high = arr.size (), mid;
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (arr[mid] == x)
			return mid;
		else if (arr[mid] < x)
			low = mid;
		else
			high = mid;
	}
	return low;
}

int main ()
{
	const int MOD = 1000000007;
	int R, C, K, tot, ans;
	vector< vector<int> > grid, cfen, cbin;
	vector<int> tfen, tcol;

	freopen ("hopscotch.in", "r", stdin);
	freopen ("hopscotch.out", "w", stdout);

	cin >> R >> C >> K;
	grid.resize (R, vector<int> (C, 0));

	for (int a = 0;a < R;a++)
		for (int b = 0;b < C;b++)
			cin >> grid[a][b];

	tfen.resize (R + 1, 0);
	cfen.resize (K, vector<int> ());
	cbin.resize (K, vector<int> ());
	tcol.resize (K, 0);
	tot = 0;

	for (int a = 0;a < R;a++)
		for (int b = 0;b < C;b++)
			if (cbin[grid[a][b] - 1].empty () || cbin[grid[a][b] - 1].back () != a)
				cbin[grid[a][b] - 1].push_back (a);

	for (int a = 0;a < K;a++)
		cfen[a].resize (cbin[a].size () + 1);

	FenAdd (tfen, 1, R, MOD);
	FenAdd (cfen[grid[R - 1][C - 1] - 1], 1, cfen[grid[R - 1][C - 1] - 1].size () - 1, MOD);
	tcol[grid[R - 1][C - 1] - 1] = 1;
	tot = 1;

	for (int a = C - 2;a >= 0;a--)
	{
		for (int b = 0, c, d;b < R - 1;b++)
		{
			c = (tot - FenSum (tfen, b + 1, MOD) + MOD) % MOD;
			d = BSIncInc (cbin[grid[b][a] - 1], b) + 1;
			c = (c + MOD - ((MOD + tcol[grid[b][a] - 1] - FenSum (cfen[grid[b][a] - 1], d, MOD)) % MOD)) % MOD;
			FenAdd (cfen[grid[b][a] - 1], c, d, MOD);
			FenAdd (tfen, c, b + 1, MOD);
			tcol[grid[b][a] - 1] = (tcol[grid[b][a] - 1] + c) % MOD;
			tot = (tot + c) % MOD;

			if (a == 0 && b == 0)
			{
				ans = c;
				break;
			}
		}
	}

	cout << ans << "\n";
	return 0;
};