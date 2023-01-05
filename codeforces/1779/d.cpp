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
		for (std::size_t i = idx; i != SIZE_MAX; i &= i + 1, i--) {
			aggregate += this->tree[i];
		}
		return aggregate;
	}

	// Modify index by a delta.
	void modify(std::size_t const idx, Value const &delta) {
		for (std::size_t i = idx; i < this->tree.size(); i |= i + 1) {
			this->tree[i] += delta;
		}
	}
};

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, M;
		cin >> N;
		vector<LL> A(N), B(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		RF(i, 0, N) {
			cin >> B[i];
		}
		cin >> M;
		vector<LL> X(M);
		RF(i, 0, M) {
			cin >> X[i];
		}

		bool impossible{false};
		RF(i, 0, N) {
			if (A[i] < B[i]) {
				impossible = true;
				break;
			}
		}
		if (impossible) {
			cout << "NO\n";
			continue;
		}

		map<LL, LL> cX;
		RF(i, 0, M) {
			cX[X[i]]++;
		}

		FenwickTree ft(N);
		map<LL, vector<LL>> D;
		RF(i, 0, N) {
			D[B[i]].push_back(i);
		}
		for (auto &i : D) {
			vector<LL> v;
			RF(j, 0, i.second.size()) {
				if (A[i.second[j]] == B[i.second[j]]) {
					ft.modify(i.second[j], 1);
				} else {
					v.push_back(i.second[j]);
				}
			}

			if (!v.empty()) {
				LL cs{1};
				RF(j, 0, v.size() - 1) {
					if (ft.sum(v[j + 1]) - ft.sum(v[j]) != v[j + 1] - v[j] - 1) {
						cs++;
					}
				}
				if (cs > cX[i.first]) {
					impossible = true;
					break;
				}
			}

			RF(j, 0, v.size()) {
				ft.modify(v[j], 1);
			}
		}
		cout << (impossible ? "NO" : "YES") << '\n';
	}

	return 0;
}
