#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <array>
#include <atomic>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <queue>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using LL = long long;
using LD = long double;

#define RF(x, from, to)                                                      \
	for (long long x = from, _to = to, _delta{x < _to ? 1LL : -1LL}; x != _to; \
			 x += _delta)

using namespace std;

/* ---------------------------- End of template. ---------------------------- */

LL mp(LL const base, LL const exponent, LL const mod) {
	if (exponent == 0) {
		return 1;
	}
	auto half = mp(base, exponent / 2, mod);
	if (exponent % 2 == 0) {
		return half * half % mod;
	} else {
		return half * half % mod * base % mod;
	}
}

vector<LL> fact, invfact;

LL choose(LL N, LL K, LL M) {
	return fact[N] * invfact[K] % M * invfact[N - K] % M;
}

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL N, M;
	cin >> N >> M;

	// vector<LL> A(3 * N);
	// RF(i, 0, 3 * N) {
	// 	A[i] = i + 1;
	// }
	// vector<LL> sorted{A};
	// LL total{0};
	// do {
	// 	LL cur{0};

	// 	while (true) {
	// 		if (A == sorted) {
	// 			break;
	// 		}

	// 		vector<LL> B{A};
	// 		sort(B.begin(), B.begin() + 2 * N);
	// 		if (B == sorted) {
	// 			cur = 1;
	// 			break;
	// 		}

	// 		B = A;
	// 		sort(B.begin() + N, B.begin() + 3 * N);
	// 		if (B == sorted) {
	// 			cur = 1;
	// 			break;
	// 		}

	// 		B = A;
	// 		sort(B.begin(), B.begin() + 2 * N);
	// 		sort(B.begin() + N, B.begin() + 3 * N);
	// 		if (B == sorted) {
	// 			cur = 2;
	// 			break;
	// 		}

	// 		B = A;
	// 		sort(B.begin() + N, B.begin() + 3 * N);
	// 		sort(B.begin(), B.begin() + 2 * N);
	// 		if (B == sorted) {
	// 			cur = 2;
	// 			break;
	// 		}

	// 		B = A;
	// 		sort(B.begin(), B.begin() + 2 * N);
	// 		sort(B.begin() + N, B.begin() + 3 * N);
	// 		sort(B.begin(), B.begin() + 2 * N);
	// 		if (B == sorted) {
	// 			cur = 3;
	// 			break;
	// 		}

	// 		// B = A;
	// 		// sort(B.begin() + N, B.begin() + 3 * N);
	// 		// sort(B.begin(), B.begin() + 2 * N);
	// 		// sort(B.begin() + N, B.begin() + 3 * N);
	// 		// if (B == sorted) {
	// 		// 	cur = 3;
	// 		// 	break;
	// 		// }

	// 		cur = 1000000000;
	// 		break;
	// 	}

	// 	total += cur;
	// 	RF(i, 0, 3 * N) {
	// 		cout << A[i] << " ";
	// 	}
	// 	cout << ": " << cur << '\n';
	// } while (next_permutation(A.begin(), A.end()));
	// cout << total << '\n';
	// return 0;

	fact.push_back(1);
	RF(i, 1, 3 * N + 1) {
		fact.push_back(fact.back() * i % M);
	}

	invfact.resize(3 * N + 1);
	invfact[3 * N] = mp(fact[3 * N], M - 2, M);
	RF(i, 3 * N - 1, -1) {
		invfact[i] = invfact[i + 1] * (i + 1) % M;
	}

	LL ones{(2 * fact[2 * N] % M - fact[N] - 1 + 5 * M) % M};
	LL twos{0};
	RF(i, 0, N + 1) {
		twos =
			(twos +
			 choose(N, i, M) * choose(N, N - i, M) % M * choose(2 * N - i, N, M)) %
			M;
	}
	twos = (choose(2 * N, N, M) * fact[N] % M * fact[2 * N] % M * 2 % M -
					twos * fact[N] % M * fact[N] % M * fact[N] % M - ones - 1 + 5 * M) %
		M;
	LL threes{(fact[3 * N] - twos - ones - 1 + 5 * M) % M};
	cout << (ones + twos * 2 % M + threes * 3 % M) % M;
	return 0;
}
