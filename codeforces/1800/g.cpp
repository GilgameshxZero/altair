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
#include <random>
#include <regex>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <system_error>
#include <thread>
#include <tuple>
#include <type_traits>
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

#pragma hdrstop

/* ------------------------ End of primary template. ------------------------ */

namespace Rain::Random {
	using Generator = std::mt19937_64;

	// Default, generally-safe generator when one is not supplied by caller.
	inline Generator generator(
		std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch())
			.count());
}

namespace Rain::Algorithm {
	// Implementation for a modulus field over the integers,
	// supporting basic operations add, subtract, multiply in O(1) and divide in
	// O(ln M). Division is generally only valid for prime moduli. For O(1)
	// division, cache multiplicative inverses and multiply with those.
	//
	// A runtime modulus may be specified with MODULUS 0 in the template and the
	// appropriate constructor.
	//
	// Integer must be large enough to store (modulus() - 1)^2.
	template <typename Integer, std::size_t MODULUS = 0>
	class ModulusField {
		public:
		Integer const modulus;
		Integer value;

		// If the integer specified is signed and negative, we want to wrap it back
		// to the positives first.
		template <
			typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		ModulusField(OtherInteger const &value = 0)
				: modulus{MODULUS},
					value(
						value < 0 ? this->modulus - ((0 - value) % this->modulus)
											: value % this->modulus) {}

		template <
			typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField(Integer const &modulus, OtherInteger const &value = 0)
				: modulus{modulus},
					value(
						value < 0 ? this->modulus - ((0 - value) % this->modulus)
											: value % this->modulus) {}

		// Builds a ModulusField<Integer, MODULUS> type, but with the same
		// underlying modulus value. Uses more specialized SFINAE to differentiate
		// otherwise identical signatures.
		template <
			typename OtherInteger,
			std::size_t MODULUS_INNER = MODULUS,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		static ModulusField<Integer, MODULUS> build(OtherInteger const &value) {
			return {value};
		}

		template <
			typename OtherInteger,
			std::size_t MODULUS_INNER = MODULUS,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField<Integer, MODULUS> build(OtherInteger const &value) const {
			return {this->modulus, value};
		}

		// Assignment operators need to be overloaded as this class stores an
		// additional modulus, which implicitly deletes the default assignment
		// operator.
		ModulusField<Integer, MODULUS> &operator=(
			ModulusField<Integer, MODULUS> const &other) {
			// Runtime moduli may not actually be the same, so we need to take an
			// additional mod here.
			this->value = other.value % this->modulus;
			return *this;
		}
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS> &operator=(OtherInteger const &other) {
			return *this = build(other);
		}

		// Comparison.
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const &other) const {
			return *this == build(other);
		}
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const &other) {
			return std::as_const(*this) == other;
		}
		inline bool operator==(ModulusField<Integer, MODULUS> const &other) const {
			// Ignores modulus comparison! Important.
			return this->value == other.value;
		}
		inline bool operator==(ModulusField<Integer, MODULUS> const &other) {
			return std::as_const(*this) == other;
		}
		template <typename OtherInteger>
		inline bool operator!=(OtherInteger const &other) const {
			return *this != build(other);
		}
		template <typename OtherInteger>
		inline bool operator!=(OtherInteger const &other) {
			return std::as_const(*this) != other;
		}
		inline bool operator!=(ModulusField<Integer, MODULUS> const &other) const {
			return !(*this == other);
		}
		inline bool operator!=(ModulusField<Integer, MODULUS> const &other) {
			return std::as_const(*this) != other;
		}
		// Other comparison operators don't make that much sense under modulus.

		// Unary.
		inline ModulusField<Integer, MODULUS> operator-() const {
			return 0 - *this;
		}
		inline ModulusField<Integer, MODULUS> operator-() {
			return -std::as_const(*this);
		}

		// Cast.
		explicit operator bool() const { return this->value != 0; }
		operator std::size_t() const {
			return static_cast<std::size_t>(this->value);
		}
		template <
			typename = typename std::enable_if<
				!std::is_same<Integer, std::size_t>::value>::type>
		operator Integer() const {
			return this->value;
		}

		// Arithmetic.
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator+(
			OtherInteger const &other) const {
			return *this + build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator+(OtherInteger const &other) {
			return std::as_const(*this) + other;
		}
		inline ModulusField<Integer, MODULUS> operator+(
			ModulusField<Integer, MODULUS> const &other) const {
			return build(this->value + other.value);
		}
		inline ModulusField<Integer, MODULUS> operator+(
			ModulusField<Integer, MODULUS> const &other) {
			return std::as_const(*this) + other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> &operator+=(
			OtherInteger const &other) {
			return *this = *this + other;
		}
		inline ModulusField<Integer, MODULUS> operator++() { return *this += 1; }
		inline ModulusField<Integer, MODULUS> operator++(int) {
			auto tmp(*this);
			*this += 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator-(
			OtherInteger const &other) const {
			return *this - build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator-(OtherInteger const &other) {
			return std::as_const(*this) - other;
		}
		inline ModulusField<Integer, MODULUS> operator-(
			ModulusField<Integer, MODULUS> const &other) const {
			return build(this->value + this->modulus - other.value);
		}
		inline ModulusField<Integer, MODULUS> operator-(
			ModulusField<Integer, MODULUS> const &other) {
			return std::as_const(*this) - other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> &operator-=(
			OtherInteger const &other) {
			return *this = *this - other;
		}
		inline ModulusField<Integer, MODULUS> operator--() { return *this -= 1; }
		inline ModulusField<Integer, MODULUS> operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator*(
			OtherInteger const &other) const {
			return *this * build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator*(OtherInteger const &other) {
			return std::as_const(*this) * other;
		}
		inline ModulusField<Integer, MODULUS> operator*(
			ModulusField<Integer, MODULUS> const &other) const {
			return build(this->value * other.value);
		}
		inline ModulusField<Integer, MODULUS> operator*(
			ModulusField<Integer, MODULUS> const &other) {
			return std::as_const(*this) * other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> &operator*=(
			OtherInteger const &other) {
			return *this = *this * other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator/(
			OtherInteger const &other) const {
			return *this / build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> operator/(OtherInteger const &other) {
			return std::as_const(*this) / other;
		}
		inline ModulusField<Integer, MODULUS> operator/(
			ModulusField<Integer, MODULUS> const &other) const {
			// This is only true if this has a multiplicative inverse, which is always
			// true if the modulus is prime.
			return *this * other.power(this->modulus - 2);
		}
		inline ModulusField<Integer, MODULUS> operator/(
			ModulusField<Integer, MODULUS> const &other) {
			return std::as_const(*this) / other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS> &operator/=(
			OtherInteger const &other) {
			return *this = *this / other;
		}

		// The following are algorithmic functions based on the modulus field
		// properties.

		// Versions of C++ before C++17 should use static member functions intead of
		// static inline member variables. static inline
		// std::vector<ModulusField<Integer, MODULUS>> 	&factorials() {
		// static std::vector<ModulusField<Integer, MODULUS>> factorials;
		// return factorials;
		// }
		// static inline std::vector<ModulusField<Integer, MODULUS>>
		// 	&invFactorials() {
		// 	static std::vector<ModulusField<Integer, MODULUS>>
		// invFactorials; 	return invFactorials;
		// }
		static inline std::vector<ModulusField<Integer, MODULUS>> factorials,
			invFactorials;

		// Computes the factorials modulus a prime, up to and including N, in O(N).
		// This enables the choose functions.
		static void precomputeFactorials(std::size_t const N) {
			factorials.resize(N + 1);
			invFactorials.resize(N + 1);
			factorials[0] = 1;
			for (std::size_t i{1}; i <= N; i++) {
				factorials[i] = factorials[i - 1] * i;
			}
			invFactorials[N] = 1 / factorials[N];
			for (std::size_t i{0}; i < N; i++) {
				invFactorials[N - i - 1] = invFactorials[N - i] * (N - i);
			}
		}

		// Computes the binomial coefficient (N choose K) modulus a prime, in O(1).
		// Must have called precomputeFactorials for the largest expected value of N
		// first.
		inline ModulusField<Integer, MODULUS> choose(std::size_t const K) const {
			std::size_t const N{static_cast<std::size_t>(this->value)};
			if (K < 0 || K > N) {
				return build(0);
			}
			return factorials[N] * invFactorials[K] * invFactorials[N - K];
		}

		// O(ln N) exponentiation.
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS> power(OtherInteger const &exponent) const {
			if (exponent == 0) {
				return build(1);
			}
			auto half = this->power(exponent / 2);
			if (exponent % 2 == 0) {
				return half * half;
			} else {
				return half * half * *this;
			}
		}
	};
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator+(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) + right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator-(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) - right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator*(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) * right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS>
inline Rain::Algorithm::ModulusField<Integer, MODULUS> operator/(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return right.build(left) / right;
}

// Ease-of-use streaming operators.
template <typename Integer, std::size_t MODULUS>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS> const &right) {
	return stream << right.value;
}
template <typename Integer, std::size_t MODULUS>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS> &right) {
	stream >> right.value;
	right.value = (right.modulus + right.value) % right.modulus;
	return stream;
}

// Hash operator for this user-defined type, which hashes the inner value (not
// the modulus).
namespace std {
	template <typename Integer, std::size_t MODULUS>
	struct hash<Rain::Algorithm::ModulusField<Integer, MODULUS>> {
		size_t operator()(
			Rain::Algorithm::ModulusField<Integer, MODULUS> const &value) const {
			return hash<Integer>{}(value.value);
		}
	};
}

using namespace Rain::Random;
using namespace Rain::Algorithm;
LL const MOD{998244353};
using MF = ModulusField<LL, MOD>;

void dfs(
	vector<unordered_set<LL>> &E,
	vector<LL> &depth,
	vector<MF> const &polyvar,
	vector<MF> &hash,
	unordered_map<MF, bool> &symm,
	LL cur,
	LL par) {
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		dfs(E, depth, polyvar, hash, symm, i, cur);
		depth[cur] = max(depth[cur], depth[i] + 1);
	}
	unordered_map<MF, bool> clash;
	for (auto const &i : E[cur]) {
		if (i == par) {
			continue;
		}
		hash[cur] *= polyvar[depth[cur]] + hash[i];
		clash[hash[i]] = !clash[hash[i]];
	}
	for (auto it{clash.begin()}; it != clash.end();) {
		if (!it->second) {
			it = clash.erase(it);
		} else {
			it++;
		}
	}
	symm[hash[cur]] =
		clash.empty() || (clash.size() == 1 && symm[clash.begin()->first]);
}

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
		LL N;
		cin >> N;
		vector<unordered_set<LL>> E(N);
		RF(i, 0, N - 1) {
			LL U, V;
			cin >> U >> V;
			E[U - 1].insert(V - 1);
			E[V - 1].insert(U - 1);
		}
		vector<LL> depth(N, 0);
		vector<MF> polyvar(N), hash(N, 1);
		unordered_map<MF, bool> symm;
		RF(i, 0, N) {
			polyvar[i] = uniform_int_distribution<LL>{0, MOD}(generator);
		}
		dfs(E, depth, polyvar, hash, symm, 0, -1);
		cout << (symm[hash[0]] ? "YES" : "NO") << '\n';
	}

	return 0;
}
