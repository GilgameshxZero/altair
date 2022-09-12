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

struct LMask
{
	int cnt[26];
};

const int HMOD = 1572869, HMUL = 43, HMOD2 = 3145739, HMUL2 = 97;

string A, B;
LMask lcnt[2][200001];
int L, hval[2][200001], hval2[2][200001];

void SubLMask (LMask &x, LMask &y, LMask &r)
{
	for (int a = 0; a < 26; a++)
		r.cnt[a] = x.cnt[a] - y.cnt[a];
}

bool EQLMask (LMask &x, LMask &y)
{
	for (int a = 0; a < 26; a++)
	{
		if (x.cnt[a] != y.cnt[a])
			return false;
	}

	return true;
}

int PowerMod (int x, int y, int mod)
{
	if (y == 0)
		return 1;
	else if (y & 1)
	{
		int k = PowerMod (x, y >> 1, mod);
		return ((ll)k * k * x) % mod;
	}
	else
	{
		int k = PowerMod (x, y >> 1, mod);
		return ((ll)k * k) % mod;
	}
}

int SubHash (int h0, int h1, int l)
{
	h1 = ((ll)h1 * PowerMod (HMUL, l, HMOD)) % HMOD;
	return (h0 + HMOD - h1) % HMOD;
}

int SubHash2 (int h0, int h1, int l)
{
	h1 = ((ll)h1 * PowerMod (HMUL2, l, HMOD2)) % HMOD2;
	return (h0 + HMOD2 - h1) % HMOD2;
}

bool EQ (int x, int y, int l)
{
	if (l & 1 == 1)
	{
		LMask r0, r1;
		SubLMask (lcnt[0][x + l], lcnt[0][x], r0);
		SubLMask (lcnt[1][y + l], lcnt[1][y], r1);

		if (!EQLMask (r0, r1))
			return false;

		if (SubHash (hval[0][x + l], hval[0][x], l) != SubHash (hval[1][y + l], hval[1][y], l))
			return false;
		if (SubHash2 (hval2[0][x + l], hval2[0][x], l) != SubHash2 (hval2[1][y + l], hval2[1][y], l))
			return false;

		for (int a = 0; a < l; a++)
			if (A[x + a] != B[y + a])
				return false;
		return true;
	}
	else //even
	{
		LMask r0, r1;
		SubLMask (lcnt[0][x + l], lcnt[0][x], r0);
		SubLMask (lcnt[1][y + l], lcnt[1][y], r1);

		if (!EQLMask (r0, r1))
			return false;

		if (SubHash (hval[0][x + l], hval[0][x], l) == SubHash (hval[1][y + l], hval[1][y], l) && 
			SubHash2 (hval2[0][x + l], hval2[0][x], l) == SubHash2 (hval2[1][y + l], hval2[1][y], l))
			return true;

		if (EQ (x, y, l / 2) && EQ (x + l / 2, y + l / 2, l / 2))
			return true;
		if (EQ (x, y + l / 2, l / 2) && EQ (x + l / 2, y, l / 2))
			return true;
		return false;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> A >> B;
	L = A.length ();

	memset (lcnt[0][0].cnt, 0, sizeof (lcnt[0][0].cnt));
	memset (lcnt[1][0].cnt, 0, sizeof (lcnt[1][0].cnt));

	for (int a = 1; a <= L; a++)
	{
		memcpy (lcnt[0][a].cnt, lcnt[0][a - 1].cnt, sizeof (lcnt[0][a].cnt));
		memcpy (lcnt[1][a].cnt, lcnt[1][a - 1].cnt, sizeof (lcnt[1][a].cnt));
		lcnt[0][a].cnt[A[a - 1] - 'a']++;
		lcnt[1][a].cnt[B[a - 1] - 'a']++;
		hval[0][a] = (hval[0][a - 1] * HMUL + A[a - 1] - 'a') % HMOD;
		hval[1][a] = (hval[1][a - 1] * HMUL + B[a - 1] - 'a') % HMOD;
		hval2[0][a] = (hval2[0][a - 1] * HMUL2 + A[a - 1] - 'a') % HMOD2;
		hval2[1][a] = (hval2[1][a - 1] * HMUL2 + B[a - 1] - 'a') % HMOD2;
	}

	if (EQ (0, 0, L))
		cout << "YES";
	else
		cout << "NO";

	return 0;
}