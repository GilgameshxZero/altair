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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;
		vector<LL> A(N), B(N), C(N);
		RF(i, 0, N) {
			cin >> A[i];
			A[i] %= K;
		}
		B[0] = C[0] = A[0];
		RF(i, 1, N) {
			B[i] = (K + A[i] - A[i - 1]) % K;
			C[i] = C[i - 1] + B[i];
		}

		LL Z{C.back()};
		RF(i, 0, N) {
			C[i] /= K;
		}

		multiset<LL> F;
		RF(i, 0, N) {
			LL j{i};
			for (; j < N && C[j] == C[i]; j++)
				;

			if (C[i] != 0) {
				sort(B.begin() + i, B.begin() + j);
				RF(k, j - 1, i - 1) {
					if (j - k > C[i]) {
						break;
					}
					F.insert(B[k]);
					if (F.size() > C[i]) {
						F.erase(F.begin());
					}
				}
			}

			i = j - 1;
		}

		for(auto &i : F) {
			Z -= i;
		}
		cout << Z << '\n';
	}

	return 0;
}
