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

	string orig;
	long long flips;

	cin >> orig >> flips;
	
	for (int a = 0, b, c;a < orig.length () && flips > 0;)
	{
		char lg = 0;
		for (b = a;b <= a + flips && b < orig.length ();b++)
			if (orig[b] > lg)
				lg = orig[b], c = b;
		if (c != a)
		{
			flips -= c - a;
			orig.erase (orig.begin () + c);
			orig.insert (orig.begin () + a, lg);
		}
		a++;
	}

	cout << orig << "\n";

	return 0;
}