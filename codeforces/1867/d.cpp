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
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
			A[i]--;
		}
		if (K == 1) {
			bool Z{true};
			RF(i, 0, N) {
				Z &= A[i] == i;
			}
			cout << (Z ? "YES" : "NO") << '\n';
			continue;
		}
		vector<bool> V(N, false);
		LL Z{true};
		RF(i, 0, N) {
			if (V[i]) {
				continue;
			}
			LL c{i};
			vector<LL> p;
			while (!V[c]) {
				p.push_back(c);
				V[c] = true;
				c = A[c];
			}
			LL x{1};
			while (p.back() != c) {
				p.pop_back();
				if (p.empty()) {
					break;
				}
				x++;
			}
			if (p.empty()) {
				continue;
			}
			if (x != K) {
				Z = false;
				break;
			}
		}
		cout << (Z ? "YES" : "NO") << '\n';
	}

	return 0;
}
