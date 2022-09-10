#include <algorithm>
#include <bitset>
#include <cassert>
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
#include <limits>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

char GetChar (int x)
{
	if (x < 26)
		return x + 'A';
	else
		return x - 26 + 'a';
}

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int n;
	while (cin >> n)
	{
		cout << "2 " << n << " " << n << "\n";
		for (int a = 0;a < n;a++)
		{
			for (int b = 0;b < n;b++)
				cout << GetChar (a);
			cout << "\n";
		}
		cout << "\n";
		for (int a = 0;a < n;a++)
		{
			for (int b = 0;b < n;b++)
				cout << GetChar (b);
			cout << "\n";
		}
		cout << "\n";
	}

	return 0;
}