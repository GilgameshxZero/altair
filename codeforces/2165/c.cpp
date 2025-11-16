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
		LL N, Q;
		cin >> N >> Q;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.end());
		RF(i, 0, Q) {
			LL X;
			cin >> X;
			priority_queue<LL> R;
			LL NA{N - 1}, Z{0};
			RF(j, 31, -1) {
				if (X & (1LL << j)) {
					LL C{0};
					if (R.empty() && NA < 0) {
						C = 0;
					} else if (R.empty()) {
						C = A[NA--];
					} else if (NA < 0) {
						C = R.top();
						R.pop();
					} else {
						if (R.top() >= A[NA]) {
							C = R.top();
							R.pop();
						} else {
							C = A[NA--];
						}
					}
					if (C <= (1LL << j)) {
						Z += (1LL << j) - C;
					} else if ((1LL << (j + 1)) <= C) {
						break;
					} else {
						R.push(C ^ (1LL << j));
					}
				}
			}
			cout << Z << '\n';
		}
	}

	return 0;
}
