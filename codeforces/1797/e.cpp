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
	// Computes the the minimum prime factor and a list of primes for all integers
	// up to and including N. The minFactor array is 1-indexed; that is,
	// minFactor[3] refers to the minimum prime factor of 3, which would be 1,
	// since primes[1] = 3. By definition, minFactor[0] = minfactor[1] = -1 (in
	// the integer representation used, which may be unsigned).
	inline std::pair<std::vector<std::size_t>, std::vector<std::size_t>>
	linearSieve(std::size_t const &N) {
		std::vector<std::size_t> minFactor(N + 1, -1), primes;
		for (std::size_t i{2}; i <= N; i++) {
			if (minFactor[i] == -1) {
				minFactor[i] = primes.size();
				primes.push_back(i);
			}
			for (std::size_t j{0}; i * primes[j] <= N; j++) {
				minFactor[i * primes[j]] = j;
				if (primes[j] == primes[minFactor[i]]) {
					break;
				}
			}
		}

		// C++17: guaranteed either NRVO or move.
		return {minFactor, primes};
	}
}

namespace Rain::Algorithm {
	// Fixed-size Fenwick/Binary-Indexed Tree implementation. O(ln N) point
	// updates and range queries. Not thread-safe.
	//
	// Value must support commutative addition. In addition, default
	// initialization should be equivalent to "empty".
	template <typename Value = long long>
	class FenwickTree {
		private:
		std::vector<Value> tree;

		public:
		// Creates a Fenwick tree, which may be resized by operations.
		FenwickTree(std::size_t const size) : tree(size) {}

		// Computes prefix sum up to and including idx.
		Value sum(std::size_t const idx) const {
			Value aggregate{};
			for (std::size_t i{idx}; i != SIZE_MAX; i &= i + 1, i--) {
				aggregate += this->tree[i];
			}
			return aggregate;
		}

		// Modify index by a delta.
		void modify(std::size_t const idx, Value const &delta) {
			for (std::size_t i{idx}; i < this->tree.size(); i |= i + 1) {
				this->tree[i] += delta;
			}
		}
	};
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	auto [minFactor, primes]{linearSieve(5000000)};
	vector<LL> tot(minFactor.size()), chain(tot.size());
	tot[0] = 0;
	tot[1] = 1;
	chain[0] = chain[1] = 0;
	LL mc{0};
	RF(i, 2, tot.size()) {
		LL pmf{(LL)primes[minFactor[i]]}, pmfm{1}, cur{i};
		while (cur % pmf == 0) {
			cur /= pmf;
			pmfm *= pmf;
		}
		if (cur == 1) {
			tot[i] = i / pmf * (pmf - 1);
		} else {
			tot[i] = tot[pmfm] * tot[cur];
		}
		chain[i] = 1 + chain[tot[i]];
		mc = max(mc, chain[i]);
	}

	LL N, M;
	cin >> N >> M;
	vector<LL> A(N);
	RF(i, 0, N) {
		cin >> A[i];
	}

	vector<vector<LL>> scx(mc + 2, vector<LL>(N));
	RF(i, 0, N) {
		scx.back()[i] = -i;
	}
	RF(i, mc, -1) {
		RF(j, 0, N) {
			if (chain[A[j]] == i) {
				scx[i][j] = A[j];
			} else if (scx[i + 1][j] < 0) {
				scx[i][j] = -j;
			} else {
				scx[i][j] = tot[scx[i + 1][j]];
			}
		}
	}

	vector<pair<LL, LL>> Q[2];
	RF(i, 0, M) {
		LL t, l, r;
		cin >> t >> l >> r;
		Q[t - 1].push_back({r - 1, l - 1});
	}
	sort(Q[1].begin(), Q[1].end());

	vector<LL> q1x(Q[1].size());
	vector<unordered_map<LL, LL>> rocc(mc + 1);
	vector<FenwickTree<LL>> rft;
	RF(i, 0, mc + 1) {
		rft.emplace_back(N);
	}
	LL prev{0};
	RF(i, 0, Q[1].size()) {
		for (; prev <= Q[1][i].first; prev++) {
			RF(j, 1, mc + 1) {
				if (rocc[j].count(scx[j][prev])) {
					rft[j].modify(rocc[j][scx[j][prev]], -1);
				}
				rocc[j][scx[j][prev]] = prev;
				rft[j].modify(rocc[j][scx[j][prev]], 1);
			}
		}
		RF(j, mc, -1) {
			if (
				rft[j].sum(Q[1][i].first) -
					(Q[1][i].second == 0 ? 0LL : rft[j].sum(Q[1][i].second - 1)) ==
				1) {
				q1x[i] = j;
				break;
			}
		}
	}

	return 0;
}
