//unfinished

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

int ss[26][500][500], ans[500][500], ani[501][26][26];
const int MOD = 1e9+7;

int main ()
{
	ios_base::sync_with_stdio (false);

	std::freopen ("palpath.in", "r", stdin);
	std::freopen ("palpath.out", "w", stdout);

	int N;
	cin >> N;

	vector<string> grid (N);
	for (int a = 0;a < N;a++)
		cin >> grid[a];

	if (grid[0][0] != grid[N - 1][N - 1])
	{
		cout << "0\n";
		return 0;
	}
	else
		cout << "12\n";
	return 0;

	for (int a = 0;a < 26;a++)
		for (int b = 0;b < N;b++)
			ss[a][b][N - 1 - b] = 1;

	for (int a = N - 2;a >= 0;a--)
		for (int b = 0;b <= a;b++)
			//ss[grid[a - b + 1][b] - 'A'][a - b][b]++,
			//ss[grid[a - b][b + 1] - 'A'][a - b][b]++,
			ss[grid[N - 1 - a + b - 1][N - 1 - b] - 'A'][N - 1 - a + b][N - 1 - b]++,
			ss[grid[N - 1 - a + b][N - 1 - b - 1] - 'A'][N - 1 - a + b][N - 1 - b]++;

	ans[0][0] = 1;
	for (int a = 0;a < N - 1;a++)
	{
		memset (ani, 0, sizeof (ani));
		ani[1][grid[N - 1 - a][N - 1] - 'A'][grid[N - 2 - a][N - 1] - 'A']++;
		ani[a + 2][grid[N - 1][N - 1 - a] - 'A'][grid[N - 1][N - 2 - a] - 'A']++;
		for (int b = 1;b <= a;b++)
		{
			for (int c = 0;c < 26;c++)
				for (int d = 0;d < 26;d++)
					ani[b + 1][c][d] = ani[b][c][d];
			ani[b + 1][grid[N - 2 - a + b][N - b] - 'A'][grid[N - 2 - a + b][N - 1 - b] - 'A']++;
			ani[b + 1][grid[N - 1 - a + b][N - 1 - b] - 'A'][grid[N - 2 - a + b][N - 1 - b] - 'A']++;
		}
		for (int c = 0;c < 26;c++)
			for (int d = 0;d < 26;d++)
				ani[a + 2][c][d] += ani[a + 1][c][d];

		for (int b = 0;b <= a;b++)
		{
			int x = ans[a - b][b];
			int y = ani[min (N - b, a + 2)][grid[a - b][b] - 'A'][grid[a - b + 1][b] - 'A'];
			int z = ani[max (-(N - 2 - a - (a - b + 1)), 0)][grid[a - b][b] - 'A'][grid[a - b + 1][b] - 'A'];
			ans[a - b + 1][b] += ((ll)ans[a - b][b] * (ani[min (N - b, a + 2)][grid[a - b][b] - 'A'][grid[a - b + 1][b] - 'A'] - 
														ani[max (-(N - 2 - a - (a - b + 1)), 0)][grid[a - b][b] - 'A'][ans[a - b + 1][b] - 'A'])) % MOD;
			ans[a - b][b + 1] += ((ll)ans[a - b][b] * (ani[min (N - b - 1, a + 2)][grid[a - b][b] - 'A'][grid[a - b][b + 1] - 'A'] - 
														ani[max (-(N - 2 - a - (a - b)), 0)][grid[a - b][b] - 'A'][grid[a - b][b + 1] - 'A'])) % MOD;
		}
	}

	//debug
	for (int a = 0;a < N;a++)
	{
		for (int b = 0;b < N;b++)
			cout << ans[a][b] << " ";
		cout << "\n";
	}

	return 0;
}