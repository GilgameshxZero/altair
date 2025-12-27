#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, M;
		cin >> N >> M;
		vector<pair<LL, LL>> E(N);
		RF(i, 0, N) {
			cin >> E[i].first;
			E[i].second = i;
		}
		sort(E.begin(), E.end());
		if (M > N / 2) {
			cout << "-1\n";
			continue;
		}
		vector<pair<LL, LL>> Z;
		if (M == 0) {
			LL R{0};
			while (R < N - 1 &&
						 E.back().first > E[N - 2].first) {
				Z.push_back({E[R].second, E.back().second});
				E.back().first -= E[R].first;
				R++;
			}
			if (R == N - 1) {
				cout << "-1\n";
				continue;
			}
			RF(i, R, N - 1) {
				Z.push_back({E[i].second, E[i + 1].second});
			}
		} else {
			LL R{0};
			if (N % 2 == 1) {
				Z.push_back({E[0].second, E[1].second});
				R++;
			}
			while (M * 2 < N - R) {
				Z.push_back({E[R].second, E[R + 1].second});
				R++;
			}
			for (LL i{R}; i < N; i += 2) {
				Z.push_back({E[i + 1].second, E[i].second});
			}
		}
		cout << Z.size() << '\n';
		RF(i, 0, Z.size()) {
			cout << Z[i].first + 1 << ' ' << Z[i].second + 1
					 << '\n';
		}
	}

	return 0;
}
