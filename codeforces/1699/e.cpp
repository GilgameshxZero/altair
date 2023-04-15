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

using namespace Rain::Algorithm;

LL const MM{5000000};
auto [minFactor, primes]{linearSieve(MM + 1)};
array<int, 1000000> A;
// array<LL, MM + 1> B;
array<vector<pair<int, int>>, MM + 1> B, C;

vector<LL> pfi, pfp;
LL Bi;
void procDiv(LL d, LL cur) {
	if (d * d > Bi) {
		return;
	}
	if (cur == pfi.size()) {
		if (d == 1) {
			return;
		}
		auto i{lower_bound(C[Bi / d].begin(), C[Bi / d].end(), make_pair((int)d, 0))};
		if (i != C[Bi / d].end()) {
			B[Bi].push_back({d, i->second});
		}
		return;
	}

	RF(i, 0, pfp[cur] + 1) {
		procDiv(d, cur + 1);
		d *= primes[pfi[cur]];
	}
}

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	B[1].push_back({1, 1});
	C[1].push_back({1, 1});
	RF(i, 2, B.size()) {
		LL cur{i};
		pfi.clear();
		pfp.clear();
		while (cur != 1) {
			pfi.push_back(minFactor[cur]);
			pfp.push_back(1);
			cur /= primes[minFactor[cur]];
			while (cur != 1 && pfi.back() == minFactor[cur]) {
				pfp.back()++;
				cur /= primes[minFactor[cur]];
			}
		}

		Bi = i;
		procDiv(1, 0);
		B[i].push_back({i, i});
		sort(B[i].begin(), B[i].end());
		C[i].push_back(B[i].back());
		RF(j, B[i].size() - 2, -1) {
			C[i].push_back({B[i][j].first, min(B[i][j].second, C[i].back().second)});
		}
		reverse(C[i].begin(), C[i].end());
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N >> M;
		RF(i, 0, N) {
			cin >> A[i];
		}
		sort(A.begin(), A.begin() + N);
		LL ans{MM};
		RF(i, 1, A[0] + 1) {
			LL amax{0};
			RF(j, 0, N) {
				auto k{lower_bound(C[A[j]].begin(), C[A[j]].end(), make_pair((int)i, 0))};
				amax = max(amax, (LL)k->second);
			}
			ans = min(ans, amax - i);
		}
		cout << ans << '\n';
	}

	return 0;
}
