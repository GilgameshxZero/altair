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
		LL N;
		cin >> N;
		vector<vector<LL>> Q(N);
		LL P;
		cin >> P;
		RF(i, 0, N - 1) {
			LL X;
			cin >> X;
			Q[abs(X - P)].push_back(i);
			P = X;
		}
		set<LL> X;
		X.insert({-1, N - 1});
		LL Z{(N - 1) * (N - 2) / 2 + N - 1};
		RF(i, 1, N) {
			cout << Z << ' ';
			for (auto &j : Q[i]) {
				// cout << "(" << j << ")" << ' ';
				auto jj{X.upper_bound(j)}, jjj{jj};
				jj--;
				// cout << "[" << *jj << "," << *jjj << "] ";
				LL d(*jjj - *jj - 1);
				Z -= d * (d - 1) / 2 + d;
				X.emplace_hint(jj, j);
				d = j - *jj - 1;
				Z += d * (d - 1) / 2 + d;
				d = *jjj - j - 1;
				Z += d * (d - 1) / 2 + d;
			}
		}
		cout << '\n';
	}

	return 0;
}
