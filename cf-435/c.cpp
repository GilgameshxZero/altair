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

struct Line
{
	int m, b, l, r;
};

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n, x = 0, y = 0, high = 0, low = 0;
	Line line[1000];
	vector< pair<int, char> > point;

	cin >> n;
	for (int a = 0, b;a < n;a++)
	{
		cin >> b;
		line[a].m = -2 * (a % 2) + 1;
		line[a].b = y - x * line[a].m;
		line[a].l = x;
		line[a].r = x + b - 1;
		//cout << line[a].m << "\t" << line[a].b << "\n";
		x += b;
		y += line[a].m * (b - 1);
		high = max (high, y);
		low = min (low, y);
	}

	//cout << high << "\t" << low << "\n";

	for (int a = high;a >= low;a--)
	{
		point.clear ();
		for (int b = 0, c;b < n;b++)
		{
			c = (a - line[b].b) / line[b].m;
			//c += (line[b].m - 1) / 2;
			if (c >= line[b].l && c <= line[b].r)
				point.push_back (make_pair (c, (char)((139 - 45 * line[b].m) / 2)));
		}

		sort (point.begin (), point.end ());

		for (int b = 0;b < point[0].first;b++)
			cout << " ";
		cout << point[0].second;
		for (int b = 1;b < point.size ();b++)
		{
			for (int c = point[b - 1].first + 1;c < point[b].first;c++)
				cout << " ";
			cout << point[b].second;
		}
		for (int b = point[point.size () - 1].first + 1;b < x;b++)
			cout << " ";

		if (a != low)
			cout << "\n";
	}

	return 0;
}