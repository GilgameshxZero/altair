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

struct Vertex {
	vector<LL> E;
	LL S, D, MD;
	bool CV{false};
};

LL N, K1, K2, Z{0};
array<Vertex, 200001> V;

void CV(LL i, LL p) {
	V[i].S = 1;
	for (auto &j : V[i].E) {
		if (j == p || V[j].CV) {
			continue;
		}
		CV(j, i);
		V[i].S += V[j].S;
	}
}

LL CC(LL i, LL p, LL t) {
	for (auto &j : V[i].E) {
		if (j == p || V[j].CV) {
			continue;
		}
		if (V[j].S > t / 2) {
			return CC(j, i, t);
		}
	}
	return i;
}

void CCZ2(LL i, LL p, vector<LL> &G) {
	if (V[i].D > K2) {
		return;
	}
	G[V[i].D]++;
	V[i].MD = V[i].D;
	for (auto &j : V[i].E) {
		if (j == p || V[j].CV) {
			continue;
		}
		V[j].D = V[i].D + 1;
		CCZ2(j, i, G);
		V[i].MD = max(V[i].MD, V[j].MD);
	}
}

void CCZ(LL i, LL p) {
	V[i].CV = true;
	CV(i, p);

	if (K1 <= V[i].S - 1) {
		for (auto &j : V[i].E) {
			if (j == p || V[j].CV) {
				continue;
			}
			LL c{CC(j, 0, V[j].S)};
			CCZ(c, 0);
		}

		vector<LL> F(min(V[i].S, K2 + 1)), G{F};
		F[0] = 1;
		LL p0{0};
		for (auto &j : V[i].E) {
			if (V[j].CV) {
				continue;
			}
			V[j].D = 1;
			CCZ2(j, i, G);
			LL p{p0}, r;
			RF(k, 0, V[j].MD + 1) {
				r = K1 - k;
				if (r >= 0 && r < F.size()) {
					p += F[r];
				}
				r = K2 - k + 1;
				if (r >= 0 && r < F.size()) {
					p -= F[r];
				}
				Z += p * G[k];
			}
			RF(k, 0, V[j].MD + 1) {
				if (k >= K1 + 1 && k < K2 + 2) {
					p0 += G[k];
				}
				F[k] += G[k];
				G[k] = 0;
			}
		}
	}

	V[i].CV = false;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N >> K1 >> K2;
	RF(i, 0, N - 1) {
		LL a, b;
		cin >> a >> b;
		V[a].E.push_back(b);
		V[b].E.push_back(a);
	}
	CV(1, 0);
	LL c{CC(1, 0, N)};
	CCZ(c, 0);
	cout << Z;

	return 0;
}