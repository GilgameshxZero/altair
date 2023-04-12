#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		vector<vector<LL>> E(N);
		RF(i, 0, M) {
			LL U, V;
			cin >> U >> V;
			E[U - 1].push_back(V - 1);
			E[V - 1].push_back(U - 1);
		}

		LL K(sqrt(N));
		while (K * K < N) {
			K++;
		}
		while (K * K > N) {
			K--;
		}
		if (N != K * K || M != K * K + K) {
			cout << "NO\n";
			continue;
		}

		vector<LL> D2, D4;
		bool possible{true};
		RF(i, 0, N) {
			if (E[i].size() == 2) {
				D2.push_back(i);
			} else if (E[i].size() == 4) {
				D4.push_back(i);
			}
		}
		possible &= D2.size() == K * K - K;
		possible &= D4.size() == K;
		if (!possible) {
			cout << "NO\n";
			continue;
		}

		LL cur{D4[0]}, prev{-1}, c4c{0};
		vector<bool> vis(N, false);
		do {
			if (vis[cur]) {
				possible = false;
				break;
			}
			vis[cur] = true;
			c4c++;

			vector<LL> cd2;
			LL next;
			for (auto &i : E[cur]) {
				if (E[i].size() != 4) {
					cd2.push_back(i);
					continue;
				}
				if (i == prev) {
					continue;
				}
				next = i;
			}
			if (cd2.size() != 2) {
				possible = false;
				break;
			}

			LL cur2{cd2[0]}, prev2{cur}, c2c{0};
			do {
				if (vis[cur2]) {
					possible = false;
					break;
				}
				vis[cur2] = true;
				c2c++;

				LL next2;
				for (auto &i : E[cur2]) {
					if (i == prev2) {
						continue;
					}
					next2 = i;
				}
				if (next2 == cur) {
					break;
				}
				if (E[next2].size() != 2) {
					possible = false;
					break;
				}
				prev2 = cur2;
				cur2 = next2;
			} while (true);
			possible &= c2c == K - 1;
			if (!possible) {
				break;
			}

			prev = cur;
			cur = next;
		} while (cur != D4[0]);
		possible &= c4c == K;

		cout << (possible ? "YES" : "NO") << '\n';
	}

	return 0;
}
