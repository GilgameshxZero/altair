#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
	// <https://codeforces.com/blog/entry/135127>.
	#include <string>
	#pragma GCC target("arch=core-avx2")
	#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for ( \
		LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
		x != _to; \
		x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N, K;
		cin >> N >> K;
		LL nA, nB, nC;
		if (K % 2 == 0) {
			nA = (1LL << K) / 3 + 1;
			nB = nA;
			nC = nA - 1;
		} else {
			nA = (1LL << K) / 3 + 1;
			nB = nA;
			nC = nA;
		}
		// cout << nA << ' ' << nB << ' ' << nC << '\n';
		string A, B, C(N, ' ');
		cin >> A >> B;
		RF(i, 0, N) {
			C[i] = '0' + ((A[i] - '0') ^ (B[i] - '0'));
		}
		LL xA{}, yA{}, xB{}, yB{}, xC{}, yC{};
		RF(i, 0, N) {
			xA += A[i] == '0';
			yA += A[i] == '1';
			xB += B[i] == '0';
			yB += B[i] == '1';
			xC += C[i] == '0';
			yC += C[i] == '1';
		}
		cout << nA * xA * yA + nB * xB * yB + nC * xC * yC
				 << '\n';
	}

	return 0;
}
