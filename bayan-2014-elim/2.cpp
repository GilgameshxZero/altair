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
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int t;
	cin >> t;
	for (int a = 1;a <= t;a++)
	{
		int i, j, k, l;
		cin >> i >> j >> k >> l;

		bool temp = (i < 35),
			beat = (j < 40),
			highbeat = (j > 60),
			still = (k < 10);

		cout << "Case #" << a << ":\n";
		if (!still)
			cout << "NOTHING";
		else if (temp || beat)
			cout << "EMERGENCY";
		else if (still && highbeat)
			cout << "NIGHTMARE";
		else if (l > 8 * 60 * 60)
			cout << "WAKE-UP";
		else
			cout << "NOTHING";

		if (a < t)
			cout << "\n";
	}

	return 0;
}