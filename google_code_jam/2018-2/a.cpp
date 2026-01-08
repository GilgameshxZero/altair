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

int main() {
	ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
	freopen("input0.in", "r", stdin);
	freopen("output.out", "w", stdout);
#endif

	int T;
	cin >> T;
	for (int a = 0; a < T; a++) {
		int C;
		cin >> C;

		cout << "Case #" << a + 1 << ": ";

		vector<int> balls(C);
		for (int b = 0; b < C; b++)
			cin >> balls[b];

		if (balls[0] == 0 || balls.back() == 0) {
			cout << "IMPOSSIBLE\n";
			continue;
		}

		vector<vector<char>> grid(C - 1, vector<char>(C, '.'));
		vector<int> pres(C);
		pres[0] = balls[0];
		for (int b = 1; b < C; b++)
			pres[b] = pres[b - 1] + balls[b];

		vector<int> ed(C);
		for (int b = 0; b < C; b++) {
			for (int c = 0; c < C; c++) {
				if (pres[c] >= b + 1) {
					ed[b] = c;
					break;
				}
			}
		}

		for (int b = 0; b < C; b++) {
			if (b > ed[b]) {
				int diff = b - ed[b];
				for (int c = 0; c < diff; c++) {
					grid[c][b - c] = '/';
				}
			} else {
				int diff = ed[b] - b;
				for (int c = 0; c < diff; c++) {
					grid[c][b + c] = '\\';
				}
			}
		}

		for (int b = grid.size() - 1; b >= 0; b--) {
			bool flag = true;
			for (int c = 0; c < grid[b].size(); c++) {
				if (grid[b][c] != '.') {
					flag = false;
					break;
				}
			}

			if (flag)
				grid.pop_back();
		}

		grid.push_back(vector<char>(C, '.'));
		cout << grid.size() << "\n";

		for (int b = 0; b < grid.size(); b++) {
			for (int c = 0; c < grid[b].size(); c++) {
				cout << grid[b][c];
			}
			cout << "\n";
		}
	}

	return 0;
}