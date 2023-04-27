#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		string A;
		cin >> A;
		reverse(A.begin(), A.end());
		multiset<char> B, C;
		RF(i, 0, A.size()) {
			B.insert(A[i]);
		}

		string Z;
		while (!(B.empty() && C.empty())) {
			if (C.empty()) {
				char low{*B.begin()};
				while (A.back() != low) {
					B.erase(B.find(A.back()));
					C.insert(min('9', (char)(A.back() + 1)));
					A.pop_back();
				}
				Z += A.back();
				B.erase(B.begin());
				A.pop_back();
			} else if (B.empty()) {
				Z += *C.begin();
				C.erase(C.begin());
			} else {
				char lowB{*B.begin()}, lowC{*C.begin()};
				if (lowB <= lowC) {
					while (A.back() != lowB) {
						B.erase(B.find(A.back()));
						C.insert(min('9', (char)(A.back() + 1)));
						A.pop_back();
					}
					Z += A.back();
					B.erase(B.begin());
					A.pop_back();
				} else {
					Z += *C.begin();
					C.erase(C.begin());
				}
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
