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

	string n;
	cin >> n;

	for (int a = 0; a < n.length();a++)
		if (n[a] == '0')
		{
			cout << "YES\n0";
			return 0;
		}
		else if (n[a] == '8')
		{
			cout << "YES\n8";
			return 0;
		}

	for (int b = 0; b < n.length(); b++)
	{
		for (int c = b + 1; c < n.length(); c++)
		{
			int x = (n[b] - '0') * 10 + n[c] - '0';
			if (x % 8 == 0)
			{
				cout << "YES\n" << x;
				return 0;
			}
		}
	}

	for (int a = 0; a < n.length(); a++)
	{
		for (int b = a + 1; b < n.length(); b++)
		{
			for (int c = b + 1; c < n.length(); c++)
			{
				int x = (n[a] - '0') * 100 + (n[b] - '0') * 10 + n[c] - '0';
				if (x % 8 == 0)
				{
					cout << "YES\n" << x;
					return 0;
				}
			}
		}
	}

	cout << "NO";

	return 0;
}