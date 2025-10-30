#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

auto transpose(vector<string> &G) {
	auto N{G.size()};
	RF(i, 0, N) {
		RF(j, i + 1, N) {
			swap(G[i][j], G[j][i]);
		}
	}
}

auto hflip(vector<string> &G) {
	auto N{G.size()};
	RF(i, 0, N) {
		RF(j, 0, N / 2) {
			swap(G[i][j], G[i][N - j - 1]);
		}
	}
}

auto check(vector<string> &G, LL target) {
	auto N{G.size()};
	RF(i, 0, N - 1) {
		LL c{0};
		RF(j, 0, N - i - 1) {
			c += G[j][i + j] == '#';
			c += G[j][i + j + 1] == '#';
		}
		c += G[N - i - 1][N - 1] == '#';
		if (c == target) {
			return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<string> G(N);
		LL CB{0};
		RF(i, 0, N) {
			cin >> G[i];
			RF(j, 0, N) {
				CB += G[i][j] == '#';
			}
		}
		if (N <= 2) {
			cout << "YES\n";
			continue;
		}

		bool fail{true};
		RF(i, 0, N - 1) {
			RF(j, 0, N - 1) {
				LL cb{0};
				RF(k, 0, 2) {
					RF(l, 0, 2) {
						cb += G[i + k][j + l] == '#';
					}
				}
				if (cb == CB) {
					fail = false;
				}
			}
		}
		if (!fail) {
			cout << "YES\n";
			continue;
		}

		fail &= check(G, CB);
		transpose(G);
		fail &= check(G, CB);
		transpose(G);

		hflip(G);
		fail &= check(G, CB);
		transpose(G);
		fail &= check(G, CB);
		transpose(G);
		hflip(G);

		transpose(G);
		hflip(G);
		fail &= check(G, CB);
		transpose(G);
		fail &= check(G, CB);
		transpose(G);
		hflip(G);
		transpose(G);

		hflip(G);
		transpose(G);
		hflip(G);
		fail &= check(G, CB);
		transpose(G);
		fail &= check(G, CB);
		transpose(G);
		hflip(G);
		transpose(G);
		hflip(G);

		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
