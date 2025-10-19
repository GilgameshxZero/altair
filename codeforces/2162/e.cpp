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
		vector<LL> A(N), C(N + 1);
		set<LL> S;
		RF(i, 0, N) {
			S.insert(i + 1);
		}
		RF(i, 0, N) {
			cin >> A[i];
			C[A[i]]++;
			S.erase(A[i]);
		}
		RF(i, 0, K) {
			if (S.empty()) {
				cout << A[i] << ' ';
			} else {
				cout << *S.begin() << ' ';
				C[*S.begin()]++;
				S.erase(S.begin());
				C[A[i]]--;
				if (C[A[i]] == 0) {
					S.insert(A[i]);
				}
			}
		}
		cout << '\n';
	}

	return 0;
}
