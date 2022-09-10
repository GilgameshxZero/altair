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

	while (true)
	{
		ll H, U, D, F;
		cin >> H >> U >> D >> F;

		if (H == 0)
			break;

		ll a;
		double cur = 0, cli = U;
		for (a = 1;;a++)
		{
			cur += cli;
			cli -= F / 100.0 * U;
			cli = max (0.0, cli);

			if (cur > H)
				break;

			cur -= D;
			if (cur < 0)
				break;
		}

		if (cur > H)
			cout << "success on day " << a << '\n';
		else
			cout << "failure on day " << a << '\n';
	}
	
	return 0;
}