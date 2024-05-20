#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		string S;
		cin >> S;
		bool U[2]{false, true}, M[2]{false, true};
		LL C[2]{0};
		string Z;
		RF(i, 0, N) {
			if (S[i] == 'N') {
				Z += U[0] ? 'R' : 'H';
				U[0] = !U[0];
				if (U[0] == M[0]) {
					M[0] = !M[0];
					U[0] = !U[0];
				}
				C[0]++;
			} else if (S[i] == 'S') {
				Z += U[0] ? 'H' : 'R';
				U[0] = !U[0];
				if (U[0] == M[0]) {
					M[0] = !M[0];
					U[0] = !U[0];
				}
				C[0]++;
			} else if (S[i] == 'E') {
				Z += U[1] ? 'R' : 'H';
				U[1] = !U[1];
				if (U[1] == M[1]) {
					M[1] = !M[1];
					U[1] = !U[1];
				}
				C[1]++;
			} else if (S[i] == 'W') {
				Z += U[1] ? 'H' : 'R';
				U[1] = !U[1];
				if (U[1] == M[1]) {
					M[1] = !M[1];
					U[1] = !U[1];
				}
				C[1]++;
			}
		}
		if (
			C[0] % 2 == 1 || C[1] % 2 == 1 ||
			Z == string(N, 'R') || Z == string(N, 'H')) {
			cout << "NO\n";
			continue;
		}
		cout << Z << '\n';
	}

	return 0;
}
