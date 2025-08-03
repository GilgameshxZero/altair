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

	vector<vector<LL>> E(2 * M);
	RF(i, 0, N) {
		char A, C;
		LL B, D;
		cin >> A >> B >> C >> D;
		B--;
		D--;
		if (A == '-') {
			if (C == '-') {
				E[M + B].push_back(D);
				E[M + D].push_back(B);
			} else {
				E[M + B].push_back(M + D);
				E[D].push_back(B);
			}
		} else {
			if (C == '-') {
				E[B].push_back(D);
				E[M + D].push_back(M + B);
			} else {
				E[B].push_back(M + D);
				E[D].push_back(M + B);
			}
		}
	}

	string Z(M, ' ');
	bool fail{false};
	vector<LL> MM(M);
	RF(i, 0, M) {
		MM[i] = i;
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(MM.begin(), MM.end(), g);
	RF(_i, 0, M) {
		LL i{MM[_i]};
		if (Z[i] != ' ') {
			continue;
		}
		queue<LL> Q;
		Q.push(i);
		vector<pair<LL, char>> C;
		while (!Q.empty()) {
			LL j{Q.front()};
			Q.pop();
			if (j < M && Z[j] == '+' || j >= M && Z[j - M] == '-') {
				fail = true;
				RF(j, 0, C.size()) {
					Z[C[j].first] = C[j].second;
				}
				break;
			}
			if (j < M && Z[j] != ' ' || j >= M && Z[j - M] != ' ') {
				continue;
			}
			if (j < M) {
				C.push_back({j, Z[j]});
				Z[j] = '-';
			} else {
				C.push_back({j - M, Z[j - M]});
				Z[j - M] = '+';
			}
			for (auto k : E[j]) {
				Q.push(k);
			}
		}
		if (fail) {
			Q = queue<LL>();
			fail = false;
			Q.push(M + i);
			while (!Q.empty()) {
				LL j{Q.front()};
				Q.pop();
				if (j < M && Z[j] == '+' || j >= M && Z[j - M] == '-') {
					fail = true;
					break;
				}
				if (j < M && Z[j] != ' ' || j >= M && Z[j - M] != ' ') {
					continue;
				}
				if (j < M) {
					Z[j] = '-';
				} else {
					Z[j - M] = '+';
				}
				for (auto k : E[j]) {
					Q.push(k);
				}
			}
			if (fail) {
				break;
			}
		}
	}

	if (fail) {
		cout << "IMPOSSIBLE";
	} else {
		RF(i, 0, M) {
			cout << Z[i] << ' ';
		}
	}

	return 0;
}
