#if defined(__GNUC__) && !defined(__clang__)
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

	map<char, LL> M;
	map<LL, set<char>> R;
	string S;
	cin >> S;
	RF(i, 0, S.length()) {
		M[S[i]]++;
	}
	for (auto i : M) {
		R[i.second].insert(i.first);
	}
	char prev{0};
	string Z;
	bool fail{false};
	RF(i, 0, S.length()) {
		auto [rf, rc] = *R.rbegin();
		if (rc.size() == 1 && *rc.begin() != prev && rf * 2 - 1 >= S.length() - i) {
			prev = *rc.begin();
			Z += prev;
			R.erase(rf);
			R[rf - 1].insert(prev);
			M[prev]--;
		} else {
			LL f;
			if (M.begin()->first == prev && M.size() > 1) {
				prev = (++M.begin())->first;
				f = (++M.begin())->second;
			} else {
				prev = M.begin()->first;
				f = M.begin()->second;
			}

			Z += prev;
			R[f].erase(prev);
			if (R[f].empty()) {
				R.erase(f);
			}
			M.erase(prev);
			f--;
			if (f > 0) {
				M.insert({prev, f});
				R[f].insert(prev);
			}
		}
	}

	RF(i, 0, Z.length() - 1) {
		if (Z[i] == Z[i + 1]) {
			fail = true;
			break;
		}
	}
	cout << (fail ? "-1" : Z);

	return 0;
}
