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

	LL N, M;
	cin >> N >> M;
	vector<vector<pair<LL, LL>>> E(N);
	RF(i, 0, M) {
		LL U, V, Y;
		cin >> U >> V >> Y;
		E[U - 1].push_back({V - 1, Y});
		E[V - 1].push_back({U - 1, Y});
	}
	vector<LL> D(N, LLONG_MAX / 2);
	D.back() = 0;
	priority_queue<pair<LL, LL>, vector<pair<LL, LL>>, greater<pair<LL, LL>>> P;
	P.push({0, N - 1});
	while (!P.empty()) {
		auto X{P.top()};
		P.pop();
		if (D[X.second] != X.first) {
			continue;
		}
		for (auto &i : E[X.second]) {
			if (D[i.first] > D[X.second] + i.second) {
				D[i.first] = D[X.second] + i.second;
				P.push({D[i.first], i.first});
			}
		}
	}
	if (D[0] >= LLONG_MAX / 2) {
		cout << "inf\n";
		return 0;
	}
	LL Z{D[0]};
	RF(i, 0, N) {
		D[i] = min(D[i], Z);
	}
	vector<pair<LL, LL>> Y;
	RF(i, 0, N) {
		Y.push_back({D[i], i});
	}
	sort(Y.begin(), Y.end());
	string S(N, '0');
	vector<pair<string, LL>> W;
	LL Q{Z};
	while (!Y.empty() && Y.back().first == Q) {
		S[Y.back().second] = '1';
		Y.pop_back();
	}
	while (!Y.empty()) {
		LL R{Y.back().first};
		W.push_back({S, Q - R});
		while (!Y.empty() && Y.back().first == R) {
			S[Y.back().second] = '1';
			Y.pop_back();
		}
		Q = R;
	}
	if (Q != 0) {
		W.push_back({S, Q});
	}
	cout << Z << ' ' << W.size() << '\n';
	RF(i, 0, W.size()) {
		cout << W[i].first << ' ' << W[i].second << '\n';
	}

	return 0;
}
