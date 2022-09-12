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

	int x, y;
	x = 24 * 60, y = 0;
	int i, j;
	cin >> i;
	cin.get ();
	cin >> j;
	x += i * 60 + j;
	cin >> i;
	cin.get ();
	cin >> j;
	y = i * 60 + j;
	x -= y;
	x %= 24 * 60;
	if (x / 60 < 10)
		cout << "0";
	cout << x / 60 << ":";
	if (x % 60 < 10)
		cout << "0";
	cout << x % 60 << "\n";

	return 0;
}