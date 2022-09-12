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

	int N;
	cin >> N;

	string s;
	cin >> s;

	for (int a = 1;a < 100;a++)
	{
		for (int b = 0;b < N;b++)
		{
			if (b + a * 4 >= N)
				break;
			bool flag = true;
			for (int c = b;c <= b + a * 4;c += a)
				if (s[c] == '.')
					flag = false;
			if (flag)
			{
				cout << "yes";
				return 0;
			}
		}
	}

	cout << "no";

	return 0;
}