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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	ll bar[2][2];
	cin >> bar[0][0] >> bar[0][1] >> bar[1][0] >> bar[1][1];

	ll prod[2];
	prod[0] = bar[0][0] * bar[0][1];
	prod[1] = bar[1][0] * bar[1][1];

	ll cnt[2][2]; //counts in each prod of 2's and 3's
	memset (cnt, 0, sizeof (cnt));
	while ((prod[0] & 1) == 0)
		cnt[0][0]++, prod[0] >>= 1;
	while ((prod[1] & 1) == 0)
		cnt[1][0]++, prod[1] >>= 1;

	while (prod[0] % 3 == 0)
		cnt[0][1]++, prod[0] /= 3;
	while (prod[1] % 3 == 0)
		cnt[1][1]++, prod[1] /= 3;

	if (prod[0] != prod[1])
	{
		cout << "-1";
		return 0;
	}

	ll trans[2][2]; //transformations applied to each
	memset (trans, 0, sizeof (trans));
	if (cnt[0][1] > cnt[1][1])
	{
		trans[0][1] = cnt[0][1] - cnt[1][1];
		cnt[0][0] += cnt[0][1] - cnt[1][1];
		cnt[0][1] = cnt[1][1];
	}
	else
	{
		trans[1][1] = cnt[1][1] - cnt[0][1];
		cnt[1][0] += cnt[1][1] - cnt[0][1];
		cnt[1][1] = cnt[0][1];
	}

	//apply trans 0 (1/2)
	if (cnt[0][0] > cnt[1][0])
	{
		trans[0][0] = cnt[0][0] - cnt[1][0];
		cnt[0][0] = cnt[1][0];
	}
	else
	{
		trans[1][0] = cnt[1][0] - cnt[0][0];
		cnt[1][0] = cnt[0][0];
	}

	cout << trans[0][0] + trans[0][1] + trans[1][0] + trans[1][1] << "\n";

	//now reconstruct. first count factors in each input num
	ll fac[2][2][2], copy[2][2];
	memset (fac, 0, sizeof (fac));
	memcpy (copy, bar, sizeof (bar));

	for (int a = 0;a < 2;a++)
	{
		for (int b = 0, c;b < 2;b++)
		{
			while ((copy[a][b] & 1) == 0)
				fac[a][b][0]++, copy[a][b] >>= 1;
			while (copy[a][b] % 3 == 0)
				fac[a][b][1]++, copy[a][b] /= 3;

			c = min (fac[a][b][1], trans[a][1]); //max applications of trans 1
			trans[a][1] -= c;
			fac[a][b][1] -= c;
			fac[a][b][0] += c;
			c = min (fac[a][b][0], trans[a][0]);
			trans[a][0] -= c;
			fac[a][b][0] -= c;

			copy[a][b] <<= fac[a][b][0];
			for (int d = 0;d < fac[a][b][1];d++)
				copy[a][b] *= 3;

			cout << copy[a][b] << " ";
		}
		cout << "\n";
	}

	return 0;
}