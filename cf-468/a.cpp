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

	int n;
	cin >> n;

	if (n < 4)
		cout << "NO\n";
	else if ((n & 1) == 0)
	{
		cout << "YES\n"
			<< "1 + 2 = 3\n"
			<< "3 + 3 = 6\n"
			<< "6 * 4 = 24\n";
		for (int a = 5;a <= n;a += 2)
			cout << a + 1 << " - " << a << " = 1\n" << "24 * 1 = 24\n";
	}
	else
	{
		cout << "YES\n"
			<< "5 + 4 = 9\n"
			<< "9 - 2 = 7\n"
			<< "7 + 1 = 8\n"
			<< "3 * 8 = 24\n";
		for (int a = 6;a <= n;a += 2)
			cout << a + 1 << " - " << a << " = 1\n" << "24 * 1 = 24\n";
	}

	return 0;
}