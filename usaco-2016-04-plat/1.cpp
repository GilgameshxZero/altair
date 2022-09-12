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

int Solve (vector<int> x, int low)
{
	vector< vector<int> > split (1, vector<int> ());
	int run = 0, mnum = 0;

	if (x.size () == 1)
		return x[0];

	for (int a = 0;a < x.size ();a++)
	{
		if (x[a] != low && run > 0)
		{
			if (run % 2 == 0)
			{
				split.back ().insert (split.back ().end (), run / 2, low + 1);
				mnum = max (mnum, low + 1);
			}
			else
			{
				split.back ().insert (split.back ().end (), run / 2, low + 1);
				split.push_back (vector<int> (run / 2, low + 1));
				mnum = max (mnum, low + 1);
			}

			run = 0;
			split.back ().push_back (x[a]);
		}
		else if (x[a] == low)
			run++;
		else
			split.back ().push_back (x[a]);

		mnum = max (mnum, x[a]);
	}

	if (run != 0)
	{
		if (run % 2 == 0)
		{
			split.back ().insert (split.back ().end (), run / 2, low + 1);
			mnum = max (mnum, low + 1);
		}
		else
		{
			split.back ().insert (split.back ().end (), run / 2, low + 1);
			split.push_back (vector<int> (run / 2, low + 1));
			mnum = max (mnum, low + 1);
		}
	}

	if (low + 1 > mnum)
		return mnum;

	int ans = 0;
	for (int a = 0;a < split.size ();a++)
		ans = max (ans, Solve (split[a], low + 1));

	return ans;
}

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("262144.in", "r", stdin);
	std::freopen ("262144.out", "w", stdout);

	/*for (int a = 0;a < 10;a++)
		cout << rand () % 3;*/

	int n;
	cin >> n;

	vector<int> x (n);
	for (int a = 0;a < n;a++)
		cin >> x[a];

	cout << Solve (x, 0) << '\n';

	return 0;
}