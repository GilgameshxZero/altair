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

int main ()
{
	ios_base::sync_with_stdio (false);

	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	int n;
	cin >> n;

	while (n != 0)
	{
		double sum = 0, buy[1000];
		for (int a = 0;a < n;a++)
		{
			cin >> buy[a];
			sum += buy[a];
		}

		double ave = (double)sum / n;
		double diff = 0, neg = 0, pos = 0;
		for (int a = 0;a < n;a++)
		{
			double v = ((int)(((double)buy[a] - ave) * 100)) / 100.0;
			if (v < 0)
				neg += -v;
			else
				pos += v;
		}

		diff = (neg > pos) ? neg : pos;
		cout << "$" << fixed << setprecision (2) << diff << "\n";
		cin >> n;
	}

	return 0;
}