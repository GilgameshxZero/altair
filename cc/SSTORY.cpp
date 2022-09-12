//Binary search with Rabin-Karp.
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

int ModPow (int x, int p, int m)
{
	if (p == 0)
		return 1;
	else if ((p & 1) == 1)
	{
		int k = ModPow (x, p >> 1, m);
		return k * k % m * x % m;
	}
	else
	{
		int k = ModPow (x, p >> 1, m);
		return k * k % m;
	}
}

bool RKComp (string s[2], int len, string& ans)
{
	const int H0 = 12289, H1 = 24593, BASE = 193; //Double hash.
	bitset<H0> bs0;
	bitset<H1> bs1;

	bs0.reset ();
	bs1.reset ();

	//Rolling hash all s[0]'s hashes into bitsets.
	int last_pow[2] = {ModPow (BASE, len - 1, H0), ModPow (BASE, len - 1, H1)};
	int roll[2] = {0, 0};
	for (int a = 0;a < len;a++) //Initialize rolling hash.
		roll[0] = (roll[0] * BASE + s[0][a]) % H0,
		roll[1] = (roll[1] * BASE + s[0][a]) % H1;
	bs0[roll[0]] = true;
	bs1[roll[1]] = true;
	for (int a = len;a < s[0].length ();a++)
	{
		roll[0] = ((roll[0] - last_pow[0] * s[0][a - len] % H0 + H0) % H0 * BASE + s[0][a]) % H0;
		roll[1] = ((roll[1] - last_pow[1] * s[0][a - len] % H1 + H1) % H1 * BASE + s[0][a]) % H1;
		bs0[roll[0]] = true;
		bs1[roll[1]] = true;
	}

	//Rolling hash all s[1]'s hashes and check if they exist. If so, return the substring.
	roll[0] = roll[1] = 0;
	for (int a = 0;a < len;a++)
		roll[0] = (roll[0] * BASE + s[1][a]) % H0,
		roll[1] = (roll[1] * BASE + s[1][a]) % H1;
	if (bs0[roll[0]] == true && bs1[roll[1]] == true)
	{
		ans = s[1].substr (0, len);
		return true;
	}
	for (int a = len;a < s[1].length ();a++)
	{
		roll[0] = ((roll[0] - last_pow[0] * s[1][a - len] % H0 + H0) % H0 * BASE + s[1][a]) % H0;
		roll[1] = ((roll[1] - last_pow[1] * s[1][a - len] % H1 + H1) % H1 * BASE + s[1][a]) % H1;
		if (bs0[roll[0]] == true && bs1[roll[1]] == true)
		{
			ans = s[1].substr (a - len + 1, len);
			return true;
		}
	}

	return false;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin); freopen ("output.txt", "w", stdout);

	string s[2], ans;
	cin >> s[0] >> s[1];

	int low = 0, high = min (s[0].length (), s[1].length ()) + 1, mid;
	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (RKComp (s, mid, ans))
			low = mid;
		else
			high = mid;
	}

	if (low == 0)
		cout << "0\n";
	else
	{
		RKComp (s, low, ans);
		cout << ans << "\n" << low << "\n";
	}

	return 0;
}