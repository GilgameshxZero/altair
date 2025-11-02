#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

// For an overloaded function f, this wraps it in an rvalue-reference lambda so
// that it may be resolved via perfect forwarding.
#define RAIN_FUNCTIONAL_RESOLVE_OVERLOAD(f)          \
	[](auto &&...args) -> decltype(auto) {             \
		return f(std::forward<decltype(args)>(args)...); \
	}

namespace Rain::Functional {
	// SFINAE for const-iterable types (containers). Assumes sizeof(char) and
	// sizeof(int) are not equal.
	template <typename Type>
	struct isConstIterable {
		template <typename TypeInner>
		static char evaluate(typename TypeInner::const_iterator *);
		template <typename TypeInner>
		static int evaluate(...);

		public:
		enum { value = sizeof(evaluate<Type>(0)) == sizeof(char) };
	};

	// Similar to `std::is_base_of`, but for template base types.
	namespace {
		template <template <typename...> class Type, typename... TypeTemplate>
		std::true_type isBaseOfTemplateImpl(Type<TypeTemplate...> const *);
		template <template <typename...> class Type>
		std::false_type isBaseOfTemplateImpl(...);
	}
	template <template <typename...> class TypeBase, typename TypeDerived>
	using isBaseOfTemplate =
		decltype(isBaseOfTemplateImpl<TypeBase>(std::declval<TypeDerived *>()));

	template <typename Type, typename = std::void_t<>>
	struct isStdHashable : std::false_type {};
	template <typename Type>
	struct isStdHashable<
		Type,
		std::void_t<decltype(std::declval<std::hash<Type>>()(
			std::declval<Type>()))>> : std::true_type {};

	// SFINAE-friendly comparators.
	template <std::size_t LEFT, std::size_t RIGHT>
	struct isEqualTo {
		static constexpr bool value{LEFT == RIGHT};
	};
	template <std::size_t LEFT, std::size_t RIGHT>
	struct isLessThan {
		static constexpr bool value{LEFT < RIGHT};
	};
	template <std::size_t LEFT, std::size_t RIGHT>
	struct isGreaterThan {
		static constexpr bool value{LEFT > RIGHT};
	};
}

namespace Rain::Random {
	using Generator = std::mt19937_64;

	// Default, generally-safe generator when one is not supplied by caller.
	inline Generator generator(
		std::chrono::duration_cast<std::chrono::nanoseconds>(
			std::chrono::high_resolution_clock::now().time_since_epoch())
			.count());

	template <typename>
	struct SplitMixHash;

	// Simple function to combine two 32 or 64-bit hashes, based on
	// <https://stackoverflow.com/questions/5889238/why-is-xor-the-default-way-to-combine-hashes>
	// from Boost.
	//
	// SIZE_T_SIZE is a default argument which forces a substitution, and thus
	// SFINAE.
	template <
		std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 8>::type * = nullptr>
	static inline std::size_t combineHash(std::size_t &seed, std::size_t next) {
		return seed ^= next + 0x517cc1b727220a95 + (seed << 6) + (seed >> 2);
	}
	template <
		typename Type,
		std::size_t SIZE_T_SIZE = sizeof(std::size_t),
		typename std::enable_if<SIZE_T_SIZE == 4>::type * = nullptr>
	static inline std::size_t combineHash(std::size_t &seed, std::size_t next) {
		return seed ^= next + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	// SFINAE enables SplitMixHash for all std::hash-able types, and defines
	// custom unwrapping hash for pairs/containers/etc.
	template <typename Type>
	struct SplitMixHash {
		// 64-bit hash from <https://codeforces.com/blog/entry/62393>.
		template <
			typename TypeInner = Type,
			std::size_t SIZE_T_SIZE = sizeof(std::size_t),
			typename std::enable_if<Functional::isStdHashable<TypeInner>::value>::type
				* = nullptr,
			typename std::enable_if<SIZE_T_SIZE == 8>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			static const std::size_t FIXED_RANDOM(
				std::chrono::duration_cast<std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now().time_since_epoch())
					.count());
			std::size_t hash{std::hash<Type>{}(value)};
			hash += FIXED_RANDOM + 0x9e3779b97f4a7c15;
			hash = (hash ^ (hash >> 30)) * 0xbf58476d1ce4e5b9;
			hash = (hash ^ (hash >> 27)) * 0x94d049bb133111eb;
			return hash ^ (hash >> 31);
		}

		// 32-bit hash from <https://groups.google.com/g/prng/c/VFjdFmbMgZI>.
		template <
			typename TypeInner = Type,
			std::size_t SIZE_T_SIZE = sizeof(std::size_t),
			typename std::enable_if<Functional::isStdHashable<TypeInner>::value>::type
				* = nullptr,
			typename std::enable_if<SIZE_T_SIZE == 4>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			static const std::size_t FIXED_RANDOM(
				std::chrono::duration_cast<std::chrono::nanoseconds>(
					std::chrono::high_resolution_clock::now().time_since_epoch())
					.count());
			std::size_t hash{std::hash<Type>{}(value)};
			hash += FIXED_RANDOM + 0x9e3779b9;
			hash = (hash ^ (hash >> 16)) * 0x85ebca6b;
			hash = (hash ^ (hash >> 13)) * 0xc2b2ae35;
			return hash ^ (hash >> 16);
		}

		// Unwraps a pair.
		template <
			typename TypeInner = Type,
			typename std::enable_if<
				!Functional::isStdHashable<TypeInner>::value &&
				Functional::isBaseOfTemplate<std::pair, TypeInner>::value>::type * =
				nullptr>
		std::size_t operator()(Type const &value) const {
			std::size_t result{0};
			combineHash(result, SplitMixHash<decltype(value.first)>{}(value.first));
			combineHash(result, SplitMixHash<decltype(value.second)>{}(value.second));
			return result;
		}

		// Unwraps a container.
		template <
			typename TypeInner = Type,
			typename std::enable_if<
				!Functional::isStdHashable<TypeInner>::value &&
				!Functional::isBaseOfTemplate<std::pair, TypeInner>::value &&
				Functional::isConstIterable<TypeInner>::value>::type * = nullptr>
		std::size_t operator()(Type const &value) const {
			std::size_t result{0};
			for (auto const &i : value) {
				combineHash(result, SplitMixHash<decltype(i)>{}(i));
			}
			return result;
		}
	};

	// Saves the use of std::remove_reference and std::remove_const.
	template <typename Type>
	struct SplitMixHash<Type &> : SplitMixHash<Type> {};
	template <typename Type>
	struct SplitMixHash<Type const> : SplitMixHash<Type> {};
}

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

array const HASH_POWER{31LL, 37LL};
array const HASH_PRIME{1000000021LL, 1000000087LL};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	LL K;
	cin >> S >> K;
	vector<string> A(K);
	vector<LL> LD, W(K);
	vector<pair<LL, LL>> L(K);
	RF(i, 0, K) {
		cin >> A[i];
		L[i].first = A[i].size();
		L[i].second = i;
	}
	sort(L.begin(), L.end());
	LD.push_back(L[0].first);
	W[L[0].second] = 0;
	RF(i, 1, K) {
		if (LD.back() != L[i].first) {
			LD.push_back(L[i].first);
		}
		W[L[i].second] = LD.size() - 1;
	}
	vector<array<LL, HASH_PRIME.size()>> M(K);
	vector<unordered_set<
		array<LL, HASH_PRIME.size()>,
		Rain::Random::SplitMixHash<array<LL, HASH_PRIME.size()>>>>
		MM(LD.size());
	RF(i, 0, K) {
		RF(j, 0, HASH_PRIME.size()) {
			M[i][j] = 0;
			RF(k, 0, A[i].size()) {
				M[i][j] = (M[i][j] * HASH_POWER[j] + A[i][k] - 'a') % HASH_PRIME[j];
			}
		}
		MM[W[i]].insert(M[i]);
	}

	vector<array<LL, HASH_PRIME.size()>> H(LD.size()), HPP(LD.size());
	RF(i, 0, H.size()) {
		H[i].fill(0);
	}
	RF(i, 0, HASH_PRIME.size()) {
		HPP[0][i] = 1;
		RF(j, 0, LD[0]) {
			HPP[0][i] = HPP[0][i] * HASH_POWER[i] % HASH_PRIME[i];
		}
	}
	RF(i, 1, HPP.size()) {
		RF(j, 0, HASH_PRIME.size()) {
			HPP[i][j] = HPP[i - 1][j];
			RF(k, LD[i - 1], LD[i]) {
				HPP[i][j] = HPP[i][j] * HASH_POWER[j] % HASH_PRIME[j];
			}
		}
	}
	vector<LL> Z(S.size() + 1);
	Z[0] = 1;
	RF(i, 0, S.size()) {
		Z[i + 1] = 0;
		RF(j, 0, H.size()) {
			RF(k, 0, H[j].size()) {
				H[j][k] = H[j][k] * HASH_POWER[k] + S[i] - 'a';
				if (i - LD[j] >= 0) {
					H[j][k] = H[j][k] - (S[i - LD[j]] - 'a') * HPP[j][k];
				}
				H[j][k] = (H[j][k] % HASH_PRIME[k] + HASH_PRIME[k]) % HASH_PRIME[k];
			}
			if (i + 1 - LD[j] >= 0) {
				if (MM[j].count(H[j])) {
					Z[i + 1] = (Z[i + 1] + Z[i + 1 - LD[j]]) % 1000000007;
				}
			}
		}
	}
	cout << Z.back();

	return 0;
}
