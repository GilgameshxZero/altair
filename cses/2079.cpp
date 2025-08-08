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
	LL S{1};
};

LL N;
array<Vertex, 200001> V;

LL CC(LL i, LL p) {
	for (auto &j : V[i].E) {
		if (j == p) {
			continue;
		}
		if (V[j].S > N / 2) {
			return CC(j, i);
		}
	}
	return i;
}

void CV(LL i, LL p) {
	for (auto &j : V[i].E) {
		if (j == p) {
			continue;
		}
		CV(j, i);
		V[i].S += V[j].S;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> N;
	RF(i, 0, N - 1) {
		LL a, b;
		cin >> a >> b;
		V[a].E.push_back(b);
		V[b].E.push_back(a);
	}
	CV(1, 0);
	cout << CC(1, 0);

	return 0;
}
