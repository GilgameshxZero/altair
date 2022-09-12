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

	//freopen ("input0.txt", "r", stdin); freopen ("output.txt", "w", stdout);

	int n;
	cin >> n;

	vector<int> x;
	x.resize (n);
	for (int a = 0;a < n;a++)
		cin >> x[a];

	sort (x.begin (), x.end ());

	int ans = 0;
	for (int a = 0;a < x.size ();)
	{
		ans++;
		int k = x[a];
		while (a < x.size () && x[a] - k <= 4) a++;
	}

	cout << ans;

	return 0;
}