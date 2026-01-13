#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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

	LL N;
	cin >> N;

	LL O{0}, x;
	RF(i, 0, N) {
		if (i == O) {
			continue;
		}
		cout << "? " << O + 1 << ' ' << i + 1 << endl;
		cin >> O;
		O--;
	}

	vector<LL> Z, Y;
	RF(i, 0, N) {
		Y.push_back(i);
	}
	while (Y.size() > 1) {
		LL C{Y[0]};
		if (C == O) {
			C = Y[1];
		}
		vector<LL> X;
		RF(i, 0, Y.size()) {
			if (Y[i] == C) {
				continue;
			}
			if (Y[i] == O) {
				X.push_back(O);
				continue;
			}
			cout << "? " << C + 1 << ' ' << Y[i] + 1 << endl;
			cin >> x;
			x--;
			if (x == O) {
				X.push_back(Y[i]);
			} else {
				C = x;
			}
		}
		Z.push_back(C);
		swap(X, Y);
	}
	cout << "! " << Z.size() << ' ';
	RF(i, 0, Z.size()) {
		cout << Z[i] + 1 << ' ';
	}
	cout << endl;

	return 0;
}
