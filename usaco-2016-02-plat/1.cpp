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

vector<pair<int, int> > pt;
vector<int> curfen, pre, precopy;

//adds k to the element at pos x
void FenAdd (vector<int>& fen, int k, int x)
{
	for (; x < fen.size (); x += (x & -x))
		fen[x] += k;
}

//sums all elements before and including x
int FenSum (vector<int>& fen, int x)
{
	int r = 0;
	for (; x > 0; x -= (x & -x))
		r += fen[x];
	return r;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("balancing.in", "r", stdin);
	std::freopen ("balancing.out", "w", stdout);
	
	int n;
	int bound[4], xlow, xhigh, xmid, total;
	cin >> n;

	pre.resize (1000005);
	curfen.resize (1000005);

	for (int a = 0, b, c;a < n;a++)
	{
		cin >> b >> c;
		c++;
		pt.push_back (make_pair (b, c));
		FenAdd (pre, 1, c);
	}

	sort (pt.begin (), pt.end ());
	int ans = n;

	precopy = pre;
	for (int a = 0;a < pt.size () / 2;a++)
	{
		FenAdd (pre, -1, pt[a].second);
		FenAdd (curfen, 1, pt[a].second);
	}

	for (int a = pt.size () / 2;a < pt.size () - 1;a++)
	{
		//update pt
		FenAdd (pre, -1, pt[a].second);
		FenAdd (curfen, 1, pt[a].second);

		//bs for ans
		int low = 0, high = n, mid;
		while (high - low >= 2)
		{
			if (low >= ans)
				break;

			mid = (high + low) / 2;

			//bs for bounds on proposed mid
			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (FenSum (curfen, xmid) <= mid)
					xlow = xmid;
				else
					xhigh = xmid;
			}
			bound[0] = xlow;

			total = FenSum (curfen, 1000004);
			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (total - FenSum (curfen, xmid - 1) <= mid)
					xhigh = xmid;
				else
					xlow = xmid;
			}
			bound[1] = xhigh;

			if (bound[1] > bound[0])
			{
				low = mid;
				continue;
			}

			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (FenSum (pre, xmid) <= mid)
					xlow = xmid;
				else
					xhigh = xmid;
			}
			bound[2] = xlow;

			total = FenSum (pre, 1000004);
			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (total - FenSum (pre, xmid - 1) <= mid)
					xhigh = xmid;
				else
					xlow = xmid;
			}
			bound[3] = xhigh;

			//check overlap
			if (bound[0] >= bound[3] && bound[2] >= bound[1] && bound[0] >= bound[1] && bound[2] >= bound[3])
				high = mid;
			else
				low = mid;
		}

		ans = min (ans, high);
	}

	pre = precopy;
	curfen.clear ();
	curfen.resize (1000005);

	for (int a = 0; a < pt.size () / 2; a++)
	{
		//update pt
		FenAdd (pre, -1, pt[a].second);
		FenAdd (curfen, 1, pt[a].second);

		//bs for ans
		int low = 0, high = n, mid;
		while (high - low >= 2)
		{
			if (low >= ans)
				break;

			mid = (high + low) / 2;

			//bs for bounds on proposed mid
			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (FenSum (curfen, xmid) <= mid)
					xlow = xmid;
				else
					xhigh = xmid;
			}
			bound[0] = xlow;

			total = FenSum (curfen, 1000004);
			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (total - FenSum (curfen, xmid - 1) <= mid)
					xhigh = xmid;
				else
					xlow = xmid;
			}
			bound[1] = xhigh;

			if (bound[1] > bound[0])
			{
				low = mid;
				continue;
			}

			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (FenSum (pre, xmid) <= mid)
					xlow = xmid;
				else
					xhigh = xmid;
			}
			bound[2] = xlow;

			total = FenSum (pre, 1000004);
			xlow = 1;
			xhigh = 1000005;
			while (xhigh - xlow >= 2)
			{
				xmid = (xhigh + xlow) / 2;
				if (total - FenSum (pre, xmid - 1) <= mid)
					xhigh = xmid;
				else
					xlow = xmid;
			}
			bound[3] = xhigh;

			//check overlap
			if (bound[0] >= bound[3] && bound[2] >= bound[1] && bound[0] >= bound[1] && bound[2] >= bound[3])
				high = mid;
			else
				low = mid;
		}

		ans = min (ans, high);
	}

	cout << ans << '\n';

	return 0;
}