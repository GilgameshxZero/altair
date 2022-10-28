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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	string s1, s2;
	cin >> s1 >> s2;

	//order
	bool f1 = true;
	for (int a = 0, b = 0;a < s2.size ();a++)
	{
		bool f2 = false;
		for (;b < s1.size ();b++)
		{
			if (s1[b] == s2[a])
			{
				f2 = true;
				b++;
				break;
			}
		}

		if (!f2)
		{
			f1 = false;
			break;
		}
	}

	if (f1)
	{
		cout << "automaton\n";
		return 0;
	}

	//same
	int cnt[2][128];
	memset (cnt, 0, sizeof (cnt));
	for (int a = 0;a < s1.size ();a++)
		cnt[0][s1[a]]++;
	for (int a = 0;a < s2.size ();a++)
		cnt[1][s2[a]]++;

	f1 = true;
	for (int a = 0;a < 128;a++)
		if (cnt[0][a] != cnt[1][a])
			f1 = false;

	if (f1)
	{
		cout << "array\n";
		return 0;
	}

	//tree
	f1 = false;
	for (int a = 0;a < 128;a++)
		if (cnt[1][a] > cnt[0][a])
			f1 = true;

	if (f1)
	{
		cout << "need tree\n";
		return 0;
	}

	cout << "both\n";

	return 0;
}