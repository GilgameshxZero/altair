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
		LL N;
		cin >> N;
		map<LL, LL> M;
		LL S{0};
		RF(i, 0, N) {
			LL x;
			cin >> x;
			M[x]++;
			S += x;
		}
		LL D{0};
		vector<LL> X;
		X.push_back(0);
		for (auto &i : M) {
			if ((i.first - (X.size() - 1)) % 2 == 0) {
				X.back() += i.second;
			} else {
				X.push_back(i.second);
			}
		}

		LL B{1};
		vector<LL> Y;
		Y.push_back(X.size() - 1);
		RF(i, X.size() - 2, -1) {
			if (X[i] > X[Y.back()]) {
				Y.push_back(i);
			}
		}
		Y.push_back(0);

		RF(i, Y.size() - 2, -1) {
			LL A{X[Y[i]]};
			RF(j, Y[i], Y[i + 1]) {
				D += B * A;
				B *= -1;
				A += X[j];
			}
		}
		// cout << (S - D) / 2 << ' ' << (S - D) / 2 + D << '\n';
		RF(i, 0, X.size()) {
			cout << X[i] << ' ';
		}
		cout << '\n';
	}

	return 0;
}
