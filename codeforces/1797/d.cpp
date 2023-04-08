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

void cip(
	vector<unordered_set<LL>> &E,
	vector<LL> &I,
	vector<LL> &S,
	vector<set<pair<LL, LL>>> &H,
	vector<LL> &P,
	LL cur,
	LL par) {
	P[cur] = par;
	S[cur] = 1;
	LL amax{-1};
	for (auto &i : E[cur]) {
		if (i == par) {
			continue;
		}
		cip(E, I, S, H, P, i, cur);
		I[cur] += I[i];
		S[cur] += S[i];
		if (amax == -1 || S[i] > S[amax] || S[i] == S[amax] && i < amax) {
			amax = i;
		}
		H[cur].insert({S[i], -i});
	}
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;

	vector<unordered_set<LL>> E(N);
	vector<LL> I(N), S(N), P(N);
	vector<set<pair<LL, LL>>> H(N);
	RF(i, 0, N) {
		cin >> I[i];
	}
	RF(i, 0, N - 1) {
		LL U, V;
		cin >> U >> V;
		E[U - 1].insert(V - 1);
		E[V - 1].insert(U - 1);
	}
	cip(E, I, S, H, P, 0, -1);

	RF(i, 0, M) {
		LL _, X;
		cin >> _ >> X;
		X--;
		if (_ == 1) {
			cout << I[X] << '\n';
		} else {
			if (H[X].empty()) {
				continue;
			}
			LL son{-H[X].rbegin()->second}, par{P[X]};
			P[son] = par;
			P[X] = son;
			E[son].insert(par);
			E[par].insert(son);
			E[X].erase(par);
			E[par].erase(X);
			S[X] -= S[son];
			S[son] += S[X];
			I[X] -= I[son];
			I[son] += I[X];
			H[son].insert({S[X], -X});
			H[X].erase({S[son] - S[X], -son});
			H[par].erase({S[son], -X});
			H[par].insert({S[son], -son});
		}
	}

	return 0;
}
