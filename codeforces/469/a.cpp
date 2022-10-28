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

	int n, x, y;
	bitset<100> pass;

	cin >> n;
	pass.reset ();

	cin >> x;
	for (int a = 0, b;a < x;a++)
		cin >> b,
		pass[--b] = true;
	cin >> y;
	for (int a = 0, b;a < y;a++)
		cin >> b,
		pass[--b] = true;

	for (int a = 0;a < n;a++)
		if (pass[a] == false)
		{
			cout << "Oh, my keyboard!\n";
			return 0;
		}
	cout << "I become the guy.";

	return 0;
}