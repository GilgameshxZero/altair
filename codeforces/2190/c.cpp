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
		LL L[2]{-1, -1};
		RF(i, 1, N) {
			cout << "? " << i << ' ' << i + 1 << endl;
			LL x;
			cin >> x;
			if (x == 1) {
				L[0] = i;
				break;
			}
		}
		if (L[0] == -1) {
			cout << "! -1" << endl;
			continue;
		}
		RF(i, L[0] + 1, N) {
			cout << "? " << i << ' ' << i + 1 << endl;
			LL x;
			cin >> x;
			if (x == 0) {
				L[1] = i - 1;
				break;
			}
		}
		if (L[1] == -1) {
			cout << "! -1" << endl;
			continue;
		}

		cout << "? " << L[1] << ' ' << L[1] + 2 << endl;
		LL x;
		cin >> x;
		vector<LL> Z(N);
		RF(i, 0, N) {
			Z[i] = i;
		}
		if (x == 1) {
			Z[L[1] - 1] = L[1] + 1;
			Z[L[1]] = L[1] - 1;
			Z[L[1] + 1] = L[1];
		} else {
			Z[L[1] - 1] = L[1];
			Z[L[1]] = L[1] + 1;
			Z[L[1] + 1] = L[1] - 1;
		}
		cout << "! ";
		RF(i, 0, N) {
			cout << Z[i] + 1 << ' ';
		}
		cout << endl;
	}

	return 0;
}
