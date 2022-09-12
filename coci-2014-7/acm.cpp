#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> diff[3];

int main ()
{
	freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);

	cin >> N;
	for (int a = 0;a < 3;a++)
	{
		diff[a].resize (N);
		for (int b = 0;b < N;b++)
			cin >> diff[a][b];
	}

	vector<int> pdiff (N + 1), ndiff (N + 1), perm (3);
	
	for (int a = 0;a < 3;a++)
		perm[a] = a;

	int ans = 10000000000;

	for (int a = 0;a < 6;a++)
	{
		pdiff[N] = 0;
		for (int b = N - 1;b >= 0;b--)
			pdiff[b] = pdiff[b + 1] + diff[perm[2]][b];

		ndiff[N - 2] = diff[perm[1]][N - 2] + diff[perm[2]][N - 1];
		for (int b = N - 3;b >= 0;b--)
			ndiff[b] = min (ndiff[b + 1] + diff[perm[1]][b], diff[perm[1]][b] + pdiff[b + 1]);

		int prop = 1000000000, psum = 0;
		for (int b = 0;b < N - 2;b++)
			psum += diff[perm[0]][b],
			prop = min (prop, psum + ndiff[b + 1]);

		ans = min (prop, ans);

		next_permutation (perm.begin (), perm.end ());
	}

	cout << ans << "\n";

	return 0;
}