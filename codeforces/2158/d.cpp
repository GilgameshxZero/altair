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

void fix(string &S, vector<pair<LL, LL>> &Z) {
	RF(i, 0, S.length()) {
		if (S[i] == '0') {
			continue;
		}
		LL J{-1};
		RF(j, i + 1, S.length()) {
			if (S[j] == '1') {
				J = j;
				break;
			}
		}
		if (J == -1) {
			if (i <= 1) {
				Z.push_back({i + 1, S.length() - 1});
				Z.push_back({i, S.length() - 1});
			} else if (i >= S.length() - 2) {
				Z.push_back({0, i - 1});
				Z.push_back({0, i});
			} else {
				Z.push_back({0, i - 1});
				Z.push_back({i + 1, S.length() - 1});
				Z.push_back({0, S.length() - 1});
			}
		} else {
			Z.push_back({i, J});
			RF(k, i, J + 1) {
				S[k] = '0' + (1 - (S[k] - '0'));
			}
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		string S, T;
		cin >> N >> S >> T;
		vector<pair<LL, LL>> Z[2];
		fix(S, Z[0]);
		fix(T, Z[1]);
		cout << Z[0].size() + Z[1].size() << '\n';
		RF(i, 0, Z[0].size()) {
			cout << Z[0][i].first + 1 << ' ' << Z[0][i].second + 1 << '\n';
		}
		reverse(Z[1].begin(), Z[1].end());
		RF(i, 0, Z[1].size()) {
			cout << Z[1][i].first + 1 << ' ' << Z[1][i].second + 1 << '\n';
		}
	}

	return 0;
}
