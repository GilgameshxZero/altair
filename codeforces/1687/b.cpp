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
	vector<pair<LL, LL>> C(M);
	RF(i, 0, M) {
		string Q(M, '0');
		Q[i] = '1';
		cout << "? " << Q << endl;
		cin >> C[i].first;
		C[i].second = i;
	}
	sort(C.begin(), C.end());
	string Q(M, '0');
	LL K{0};
	RF(i, 0, M) {
		string S(Q);
		S[C[i].second] = '1';
		cout << "? " << S << endl;
		LL A;
		cin >> A;
		if (A == K + C[i].first) {
			K = A;
			Q = S;
		}
	}
	cout << "! " << K << endl;
	return 0;
}
