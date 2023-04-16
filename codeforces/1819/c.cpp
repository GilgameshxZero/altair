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

LL N;
array<vector<LL>, 200000> E, L, H, G;
array<bool, 200000> S, C;
vector<LL> Z;

void calcC(LL cur, LL par) {
	for (auto &i : E[cur]) {
		if (i == par) {
			continue;
		}
		calcC(i, cur);
		if (S[i]) {
			L[cur].push_back(i);
		} else if (C[i]) {
			H[cur].push_back(i);
		} else {
			G[cur].push_back(i);
		}
	}
	if (!G[cur].empty() || H[cur].size() >= 2) {
		C[cur] = false;
		S[cur] = false;
		return;
	}

	C[cur] = true;
	if (H[cur].empty() && L[cur].empty()) {
		S[cur] = true;
	} else {
		S[cur] = false;
	}
}

void calcZ(LL cur) {
	if (H[cur].empty()) {
		for (auto &i : L[cur]) {
			Z.push_back(i);
		}
	} else if (H[cur].size() == 1) {
		LL child{H[cur][0]};
		if (H[child].empty()) {
			for (auto &i : L[child]) {
				Z.push_back(i);
			}
			Z.push_back(child);
		} else {
			for (auto &i : L[child]) {
				Z.push_back(i);
			}
			Z.push_back(H[child][0]);
			calcZ(H[child][0]);
			Z.push_back(child);
		}
		for (auto &i : L[cur]) {
			Z.push_back(i);
		}
	} else {
		if (H[H[cur][0]].empty()) {
			for (auto &i : L[H[cur][0]]) {
				Z.push_back(i);
			}
			Z.push_back(H[cur][0]);
		} else {
			for (auto &i : L[H[cur][0]]) {
				Z.push_back(i);
			}
			Z.push_back(H[H[cur][0]][0]);
			calcZ(H[H[cur][0]][0]);
			Z.push_back(H[cur][0]);
		}
		for (auto &i : L[cur]) {
			Z.push_back(i);
		}
		Z.push_back(H[cur][1]);
		calcZ(H[cur][1]);
	}
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].push_back(V - 1);
		E[V - 1].push_back(U - 1);
	}
	calcC(0, -1);
	if (!G[0].empty() || H[0].size() >= 3) {
		RF(i, 0, N) {
			L[i].clear();
			H[i].clear();
			G[i].clear();
		}
		calcC(E[0][0], -1);
		if (!G[E[0][0]].empty() || H[E[0][0]].size() >= 3) {
			cout << "No";
			return 0;
		}

		cout << "Yes\n";
		Z.push_back(E[0][0]);
		calcZ(E[0][0]);
		for (auto &i : Z) {
			cout << i + 1 << ' ';
		}
		return 0;
	}

	cout << "Yes\n";
	Z.push_back(0);
	calcZ(0);
	for (auto &i : Z) {
		cout << i + 1 << ' ';
	}

	return 0;
}
