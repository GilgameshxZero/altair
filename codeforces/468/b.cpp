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

	int n, A, B;
	cin >> n >> A >> B;

	bool flip = (A <= B);
	if (flip)
		swap (A, B);

	bitset<100000> ans;
	map<int, pair<int, bool> > x;
	for (int a = 0, b;a < n;a++)
		cin >> b,
		x.insert (make_pair (b, make_pair (a, true)));
	ans.reset ();

	for (map<int, pair<int, bool> >::iterator a = x.begin (), b;a != x.end ();a++)
	{
		if (!a->second.second)
			continue;
		b = x.find (A - a->first);
		if (b != x.end () && b->second.second)
		{
			a->second.second = false;
			b->second.second = false;
		}
		else
		{
			b = x.find (B - a->first);
			if (b == x.end () || !b->second.second)
			{
				cout << "NO\n";
				return 0;
			}
			a->second.second = false;
			b->second.second = false;
			ans[a->second.first] = true;
			ans[b->second.first] = true;
		}
	}

	cout << "YES\n";
	for (int a = 0;a < n - 1;a++)
		cout << (int)(ans[a] ^ flip) << " ";
	cout << (int)(ans[n - 1] ^ flip) << "\n";

	return 0;
}