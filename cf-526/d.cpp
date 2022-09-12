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

struct HashVal
{
	static const int HASHMUL = 2, HASHX = 37;
	static const int HASHLIM[HASHMUL];
	int val[HASHMUL];

	void LeftShift ()
	{
		for (int a = 0;a < HASHMUL;a++)
			val[a] = (val[a] * HASHX) % HASHLIM[a];
	}

	void AddPos (int k)
	{
		for (int a = 0;a < HASHMUL;a++)
			val[a] = (val[a] + k % HASHLIM[a]) % HASHLIM[a];
	}

	void Zero ()
	{
		memset (val, 0, sizeof (val));
	}

	bool operator < (const HashVal &other) const
	{
		for (int a = 0;a < HASHMUL;a++)
			if (val[a] < other.val[a])
				return true;
			else if (val[a] > other.val[a])
				return false;
		return false;
	}

	bool operator > (const HashVal &other) const
	{
		for (int a = 0;a < HASHMUL;a++)
			if (val[a] > other.val[a])
				return true;
			else if (val[a] < other.val[a])
				return false;
		return false;
	}

	bool operator == (const HashVal &other) const
	{
		for (int a = 0;a < HASHMUL;a++)
			if (val[a] != other.val[a])
				return false;
		return true;
	}

	inline HashVal operator * (const int x) const
	{
		HashVal r;
		for (int a = 0;a < HASHMUL;a++)
			r.val[a] = (ll)val[a] * x % HASHLIM[a];
		return r;
	}

	inline HashVal operator * (const HashVal &other) const
	{
		HashVal r;
		for (int a = 0;a < HASHMUL;a++)
			r.val[a] = (ll)val[a] * other.val[a] % HASHLIM[a];
		return r;
	}

	inline HashVal operator - (const HashVal &other) const
	{
		HashVal r;
		for (int a = 0;a < HASHMUL;a++)
			r.val[a] = ((ll)val[a] - other.val[a] + HASHLIM[a]) % HASHLIM[a];
		return r;
	}

	inline HashVal operator + (const HashVal &other) const
	{
		HashVal r;
		for (int a = 0;a < HASHMUL;a++)
			r.val[a] = ((ll)val[a] + other.val[a]) % HASHLIM[a];
		return r;
	}
};

const int HashVal::HASHLIM[HashVal::HASHMUL] = /*{100153, 123191, 150659, */{184901, 193013};

int HighBit (int x)
{
	int a;
	for (a = 0;x > 0;x >>= 1, a++);
	return a;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int N, K;
	cin >> N >> K;

	string S;
	cin >> S;

	vector<HashVal> hv (N);
	hv[0].AddPos (S[0] - 'a');
	for (int a = 1;a < N;a++)
	{
		hv[a] = hv[a - 1];
		hv[a].LeftShift ();
		hv[a].AddPos (S[a] - 'a');
	}

	vector<HashVal> xexp (N + 1);
	for (int a = 0;a < 5;a++)
		xexp[0].val[a] = 1;
	for (int a = 1;a <= N;a++)
	{
		xexp[a] = xexp[a - 1];
		xexp[a].LeftShift ();
	}

	int mtest = N / K;
	bitset<1000000> ans, pos, know;
	know.reset ();
	bool flag;
	int limord = HighBit (K) - 1;
	int mm = (1 << limord), low, high, mid;
	ans.reset ();
	for (int a = 1;a <= mtest;a++)
	{
		flag = true;
		
		for (int b = 2, c;b <= mm;b <<= 1)
		{
			c = (b / 2) * a - 1;
			if (know[c] == true)
			{
				if (pos[c] == true)
					continue;
				else
				{
					flag = false;
					break;
				}
			}
			if (!(hv[c] == (hv[b * a - 1] - hv[c] * xexp[c + 1])))
			{
				flag = false;
				pos[c] = false;
				know[c] = true;
				break;
			}
			else
			{
				know[c] = true;
				pos[c] = true;
			}
		}
		if (!flag)
			continue;

		if (mm != K)
			if (!(hv[mm * a - 1] == (hv[K * a - 1] - hv[(K - mm) * a - 1] * xexp[mm * a])))
				continue;

		/*for (int b = 2 * a - 1;b <= K * a - 1;b = (b + 1) * 2 - 1)
		{
			if (!(hv[a - 1] == (hv[b] - hv[b - a] * xexp[a])))
			{
				flag = false;
				break;
			}
		}*/

		if (flag)
		{
			ans[K * a - 1] = true;

			low = K * a;
			high = min (N, (K + 1) * a);

			while (low + 1 < high)
			{
				mid = (low + high) / 2;
				if (hv[mid - K * a] == hv[mid] - hv[K * a - 1] * xexp[mid - K * a + 1])
					low = mid;
				else
					high = mid;
			}

			if (low < N)
				for (int b = K * a;b <= low;b++)
					ans[b] = true;

			/*for (int b = K * a, c = min (N, (K + 1) * a);b < c;b++)
			{
				if (S[b] == S[b - K * a])
					ans[b] = true;
				else
					break;
			}*/
		}
	}

	for (int a = 0;a < N;a++)
		cout << ans[a];

	return 0;
}