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

	std::freopen ("taxi.in", "r", stdin);
	std::freopen ("taxi.out", "w", stdout);

	int N, M;
	cin >> N >> M;

	vector<int> cd (N * 2);
	for (int a = 0;a < N;a++)
		cin >> cd[a * 2] >> cd[a * 2 + 1];

	sort (cd.begin (), cd.end ());
	ll ans = 0;
	for (int a = 0;a < 2 * N - 2;a++)
		ans += cd[a + 2] - cd[a] + cd[a + 2] - cd[a + 1];
	ans -= cd[2 * N - 1] - cd[2 * N - 2];
	ans += M - cd[2 * N - 1];
	cout << ans << "\n";

	return 0;
}