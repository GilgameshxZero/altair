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

struct LetCnt
{
	int cnt[26];

	LetCnt ()
	{
		memset (cnt, 0, sizeof (cnt));
	}

	bool operator== (const LetCnt& other)
	{
		for (int a = 0;a < 26;a++)
			if (other.cnt[a] != cnt[a])
				return false;
		return true;
	}
};

int C2 (int x)
{
	return x * (x - 1) / 2;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin); freopen ("output.txt", "w", stdout);

	int T;
	cin >> T;

	for (int a = 0;a < T;a++)
	{
		string s;
		cin >> s;

		int ans = 0;
		for (int b = 1;b < s.length ();b++)
		{
			vector< pair<LetCnt, int> > cur;
			LetCnt prev;
			for (int c = 0;c < b;c++)
				prev.cnt[s[c] - 'a']++;
			cur.push_back (make_pair (prev, 1));
			for (int c = 1;c <= s.length () - b;c++)
			{
				//update prev
				prev.cnt[s[c - 1] - 'a']--;
				prev.cnt[s[c + b - 1] - 'a']++;

				//comp with cur
				bool flag = false;
				for (int d = 0;d < cur.size ();d++)
					if (cur[d].first == prev)
						cur[d].second++,
						flag = true;
				if (!flag)
					cur.push_back (make_pair (prev, 1));
			}

			for (int c = 0;c < cur.size ();c++)
				ans += C2 (cur[c].second);
		}

		cout << ans << "\n";
	}

	return 0;
}