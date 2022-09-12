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
const int HASHCNT = 3, HASH[] = {24593, 12289, 6151, 3079}, BASE = 193;

struct HashEntry
{
	int num[HASHCNT];
};

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

bool HEComp (HashEntry x, HashEntry y)
{
	for (int a = 0;a < HASHCNT;a++)
	{
		if (x.num[a] < y.num[a])
			return true;
		else if (x.num[a] > y.num[a])
			return false;
	}
	return false;
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string s;
	bitset<26> bad;
	int acc;
	cin >> s;
	cin.get ();
	for (int a = 0;a < 26;a++)
		bad[a] = (cin.get () == '0');
	cin >> acc;

	//rabin-karp each length and find unique OK substrs for each len
	int ans = 0, roll[HASHCNT], last_pow[HASHCNT], bad_cnt;
	vector<HashEntry> table;
	for (int a = 1;a <= s.length ();a++)
	{
		table.clear ();
		bad_cnt = 0;
		for (int b = 0;b < HASHCNT;b++)
		{
			roll[b] = 0;
			last_pow[b] = ModPow (BASE, a - 1, HASH[b]);
		}
		for (int b = 0;b < a;b++)
		{
			for (int c = 0;c < HASHCNT;c++)
				roll[c] = (roll[c] * BASE + s[b]) % HASH[c];
			bad_cnt += bad[s[b] - 'a'];
		}
		if (bad_cnt <= acc)
		{
			table.push_back (HashEntry ());
			for (int b = 0;b < HASHCNT;b++)
				table.back ().num[b] = roll[b];
		}

		//rolling hash
		for (int b = a;b < s.length ();b++)
		{
			bad_cnt += -bad[s[b - a] - 'a'] + bad[s[b] - 'a'];
			for (int c = 0;c < HASHCNT;c++)
				roll[c] = ((roll[c] + HASH[c] - s[b - a] * last_pow[c] % HASH[c]) * BASE + s[b]) % HASH[c];
			if (bad_cnt <= acc)
			{
				table.push_back (HashEntry ());
				for (int c = 0;c < HASHCNT;c++)
					table.back ().num[c] = roll[c];
			}
		}

		//sort table and get number of distinct pairs added to ans
		sort (table.begin (), table.end (), HEComp);
		if (table.size () >= 1)
			ans++;
		for (int b = 1, flag;b < table.size ();b++)
		{
			flag = true;
			for (int c = 0;c < HASHCNT;c++)
				if (table[b].num[c] != table[b - 1].num[c])
					flag = false;
			if (flag == false)
				ans++;
		}
	}

	cout << ans << "\n";

	return 0;
}