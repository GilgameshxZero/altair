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

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	vector< pair<int, int> > st;
	string ans;

	for (int a = 0;a < n;a++)
	{
		int b, c;
		cin >> b >> c;
		ans += "(";
		st.push_back (make_pair (ans.length () + b - 1, ans.length () + c - 1));
		while (!st.empty () && ans.length () >= st.back ().first)
		{
			if (st.back ().second < ans.length ())
			{
				cout << "IMPOSSIBLE";
				return 0;
			}
			ans += ")";
			st.pop_back ();
		}
	}

	if (st.empty ())
		cout << ans;
	else
		cout << "IMPOSSIBLE";

	return 0;
}