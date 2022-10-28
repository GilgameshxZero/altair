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

	freopen ("input0.txt", "r", stdin); freopen ("output.txt", "w", stdout);

	int T;
	cin >> T;

	for (int a = 0;a < T;a++)
	{
		ll X, Y, Z, B, W;
		cin >> B >> W >> X >> Y >> Z;
		X = min (X, Y + Z);
		Y = min (Y, X + Z);
		cout << B * X + W * Y << "\n";
	}

	return 0;
}