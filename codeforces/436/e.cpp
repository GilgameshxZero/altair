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

vector< pair<int, int> > one, two;
long long sum = 0, minsum, minx, miny;
int n, w, x, y, stat[300000];

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	cin >> n >> w;
	for (int a = 0, b, c;a < n;a++)
	{
		cin >> b >> c;
		one.push_back (make_pair (b, a));
		two.push_back (make_pair (c, a));
	}


	return 0;
}