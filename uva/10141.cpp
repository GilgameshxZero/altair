#define _CRT_SECURE_NO_WARNINGS

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
	freopen ("input0.in", "r", stdin);
	freopen ("output.out", "w", stdout);
#endif

	int cnt = 1;
	while (true)
	{
		int n, p;
		cin >> n >> p;

		if (n == p && n == 0)
			break;

		string tmp;
		getline (cin, tmp);
		for (int a = 0;a < n;a++)
			getline (cin, tmp);

		vector<string> name;
		vector<double> price;
		vector<int> met;
		int best = 0;
		for (int a = 0;a < p;a++)
		{
			name.push_back ("");
			getline (cin, name.back ());
			price.push_back (0);
			cin >> price.back ();
			met.push_back (0);
			cin >> met.back ();
			getline (cin, tmp);
			for (int b = 0;b < met.back ();b++)
				getline (cin, tmp);

			if (met.back () > met[best])
				best = a;
			else if (met.back () == met[best])
			{
				if (price.back () < price[best])
					best = a;
			}
		}

		if (cnt != 1)
			cout << "\n";
		cout << "RFP #" << cnt++ << '\n' << name[best] << '\n';
	}

	return 0;
}