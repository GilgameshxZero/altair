#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
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

	LL T;
	cin >> T;
	while (T--) {
		string S;
		cin >> S;
		if (count(S.begin(), S.end(), '0') == 0) {
			cout << "0\n";
			continue;
		}
		S = '0' + S;
		array<vector<LL>, 10> P;
		RF(i, 0, S.length()) {
			P[S[i] - '0'].push_back(i);
		}
		vector<LL> F;
		for (LL i(S.length() - 1); i > -1; i--) {
			bitset<10> V;
			LL C{0};
			for (; i > -1; i--) {
				if (!V[S[i] - '0']) {
					V[S[i] - '0'] = true;
					C++;
					if (C == 10) {
						F.push_back(i);
						break;
					}
				}
			}
		}
		reverse(F.begin(), F.end());
		F.push_back(S.length());
		array<LL, 10> NP;
		NP.fill(0);
		string Z;
		RF(i, 0, F.size()) {
			RF(j, Z.empty() ? 1 : 0, 10) {
				if (NP[j] >= P[j].size() || P[j][NP[j]] >= F[i]) {
					Z.push_back('0' + j);
					if (NP[j] >= P[j].size()) {
						i = F.size() - 1;
					} else {
						LL C{P[j][NP[j]] + 1};
						RF(k, 0, 10) {
							for (; NP[k] < P[k].size() && P[k][NP[k]] < C; NP[k]++);
						}
					}
					break;
				}
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
