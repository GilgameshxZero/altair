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

	ll N, M;
	cin >> N >> M;

	ll p2[51];
	p2[1] = 1;
	for (int a = 2;a < 51;a++)
		p2[a] = 2 * p2[a - 1];

	int fr = 0, bk = N - 1, arr[51];
	M--;
	for (int a = N - 2;a >= 0;a--)
	{
		if (M & (1 << a))
			arr[bk--] = N - a - 1;
		else
			arr[fr++] = N - a - 1;
	}

	arr[fr] = N;

	for (int a = 0;a < N;a++)
		cout << arr[a] << " ";

	return 0;
}