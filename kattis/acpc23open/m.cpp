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

string tToS(LL t) {
	LL h{t / 3600}, m{t % 3600 / 60}, s{t % 3600 % 60};
	stringstream ss;
	ss << setfill('0') << setw(2) << h << ':' << setw(2) << m << ':' << setw(2)
		 << s;
	return ss.str();
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<vector<LL>> Z(30, vector<LL>(66, LLONG_MAX));
	LL I{0}, J{0};
	RF(i, 1, 30 * 60 * 60 + 1) {
		LL t{(i + 12 * 60 * 60) % (24 * 60 * 60)},
			pt{(i + 12 * 60 * 60 - 1) % (24 * 60 * 60)};
		LL h{t % (12 * 60 * 60)}, ph{pt % (12 * 60 * 60)}, m{t % 3600 * 12},
			pm{pt % 3600 * 12}, s{t % 3600 % 60 * 12 * 60},
			ps{pt % 3600 % 60 * 12 * 60};
		if (s < ps) {
			s += 12 * 60 * 60;
			if (m < pm) {
				m += 12 * 60 * 60;
				if (h < ph) {
					h += 12 * 60 * 60;
				}
			}
		}
		if (ps < pm && s >= m) {
			J++;
		}
		if (pm < ph && m >= h) {
			if (ps < pm && s >= m) {
				J++;
			}
			I++;
			J = 0;
		}
		Z[I][J] = min(Z[I][J], i);
	}

	LL N;
	cin >> N;
	RF(i, 0, N) {
		LL u, v;
		cin >> u >> v;
		cout << tToS((Z[u][v] + 12 * 60 * 60) % (24 * 60 * 60)) << '\n';
	}

	return 0;
}
