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
	
	int T;
	cin >> T;

	for (int a = 0; a < T; a++) {
		int A;
		cin >> A;

		//cerr << A;

		int prepb[2][2], rectb[2][2];
		prepb[0][0] = 999;
		prepb[0][1] = 0;
		prepb[1][0] = 999;
		prepb[1][1] = 0;

		rectb[0][0] = 499;
		rectb[0][1] = 501;
		rectb[1][0] = 499;
		rectb[1][1] = 501;

		double center[2];
		center[0] = 500;
		center[1] = 500;

		vector<vector<int>> prepsum(1000, vector<int>(1000));
		vector<vector<bool>> prep(1000, vector<bool>(1000));

		bool fail = true;

		for (int tries = 0; tries < 1000; tries++) {
			int lowprep = prepsum[rectb[0][0] + 1][rectb[1][0] + 1], pos[2];
			pos[0] = rectb[0][0] + 1;
			pos[1] = rectb[1][0] + 1;
			for (int b = rectb[0][0] + 1; b < rectb[0][1]; b++) {
				for (int c = rectb[1][0] + 1; c < rectb[1][1]; c++) {
					if (prepsum[b][c] < lowprep || (prepsum[b][c] == lowprep && 
						abs(b - center[0]) + abs(c - center[1]) < abs(pos[0] - center[0]) + abs(pos[1] - center[1]))) {
						lowprep = prepsum[b][c];
						pos[0] = b;
						pos[1] = c;
					}
				}
			}

			cout << pos[0] + 1 << " " << pos[1] + 1 << "\n";
			cout.flush();
			//cerr << pos[0] << " " << pos[1] << "\n";

			int x, y;
			cin >> x >> y;

			if (x == 0 && y == 0) {
				fail = false;
				break;
			} else if (x == -1 && y == -1) {
				break; //error
			} else if (!prep[--x][--y]) {
				prep[x][y] = true;
				for (int b = x - 1; b <= x + 1; b++) {
					for (int c = y - 1; c <= y + 1; c++) {
						prepsum[b][c]++;
					}
				}
				//cerr << "\t" << x << " " << y << "\n";

				prepb[0][0] = min(prepb[0][0], x);
				prepb[0][1] = max(prepb[0][1], x);
				prepb[1][0] = min(prepb[1][0], y);
				prepb[1][1] = max(prepb[1][1], y);
				static const int bord = 15;
				int b = bord - (prepb[0][1] - prepb[0][0] + 1);
				int c = bord - (prepb[1][1] - prepb[1][0] + 1);
				rectb[0][0] = prepb[0][0] - b / 2;
				rectb[0][1] = rectb[0][0] + bord - 1;
				rectb[1][0] = prepb[1][0] - c / 2;
				rectb[1][1] = rectb[1][0] + bord - 1;
				center[0] = (double) (rectb[0][0] + rectb[0][1]) / 2;
				center[1] = (double) (rectb[1][0] + rectb[1][1]) / 2;

				//cerr << rectb[0][0] << " " << rectb[0][1] << " " << rectb[1][0] << " " << rectb[1][1] << "\n";
			}
		}

		if (fail)
			break;
	}

	return 0;
}