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

	LL N;
	cin >> N;
	if (N % 4 == 1 || N % 4 == 2) {
		cout << "NO\n";
		return 0;
	}

	cout << "YES\n";
	vector<LL> S[2];
	if (N % 4 == 0) {
		RF(i, 0, N / 4) {
			S[0].push_back(i * 2 + 1);
			S[0].push_back(N - (2 * i));
			S[1].push_back(N - (2 * i + 1));
			S[1].push_back(2 * i + 2);
		}
	} else {
		RF(i, 0, (N - 3) / 4) {
			S[0].push_back(i * 2 + 4);
			S[0].push_back(N - (2 * i));
			S[1].push_back(N - (2 * i + 1));
			S[1].push_back(2 * i + 5);
		}
		S[0].push_back(1);
		S[0].push_back(2);
		S[1].push_back(3);
	}
	cout << S[0].size() << '\n';
	RF(j, 0, S[0].size()) {
		cout << S[0][j] << ' ';
	}
	cout << '\n' << S[1].size() << '\n';
	RF(j, 0, S[1].size()) {
		cout << S[1][j] << ' ';
	}

	return 0;
}
