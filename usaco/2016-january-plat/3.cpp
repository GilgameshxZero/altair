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

//KMP hashing, optimal left or right until can identify position
//why no work?

using namespace std;

typedef long long ll;

class Point
{
public:
	int x, y;

	Point ()
	{
		x = y = 0;
	}
};

string its (int x)
{
	stringstream ss;
	ss << x;
	return ss.str ();
}

int dist (Point x, Point y)
{
	return abs (x.x - y.x) + abs (x.y - y.y);
}

double CrossProd (Point& a, Point& b, Point& c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int KMP (string &big, string &small)
{
	//build failure function for ele
	vector<int> ff;
	ff.resize (small.size () + 1);
	ff[0] = ff[1] = 0;
	for (int a = 2, b; a < ff.size (); a++)
	{
		b = ff[a - 1];
		while (true)
		{
			if (small[b] == small[a - 1])
			{
				ff[a] = b + 1;
				break;
			}
			else if (b == 0)
			{
				ff[a] = 0;
				break;
			}
			else
				b = ff[b];
		}
	}

	int ans = 0;
	for (int a = 0, b = 0; a < big.size ();)
	{
		if (big[a] == small[b])
		{
			a++;
			b++;
			if (b == small.size ())
			{
				ans++;
				b = ff[b];
			}
		}
		else if (b != 0)
			b = ff[b];
		else
			a++;
	}

	return ans;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("lightsout.in", "r", stdin);
	std::freopen ("lightsout.out", "w", stdout);

	int n;
	cin >> n;

	vector< Point > pt;
	pt.resize (n);
	for (int a = 0; a < n; a++)
		cin >> pt[a].x >> pt[a].y;

	pt.push_back (pt[0]);
	pt.insert (pt.begin (), pt[n - 1]);

	string path = "S";
	for (int a = 1; a < n; a++)
	{
		path += its (dist (pt[a], pt[a + 1]));

		if (CrossProd (pt[a], pt[a + 1], pt[a + 2]) > 0)
			path += "L";
		else
			path += "R";
	}

	path += its (dist (pt[n], pt[n + 1]));
	path += "S";
	string revp = "S";
	for (int a = n + 1;a >= 2; a--)
	{
		revp += its (dist (pt[a], pt[a - 1]));

		if (CrossProd (pt[a], pt[a - 1], pt[a - 2]) > 0)
			revp += "L";
		else
			revp += "R";
	}
	revp.pop_back ();
	revp += "S";

	vector<int> pre;
	pre.resize (n + 2);
	for (int a = 2; a <= n + 1; a++)
		pre[a] = pre[a - 1] + dist (pt[a - 1], pt[a]);

	int ans = 0, ans2 = ans;
	vector<int> op;
	op.resize (n + 2, 1e9);
	for (int a = 2; a <= n; a++)
		op[a] = min (pre[a], pre[n + 1] - pre[a]);

	for (int a = 2; a <= n; a++)
	{
		//left
		//if (pre[a] != op[a])
		{
			int test = 0;
			string check;
			if (CrossProd (pt[a + 1], pt[a], pt[a - 1]) > 0)
				check = "L";
			else
				check = "R";

			int b;
			for (b = a - 1; b > 1; b--)
			{
				check += its (dist (pt[b + 1], pt[b]));
				test += dist (pt[b + 1], pt[b]);
				if (CrossProd (pt[b + 1], pt[b], pt[b - 1]) > 0)
					check += "L";
				else
					check += "R";

				if (KMP (path, check) + KMP (revp, check) == 1)
				{
					ans = max (ans, test + op[b] - op[a]);
					break;
				}
				if (KMP (path, check) + KMP (revp, check) == 0)
					memset (0, 0, 10000000);
			}
			if (b == 1)
				ans = max (ans, pre[a] - op[a]);
		}
		//right
		//if (pre[n + 1] - pre[a] != op[a])
		{
			int test = 0;
			string check;
			if (CrossProd (pt[a - 1], pt[a], pt[a + 1]) > 0)
				check = "L";
			else
				check = "R";

			int b;
			for (b = a + 1; b < n + 1; b++)
			{
				check += its (dist (pt[b - 1], pt[b]));
				test += dist (pt[b - 1], pt[b]);
				if (CrossProd (pt[b - 1], pt[b], pt[b + 1]) > 0)
					check += "L";
				else
					check += "R";

				if (KMP (path, check) + KMP (revp, check) == 1)
				{
					ans2 = max (ans2, test + op[b] - op[a]);
					break;
				}
				if (KMP (path, check) + KMP (revp, check) == 0)
					memset (0, 0, 10000000);
			}
			if (b == n + 1)
				ans2 = max (ans2, pre[n + 1] - pre[a] - op[a]);
		}
	}

	cout << min (ans, ans2) << '\n';

	return 0;
}