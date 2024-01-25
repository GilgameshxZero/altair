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

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;
		vector<LL> A(N);
		vector<pair<LL, LL>> B(N);
		vector<vector<LL>> CA(N + 1);
		RF(i, 0, N) {
			cin >> A[i];
			CA[A[i]].push_back(i);
		}

		vector<vector<LL>> rmq(
			Rain::Algorithm::mostSignificant1BitIdx(N) + 1, vector<LL>(N));
		RF(i, 0, N) {
			rmq[0][i] = A[i];
		}
		RF(i, 1, rmq.size()) {
			RF(j, 0, N - (1LL << i) + 1) {
				rmq[i][j] = max(rmq[i - 1][j], rmq[i - 1][j + (1LL << (i - 1))]);
			}
		}
		auto rmqq = [&](LL l, LL r) {
			if (l == r) {
				return rmq[0][l];
			}
			LL i = Rain::Algorithm::mostSignificant1BitIdx(r - l + 1);
			return max(rmq[i][l], rmq[i][r - (1LL << i) + 1]);
		};

		RF(i, 1, N + 1) {
			sort(CA[i].begin(), CA[i].end());
		}
		RF(i, 0, N) {
			cin >> B[i].first;
			B[i].second = i;
		}
		sort(B.begin(), B.end());
		set<LL> bounds;
		bool fail{false};
		RF(i, 0, N) {
			LL j{i};
			while (j < N && B[j].first == B[i].first) {
				j++;
			}

			RF(k, i, j) {
				auto boundIt = bounds.lower_bound(B[k].second);
				pair<LL, LL> b{
					boundIt == bounds.begin() ? -1 : *prev(boundIt),
					boundIt == bounds.end() ? N : *boundIt};
				auto firstIt = lower_bound(
					CA[B[k].first].begin(), CA[B[k].first].end(), B[k].second);
				pair<LL, LL> firsts{
					firstIt == CA[B[i].first].begin() ? -1 : *prev(firstIt),
					firstIt == CA[B[i].first].end() ? N : *firstIt};

				bool possible{false};
				if (firsts.first > b.first) {
					possible |= rmqq(firsts.first, B[k].second) <= B[k].first;
				}
				if (firsts.second < b.second) {
					possible |= rmqq(B[k].second, firsts.second) <= B[k].first;
				}
				if (!possible) {
					fail = true;
					break;
				}
			}
			if (fail) {
				break;
			}
			RF(k, i, j) {
				bounds.insert(B[k].second);
			}

			i = j - 1;
		}
		cout << (fail ? "NO" : "YES") << '\n';
	}

	return 0;
}
