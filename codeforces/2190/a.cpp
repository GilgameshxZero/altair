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
		string S;
		cin >> N >> S;
		string T{S};
		sort(T.begin(), T.end());
		if (S == T) {
			cout << "Bob\n";
		} else {
			cout << "Alice\n";
			vector<LL> Z;
			RF(i, 0, N) {
				if (S[i] != T[i]) {
					Z.push_back(i);
				}
			}
			cout << Z.size() << '\n';
			for (auto &i : Z) {
				cout << i + 1 << ' ';
			}
			cout << '\n';
		}
	}

	return 0;
}
