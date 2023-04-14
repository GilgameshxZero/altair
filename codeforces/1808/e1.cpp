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

array<array<array<LL, 3001>, 100>, 30> B;
array<bool, 30> done;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, K, M;
	cin >> N >> K >> M;

	LL ans{0};
	vector<LL> digs;
	done.fill(false);
	RF(S, 0, N * (K - 1) + 1) {
		LL sk{S % K};
		if (done[sk]) {
			ans = (ans + B[sk][N - 1][S]) % M;
			continue;
		}
		done[sk] = true;

		digs.clear();
		RF(i, 0, K) {
			if (2 * i % K != sk) {
				digs.push_back(i);
			}
		}

		B[sk][0].fill(0);
		RF(i, 0, digs.size()) {
			if (digs[i] > N * (K - 1)) {
				break;
			}
			B[sk][0][digs[i]] = 1;
		}
		RF(i, 1, N) {
			RF(j, 0, N * (K - 1) + 1) {
				B[sk][i][j] = 0;
				RF(k, 0, digs.size()) {
					if (digs[k] > j) {
						break;
					}
					B[sk][i][j] = (B[sk][i][j] + B[sk][i - 1][j - digs[k]]) % M;
				}
			}
		}

		ans = (ans + B[sk][N - 1][S]) % M;
	}

	LL total{1};
	RF(i, 0, N) {
		total = total * K % M;
	}
	cout << (M + total - ans) % M;

	return 0;
}
