#define _CRT_SECURE_NO_WARNINGS

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

int Decode (vector< vector<bool> > &img, string &s, int pos, int x, int y, int sz)
{
	if (s[pos] == 'e')
	{
		for (int a = 0;a < sz;a++)
			for (int b = 0;b < sz;b++)
				img[x + a][y + b] = false;
		return pos + 1;
	}
	else if (s[pos] == 'f')
	{
		for (int a = 0; a < sz; a++)
			for (int b = 0; b < sz; b++)
				img[x + a][y + b] = true;
		return pos + 1;
	}
	else
	{
		int k;
		k = Decode (img, s, pos + 1, x, y + sz / 2, sz / 2);
		k = Decode (img, s, k, x, y, sz / 2);
		k = Decode (img, s, k, x + sz / 2, y, sz / 2);
		k = Decode (img, s, k, x + sz / 2, y + sz / 2, sz / 2);
		return k;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int t;
	cin >> t;

	for (int a = 0;a < t;a++)
	{
		string s[2];
		cin >> s[0] >> s[1];

		vector< vector<bool> > img[2];
		img[0].resize (32, vector<bool>(32, false));
		img[1] = img[0];

		Decode (img[0], s[0], 0, 0, 0, 32);
		Decode (img[1], s[1], 0, 0, 0, 32);

		int ans = 0;

		for (int b = 0;b < 32;b++)
		{
			for (int c = 0;c < 32;c++)
			{
				img[0][b][c] = img[0][b][c] | img[1][b][c];
				ans += img[0][b][c];
			}
		}

		cout << "There are " << ans << " black pixels.\n";
	}

	return 0;
}