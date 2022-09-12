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

	int n, box[100], cnt = 0, k = 0;
	cin >> n;
	for (int a = 0;a < n;a++)
		cin >> box[a];
	sort (box, box + n);
	while (cnt != n)
	{
		k++;
		int w = 0;
		for (int a = 0;a < n;a++)
		{
			if (box[a] != -1 && box[a] >= w)
				box[a] = -1,
				cnt++,
				w++;
		}
	}

	cout << k << "\n";

	return 0;
}