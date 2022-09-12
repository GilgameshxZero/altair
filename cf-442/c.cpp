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

long long ans = 0;
int n, l, r, x[500002], Next[500002], Last[500002];
priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n;
	for (int a = 1;a <= n;a++)
	{
		cin >> x[a];
		Next[a] = a + 1;
		Last[a] = a - 1;
		pq.push (make_pair (x[a], a));
	}

	int rem = n, cur = 0;
	while (pq.size () > 2)
	{
		pair<int, int> pii = pq.top (); 
		pq.pop ();

		ans += (rem - 2) * (pii.first - cur);
		cur = pii.first;
		rem--;

		int nu = Next[pii.second], lu = Last[pii.second];

		if(nu == n + 1 || lu == 0)
			continue;

		ans += max (0, min (x[lu], x[nu]) - cur);
		Next[lu] = nu;
		Last[nu] = lu;
	}

	cout << ans << "\n";

	return 0;
}