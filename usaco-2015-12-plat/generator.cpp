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

vector<ll> bales;

int main ()
{
	ios_base::sync_with_stdio (false);

	//std::freopen ("file_name.in", "r", stdin);
	std::freopen ("out.txt", "w", stdout);

	cout << 200000 << ' ' << 100000 << '\n';
	for (int a = 0; a < 200000 - 1; a++)
		cout << rand () % 100001 << ' ';
	cout << rand () % 100001 << '\n';
	for (int a = 0; a < 100000; a++)
	{
		int k = rand () % 3;
		int x = rand () % 200000 + 1, y = rand () % 200000 + 1;

		if (x > y)
			swap (x, y);
		if (k == 0)
		{
			cout << "M " << x << ' ' << y << '\n';
		}
		if (k == 1)
		{
			cout << "S " << x << ' ' << y << '\n';
		}
		if (k == 2)
		{
			cout << "P " << x << ' ' << y << ' ' << rand () % 100001 + 1 << '\n';
		}
	}

	return 0;
}