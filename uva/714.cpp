#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

bool Eval (vector<int>& x, vector<int>& ans, int k, int m)
{
	vector<int> cut;
	int sum = 0;
	for (int a = x.size () - 1;a >= 0;a--)
	{
		sum += x[a];
		if (sum > k)
			cut.push_back (a),
			sum = x[a];
	}

	if (cut.size () != m - 1)
		return false;
	else
	{
		ans = cut;
		return true;
	}
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int t;
	cin >> t;
	for (;t > 0;t--)
	{
		int n, m;
		cin >> n >> m;
		vector<int> x, ans;
		x.resize (n);
		int low = 0, high = 0, mid;
		for (int a = 0;a < n;a++)
			cin >> x[a],
			high += x[a],
			low = max (low, x[a]);
		if (n == 1)
		{
			cout << x[0] << "\n";
			continue;
		}
		//binary search on function
		while (low + 1 < high)
		{
			mid = (low + high) / 2;
			if (Eval (x, ans, mid, m))
				high = mid;
			else
				low = mid;
		}
		reverse (ans.begin (), ans.end ());
		for (int a = 0;a <= ans[0];a++)
			cout << x[a] << " ";
		cout << "/ ";
		for (int a = 0;a < ans.size () - 1;a++)
		{
			for (int b = ans[a] + 1;b <= ans[a + 1];b++)
				cout << x[b] << " ";
			cout << "/ ";
		}
		for (int a = ans[ans.size () - 1] + 1;a < n;a++)
			cout << x[a] << " ";
		cout << "\n";
	}

	return 0;
}