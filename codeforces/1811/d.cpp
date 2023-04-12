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
	// Compute the `index`-th Fibonacci matrix in $O(\log N)$ time. Helper
	// function to fibonacciNumber. `index` must be positive.
	template <typename Integer = std::size_t>
	inline std::pair<std::pair<Integer, Integer>, std::pair<Integer, Integer>>
	fibonacciMatrix(std::size_t const index) {
		if (index == 1) {
			return {{1, 1}, {1, 0}};
		}

		if (index % 2 == 0) {
			auto sub{fibonacciMatrix<Integer>(index / 2)};
			return {
				{sub.first.first * sub.first.first +
					 sub.first.second * sub.second.first,
				 sub.first.first * sub.first.second +
					 sub.first.second * sub.second.second},
				{sub.second.first * sub.first.first +
					 sub.second.second * sub.second.first,
				 sub.second.first * sub.first.second +
					 sub.second.second * sub.second.second}};
		} else {
			auto sub{fibonacciMatrix<Integer>(index - 1)};
			return {
				{sub.first.first + sub.first.second, sub.first.first},
				{sub.second.first + sub.second.second, sub.second.first}};
		}
	}

	// Compute the `index`-th Fibonacci number in $O(\log N)$ time with repeated
	// exponentiation on the 2-by-2 matrix. `index` must be non-negative.
	// fibonacciNumber(0) is defined as 0.
	template <typename Integer = std::size_t>
	inline Integer fibonacciNumber(std::size_t const index) {
		return fibonacciMatrix<Integer>(index + 1).second.second;
	}
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<LL> fib(46);
	RF(i, 0, fib.size()) {
		fib[i] = fibonacciNumber(i + 1);
	}

	LL T;
	cin >> T;
	while (T--) {
		LL N, X, Y;
		cin >> N >> X >> Y;
		X--;
		Y--;
		bool possible{true};
		while (N > 1 && possible) {
			if (Y >= fib[N]) {
				LL X2{Y - fib[N]}, Y2{X};
				X = X2;
				Y = Y2;
				N--;
			} else if (Y < fib[N - 1]) {
				LL X2{Y}, Y2{X};
				X = X2;
				Y = Y2;
				N--;
			} else {
				possible = false;
				break;
			}
		}
		cout << (possible ? "YES" : "NO") << '\n';
	}

	return 0;
}
