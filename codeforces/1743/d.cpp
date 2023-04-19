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

	LL N;
	string S;
	cin >> N >> S;
	reverse(S.begin(), S.end());
	while (!S.empty() && S.back() == '0') {
		S.pop_back();
	}
	reverse(S.begin(), S.end());
	if (S.empty()) {
		cout << 0;
		return 0;
	}

	vector<LL> zs;
	RF(i, 0, S.size()) {
		if (S[i] == '0') {
			zs.push_back(i);
		}
	}
	if (zs.empty()) {
		cout << S;
		return 0;
	}

	LL amax{0};
	vector<bool> vmax(zs.size(), false), cand(zs.size());
	RF(i, 0, zs[0]) {
		bool better{false};
		RF(j, 0, zs.size()) {
			cand[j] = S[i + zs[j] - zs[0]] == '1';
			if (!better && cand[j] == false && vmax[j] == true) {
				break;
			}
			if (!better && cand[j] == true && vmax[j] == false) {
				better = true;
			}
		}
		if (better) {
			vmax.swap(cand);
			amax = i;
		}
	}

	RF(i, zs.size() - 1, -1) {
		S[zs[i]] = S[amax + zs[i] - zs[0]];
	}
	cout << S;
	return 0;
}
