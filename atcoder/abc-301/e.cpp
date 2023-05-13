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

namespace Rain::Algorithm {
	// Most significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t mostSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_clzll)
		return 8 * sizeof(unsigned long long) - __builtin_clzll(x) - 1;
#endif
#endif
		for (std::size_t bit{8 * sizeof(Integer) - 1};
				 bit != std::numeric_limits<std::size_t>::max();
				 bit--) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Least significant 1-bit for unsigned integral types of at most long long in
	// size. Undefined result if x = 0.
	template <typename Integer>
	inline std::size_t leastSignificant1BitIdx(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_ctzll)
		return __builtin_ctzll(x);
#endif
#endif
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			if (x & (static_cast<Integer>(1) << bit)) {
				return bit;
			}
		}
		return std::numeric_limits<std::size_t>::max();
	}

	// Count of 1-bits in unsigned integral types of at most long long in size.
	template <typename Integer>
	inline std::size_t bitPopcount(Integer const &x) {
#ifdef __has_builtin
#if __has_builtin(__builtin_popcountll)
		return __builtin_popcountll(x);
#endif
#endif
		std::size_t count{0};
		for (std::size_t bit{0}; bit != 8 * sizeof(Integer); bit++) {
			count += !!(x & (static_cast<Integer>(1) << bit));
		}
		return count;
	}
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL H, W, T;
	cin >> H >> W >> T;
	vector<string> A(H + 2);
	RF(i, 0, H) {
		string S;
		cin >> S;
		A[i + 1] = '#' + S + '#';
	}
	A[0] = A[H + 1] = string(W + 2, '#');

	vector<pair<LL, LL>> P;
	pair<LL, LL> S, G;
	H += 2;
	W += 2;
	RF(i, 0, H) {
		RF(j, 0, W) {
			if (A[i][j] == 'o') {
				P.push_back({i, j});
			} else if (A[i][j] == 'S') {
				S = {i, j};
			} else if (A[i][j] == 'G') {
				G = {i, j};
			}
		}
	}

	P.push_back(S);
	vector<vector<vector<LL>>> D;
	for (auto &i : P) {
		D.push_back(vector<vector<LL>>(H, vector<LL>(W, LLONG_MAX / 2)));
		queue<pair<LL, LL>> Q;
		Q.push(i);
		D.back()[i.first][i.second] = 0;
		while (!Q.empty()) {
			auto C{Q.front()};
			Q.pop();

			for (auto &j :
					 {make_pair(-1LL, 0LL),
						make_pair(0LL, 1LL),
						make_pair(1LL, 0LL),
						make_pair(0LL, -1LL)}) {
				pair<LL, LL> J{C.first + j.first, C.second + j.second};
				if (A[J.first][J.second] == '#') {
					continue;
				}
				if (D.back()[J.first][J.second] > D.back()[C.first][C.second] + 1) {
					D.back()[J.first][J.second] = D.back()[C.first][C.second] + 1;
					Q.push(J);
				}
			}
		}
	}
	P.pop_back();

	vector<vector<LL>> Y(1LL << P.size(), vector<LL>(P.size(), LLONG_MAX / 2));
	LL Z{-1};
	if (D.back()[G.first][G.second] <= T) {
		Z = 0;
	}
	RF(i, 1, Y.size()) {
		RF(j, 0, P.size()) {
			if (!((1LL << j) & i)) {
				continue;
			}
			LL R{(1LL << j) ^ i};
			if (R == 0) {
				Y[i][j] = D[j][G.first][G.second];
			} else {
				RF(k, 0, P.size()) {
					if (k == j) {
						continue;
					}
					Y[i][j] = min(Y[i][j], D[j][P[k].first][P[k].second] + Y[R][k]);
				}
			}
			if (D.back()[P[j].first][P[j].second] + Y[i][j] <= T) {
				Z = max(Z, (LL)bitPopcount(i));
			}
		}
	}
	cout << Z;

	return 0;
}
