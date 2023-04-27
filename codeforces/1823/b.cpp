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
		LL N, K;
		cin >> N >> K;

		vector<LL> A(N);
		vector<vector<LL>> B(K);
		RF(i, 0, N) {
			cin >> A[i];
			B[i % K].push_back(A[i]);
		}
		RF(i, 0, K) {
			sort(B[i].begin(), B[i].end());
			reverse(B[i].begin(), B[i].end());
		}

		bool swapped{false}, fail{false};
		RF(i, 0, N) {
			if (B[i % K].back() == i + 1) {
				B[i % K].pop_back();
			} else if (!swapped) {
				swapped = true;
				LL toSwap(B[i % K].size() - 1);
				RF(j, 0, B[i % K].size()) {
					if (B[i % K][j] % K != (i + 1) % K) {
						toSwap = j;
						break;
					}
				}
				RF(j, 0, K) {
					RF(k, 0, B[j].size()) {
						if (B[j][k] == i + 1) {
							swap(B[i % K][toSwap], B[j][k]);
							sort(B[j].begin(), B[j].end());
							reverse(B[j].begin(), B[j].end());
							sort(B[i % K].begin(), B[i % K].end());
							reverse(B[i % K].begin(), B[i % K].end());
						}
					}
				}
				B[i % K].pop_back();
			} else {
				fail = true;
				break;
			}
		}
		if (fail) {
			cout << "-1\n";
		} else if (swapped) {
			cout << "1\n";
		} else {
			cout << "0\n";
		}
	}

	return 0;
}
