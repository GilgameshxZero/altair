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

	vector<int> mm (50001, 200000);
	int n, m;
	cin >> n >> m;

	mm[n] = 0;
	queue<int> q;
	q.push (n);
	while (!q.empty ())
	{
		if (q.front () - 1 > 0 && mm[q.front () - 1] == 200000)
			mm[q.front () - 1] = mm[q.front ()] + 1,
			q.push (q.front () - 1);
		if (q.front () * 2 <= 2 * m && mm[q.front () * 2] == 200000)
			mm[q.front () * 2] = mm[q.front ()] + 1,
			q.push (q.front () * 2);
		q.pop ();
	}

	cout << mm[m];

	return 0;
}