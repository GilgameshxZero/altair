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

	int n, pre[100002];
	cin >> n;
	pre[0] = 0;
	for (int a = 0;a < n;a++)
		cin >> pre[a + 1],
		pre[a + 1] += pre[a];
	pre[n + 1] = pre[n] + 1;
	pre[n + 2] = pre[n + 1] + 1;
	int q;
	cin >> q;
	//vector<int> p (pre);
	for (int a = 0;a < q;a++)
	{
		int b;
		cin >> b;
		cout << lower_bound (pre, pre + n + 1, b) - pre << "\n";
	}

	return 0;
}