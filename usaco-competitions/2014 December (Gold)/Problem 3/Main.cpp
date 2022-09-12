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
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("cowjog.in", "r", stdin);
	std::freopen ("cowjog.out", "w", stdout);

	int n, t;
	cin >> n >> t;

	vector< pair<ll, ll> > cow (n);
	for (int a = 0;a < n;a++)
		cin >> cow[a].first >> cow[a].second;

	//go from farthest cow
	vector<ll> group; //sorted array of min end pos for each group
	group.push_back (cow[n - 1].first + t * cow[n - 1].second);
	for (int a = n - 2;a >= 0;a--)
	{
		//binary search for group with end time just greater than this end time
		vector<ll>::iterator it = upper_bound (group.begin (), group.end (), cow[a].first + t * cow[a].second);

		if (it == group.end ())
			group.push_back (cow[a].first + t * cow[a].second);
		else
			(*it) = cow[a].first + t * cow[a].second;
	}

	cout << group.size () << "\n";

	return 0;
}