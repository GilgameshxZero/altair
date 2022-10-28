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

	string str;
	ll n, cur, cpos = 0, cneg = 0;
	vector<int> sign, num;

	sign.push_back (1);
	str = "";
	cpos++;
	while (str != "=")
	{
			cin >> str;
			if (str == "?")
				num.push_back (0);
			else if (str == "-")
				sign.push_back (-1),
				cneg++;
			else if (str == "+")
				sign.push_back (1),
				cpos++;
	}

	cin >> n;
	cur = 1 * cpos - n * cneg;
	if (cur <= n && n * cpos - 1 * cneg >= n)
	{
		cout << "Possible\n";

		for (int a = 0;a < num.size ();a++)
			if (sign[a] == 1)
				num[a] = 1;
			else
				num[a] = n;

		for (int a = 0;a < num.size ();a++)
		{
			static int diff;
			diff = n - cur;
			if (sign[a] == 1)
			{
				if (diff > n - 1)
					num[a] = n,
					cur += n - 1;
				else
				{
					num[a] = 1 + diff;
					break;
				}
			}
			else
			{
				if (diff > n - 1)
					num[a] = 1,
					cur += n - 1;
				else
				{
					num[a] = n - diff;
					break;
				}
			}
		}

		cout << num[0] << ' ';
		for (int a = 1;a < num.size ();a++)
		{
			if (sign[a] == 1)
				cout << "+ ";
			else
				cout << "- ";
			cout << num[a] << ' ';
		}
		cout << "= " << n;
	}
	else
		cout << "Impossible";

	return 0;
}