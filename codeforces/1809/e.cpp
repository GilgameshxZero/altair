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

#pragma hdrstop	 // ------------------------------------------------------------

LL N, A, B;
vector<vector<vector<LL>>> result;

void sim(vector<LL> &V, vector<LL> &tail, LL f0, LL f1) {
	tail.resize(N + 2);
	tail.back() = f0;
	RF(i, N, -1) {}
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> A >> B;
	vector<LL> V(N + 2), smooth(N + 2);
	RF(i, 1, N + 1) {
		cin >> V[i];
		smooth[i] = smooth[i - 1] + V[i];
	}
	smooth.back() = smooth[N];

	array<vector<LL>, 4> lims;
	RF(i, 0, 4) {
		lims[i].resize(N + 2);
	}
	RF(i, 1, N + 2) {
		lims[0][i] = min(lims[0][i - 1], lims[0][i - 1] - V[i]);
		lims[1][i] = max(lims[1][i - 1], lims[1][i - 1] - V[i]);
		lims[2][i] = min(lims[2][i - 1], lims[2][i - 1] + V[i]);
		lims[3][i] = max(lims[3][i - 1], lims[3][i - 1] + V[i]);
	}

	result.resize(A + B + 1);
	RF(s, 0, A + B + 1) {
		result[s].resize(4);
		if (s <= B) {
			sim(V, result[s][0], 0, s);
		}
		if (s >= A) {
			sim(V, result[s][1], A, s - A);
		}
		if (s <= A) {
			sim(V, result[s][2], s, 0);
		}
		if (s >= B) {
			sim(V, result[s][3], s - B, B);
		}
	}

	return 0;
}
