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
		int N;
		cin >> N;

		vector<vector<int>> grid(N, vector<int>(N));
		for (int b = 0; b < N; b++) {
			for (int c = 0; c < N; c++) {
				cin >> grid[b][c];
			}
		}

		map<pair<int, int>, int> node;
		vector<set<int>> edge;
		int cedge = 0;
		for (int b = 0; b < N; b++) {
			for (int c = 0; c < N; c++) {
				for (int d = 0; d < N; d++) {
					if (d != c && grid[b][c] == grid[b][d]) {
						auto it1 = node.find(make_pair(b, c)),
							it2 = node.find(make_pair(b, d));
						if (it1 == node.end())
							node.insert(make_pair(make_pair(b, c), node.size()));
						if (it2 == node.end())
							node.insert(make_pair(make_pair(b, d), node.size()));
						it1 = node.find(make_pair(b, c)),
						it2 = node.find(make_pair(b, d));
						edge.resize(node.size());
						edge[it1->second].insert(it2->second);
						cedge++;
					}
					if (d != b && grid[b][c] == grid[d][c]) {
						auto it1 = node.find(make_pair(b, c)),
							it2 = node.find(make_pair(d, c));
						if (it1 == node.end())
							node.insert(make_pair(make_pair(b, c), node.size()));
						if (it2 == node.end())
							node.insert(make_pair(make_pair(d, c), node.size()));
						it1 = node.find(make_pair(b, c)),
							it2 = node.find(make_pair(d, c));
						edge.resize(node.size());
						edge[it1->second].insert(it2->second);
						cedge++;
					}
				}
			}
		}

		cedge /= 2;

		int ans = 0;
		while (cedge > 0) {
			int leaf = -1;
			for (int b = 0; b < edge.size(); b++) {
				if (edge[b].size() > 0 && (leaf == -1 || edge[b].size() < edge[leaf].size()))
					leaf = b;
			}

			int rem = *edge[leaf].begin();
			for (auto it = edge[rem].begin();it != edge[rem].end();it++) {
				edge[*it].erase(rem);
				cedge--;
			}

			edge[rem].clear();
			ans++;
		}

		cout << "Case #" << a + 1 << ": " << ans << "\n";
	}

	return 0;
}