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

	template <typename>
	struct isPair : std::false_type {};

	template <typename TypeFirst, typename TypeSecond>
	struct isPair<std::pair<TypeFirst, TypeSecond>> : std::true_type {};

	template <typename Type, typename = std::void_t<>>
	struct isStdHashable : std::false_type {};

	template <typename Type>
	struct isStdHashable<
		Type,
		std::void_t<decltype(std::declval<std::hash<Type>>()(
			std::declval<Type>()))>> : std::true_type {};
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
				Functional::isPair<TypeInner>::value>::type * = nullptr>
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
				!Functional::isPair<TypeInner>::value &&
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

using namespace Rain::Random;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N;
		cin >> N;

		vector<LL> D[2];
		LL mD[2];
		bool S{false};
		RF(j, 0, 2) {
			D[j].resize(N);
			mD[j] = 0;
			RF(i, 0, N) {
				cin >> D[j][i];
				mD[j] = max(mD[j], D[j][i]);
			}
		}
		if (mD[1] > mD[0]) {
			S = true;
			swap(mD[0], mD[1]);
			swap(D[0], D[1]);
		}

		LL X[2];
		X[0] = mD[0];
		multimap<LL, LL> E[2];
		RF(i, 0, N) {
			E[0].insert({X[0] - D[0][i], i});
		}

		{
			auto TE0{E[0]};
			mD[1] = LLONG_MAX / 2;
			RF(i, 0, N) {
				mD[1] = min(mD[1], D[1][i]);
			}
			X[1] = -mD[1];
			RF(i, 0, N) {
				if (E[0].count(D[1][i] - X[1])) {
					auto k{E[0].find(D[1][i] - X[1])};
					E[0].erase(k);
				}
			}
			if (E[0].empty()) {
				cout << "YES\n";
				for (auto &i : D[0]) {
					cout << i + X[1] << ' ';
				}
				cout << "\n0 " << X[0] + X[1] << '\n';
				continue;
			}

			swap(TE0, E[0]);
		}

		bool fail{false};
		E[0].erase(E[0].find(0));

		vector<LL> L[2];
		RF(i, 0, 2) {
			L[i].resize(N);
		}
		RF(i, 0, N) {
			auto TE0{E[0]};

			X[1] = D[1][i];
			if (X[0] == X[1]) {
				RF(j, 0, N) {
					if (i == j) {
						continue;
					}
					if (E[0].count(X[1] - D[1][j])) {
						auto k{E[0].find(X[1] - D[1][j])};
						L[0][k->second] = k->first;
						L[1][j] = k->first;
						E[0].erase(k);
					}
				}
				if (E[0].empty()) {
					break;
				}
				swap(TE0, E[0]);
				continue;
			}

			E[1].clear();
			RF(j, 0, N) {
				if (i == j) {
					continue;
				}
				E[1].insert({X[1] + D[1][j], j});
			}

			LL B{X[1] * 2};
			while (!E[0].empty()) {
				while (!E[1].empty() && E[1].rbegin()->first > B) {
					auto Y{E[1].find(E[1].rbegin()->first)};
					LL C{Y->first};
					L[1][Y->second] = C;
					E[1].erase(Y);
					LL B{C};
					if (B > X[0]) {
						B = X[0] - (B - X[0]);
					}
					if (E[0].count(B)) {
						auto Z{E[0].find(B)};
						L[0][Z->second] = C;
						E[0].erase(Z);
					} else {
						fail = true;
						break;
					}
				}
				if (fail) {
					break;
				}

				B = X[0] - (B - X[0]);
				while (!E[0].empty() && E[0].begin()->first > B) {
					auto Y{E[0].find(E[0].begin()->first)};
					LL C{Y->first};
					L[0][Y->second] = C;
					E[0].erase(Y);
					LL B{C};
					if (B < X[1]) {
						B = X[1] - (B - X[1]);
					}
					if (E[1].count(C)) {
						auto Z{E[1].find(B)};
						L[1][Z->second] = C;
						E[1].erase(Z);
					} else {
						fail = true;
						break;
					}
				}
				if (fail) {
					break;
				}

				B = X[1] - (B - X[1]);
			}
			if (!fail) {
				break;
			}

			swap(TE0, E[0]);
		}
		cout << (fail ? "NO" : "YES") << '\n';
		if (!fail) {
			RF(i, 0, N) {
				cout << L[0][i] << ' ';
			}
			if (S) {
				swap(X[0], X[1]);
			}
			cout << '\n' << X[0] << ' ' << X[1] << '\n';
		}
	}

	return 0;
}
