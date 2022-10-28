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

	int t;
	cin >> t;

	for (int a = 0; a < t; a++) {
		int n, l;
		cin >> n >> l;

		vector<int> res(l);
		int left = n;
		for (int b = 0; b < l; b++) {
			cin >> res[b];
			left -= res[b];
		}

		int first = -1;
		for (int b = 0; b < n; b++) {
			if ((double) 100 * b / n - 100 * b / n >= 0.5) {
				first = b;
				break;
			}
		}

		if (first == -1) {
			cout << "Case #" << a + 1 << ": " << 100 << "\n";
			continue;
		}

		vector<int> ton(n);
		ton[n-1] = (first + 1) % n;
		int last = ton[n - 1];
		for (int b = n - 2; b >= 0; b--) {
			if ((double) 100 * b / n - 100 * b / n >= 0.5) {
				last = 0;
				ton[b] = 0;
			} else
				ton[b] = ++last;
		}
		ton.push_back(ton[0]);

		vector<pair<int, int>> mins(left / ton[0] + 1, make_pair(ton[0], -1));
		for (int b = 0; b < res.size(); b++) {
			mins.push_back(make_pair(ton[res[b]], b));
		}

		sort(mins.begin(), mins.end());
		int total = 0;
		for (int b = 0; b < mins.size(); b++) {
			if (mins[b].first > left)
				break;
			left -= mins[b].first;
			if (mins[b].second == -1)
				total += round((double) 100 * (mins[b].first) / n);
			else {
				total += round((double) 100 * (res[mins[b].second] + mins[b].first) / n);
				res[mins[b].second] = -1;
			}
		}

		if (left != 0)
			res.push_back(left);

		for (int b = 0; b < res.size(); b++) {
			if (res[b] == -1)
				continue;
			total += round((double) 100 * res[b] / n);
		}

		cout << "Case #" << a + 1 << ": " << total << "\n";
	}

	return 0;
}