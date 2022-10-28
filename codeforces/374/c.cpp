#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int n, m, cnt[1000][1000], id[1000][1000], cid, ans;
char grid[1000][1000];

int DFS(int x, int y, int pid) {
	if (id[x][y] == pid) return 1 << 29;
	if (cnt[x][y] != -1) return cnt[x][y];

	id[x][y] = pid;
	char nlet;
	if (grid[x][y] == 'D') nlet = 'I';
	if (grid[x][y] == 'I') nlet = 'M';
	if (grid[x][y] == 'M') nlet = 'A';
	if (grid[x][y] == 'A') nlet = 'D';

	int r = 1;
	if (x > 0 && grid[x - 1][y] == nlet) r = max(r, 1 + DFS(x - 1, y, pid));
	if (y > 0 && grid[x][y - 1] == nlet) r = max(r, 1 + DFS(x, y - 1, pid));
	if (x < n - 1 && grid[x + 1][y] == nlet) r = max(r, 1 + DFS(x + 1, y, pid));
	if (y < m - 1 && grid[x][y + 1] == nlet) r = max(r, 1 + DFS(x, y + 1, pid));
	id[x][y] = 0;

	return cnt[x][y] = r;
}

int main() {
	ios_base::sync_with_stdio(false);

#ifndef ONLINE_JUDGE
	freopen("../build/i.default.txt", "r", stdin);
	freopen("../build/o.default.txt", "w", stdout);
#endif

	memset(cnt, -1, sizeof(cnt));

	cin >> n >> m;
	for (int a = 0; a < n; a++) {
		cin.get();
		for (int b = 0; b < m; b++) grid[a][b] = cin.get();
	}

	for (int a = 0; a < n; a++)
		for (int b = 0; b < m; b++)
			if (grid[a][b] == 'D') {
				ans = max(ans, DFS(a, b, ++cid));
			}

	if (ans >= 1 << 29)
		cout << "Poor Inna!\n";
	else if (ans < 4)
		cout << "Poor Dima!\n";
	else
		cout << ans / 4 << "\n";

	return 0;
}
