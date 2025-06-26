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

void solve(map<char, LL> &R, vector<string> &Z, string &B) {
	bool pushed{false};
	for (auto &i : R) {
		if (i.second == 0) {
			continue;
		}
		i.second--;
		B += i.first;
		solve(R, Z, B);
		B.pop_back();
		i.second++;
		pushed = true;
	}
	if (!pushed) {
		Z.push_back(B);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;
	map<char, LL> R;
	vector<string> Z;
	string B;
	RF(i, 0, S.length()) {
		R[S[i]]++;
	}
	solve(R, Z, B);
	cout << Z.size() << '\n';
	RF(i, 0, Z.size()) {
		cout << Z[i] << '\n';
	}

	return 0;
}
