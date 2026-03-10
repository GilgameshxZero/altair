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
		LL N, M, L;
		cin >> N >> M >> L;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		multiset<LL> S;
		RF(i, 0, M) {
			S.insert(0);
		}
		reverse(A.begin(), A.end());
		RF(i, 0, L) {
			LL target(min((LL)A.size() + 1, M));
			while ((LL)S.size() > target) {
				S.erase(S.begin());
			}
			auto j{S.begin()};
			LL k{*j};
			S.erase(j);
			S.insert(k + 1);
			if (!A.empty() && A.back() == i + 1) {
				S.erase(--S.end());
				S.insert(0);
				A.pop_back();
			}
		}
		cout << *S.rbegin() << '\n';
	}

	return 0;
}
