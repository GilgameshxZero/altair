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

	LL N, M;
	cin >> N >> M;
	vector<string> S(N);
	vector<LL> I(N);
	RF(i, 0, N) {
		cin >> S[i];
		I[i] = i;
	}

	do {
		bool fail{false};
		RF(i, 0, N - 1) {
			string &X{S[I[i]]}, &Y{S[I[i + 1]]};
			LL D{0};
			RF(j, 0, M) {
				D += X[j] != Y[j];
			}
			if (D != 1) {
				fail = true;
				break;
			}
		}
		if (!fail) {
			cout << "Yes";
			return 0;
		}
	} while (next_permutation(I.begin(), I.end()));
	cout << "No";
	return 0;
}
