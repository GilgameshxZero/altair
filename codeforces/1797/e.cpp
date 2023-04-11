#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target("avx2", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("O3", "unroll-loops")
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

namespace Rain {
	// Inline namespaces are implicitly accessible by the parent namespace.
	inline namespace Literal {
		// Inject std literals into the Rain namespace.
		using namespace std::literals;

		// User-defined literals.
		inline constexpr std::size_t operator"" _zu(unsigned long long value) {
			return static_cast<std::size_t>(value);
		}
		inline std::regex operator"" _re(char const *value, std::size_t) {
			return std::regex(value);
		}
	}
}

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
	// Union-Find/Disjoint-Set-Union implementation. Near-constant time amortized
	// union and find. A constant-time amortized Union-Find exists for offline
	// unions and online finds, but this does not implement it.
	//
	// Implements path compression and union by rank. Stores additional parity and
	// distance extensions:
	// <https://cp-algorithms.com/data_structures/disjoint_set_union.html>.
	class DisjointSetUnion {
		private:
		mutable std::vector<bool> isRoot;
		// If a node is root, parent[node] stores the size of the component instead.
		mutable std::vector<std::size_t> parent;
		// Parity of the path weight from a node to its parent. Joining i and j
		// preserves the parity as if an edge had been added between i and j.
		mutable std::vector<bool> parity;
		// Length of the path wieght from node to its parent. Joining i and j
		// preserves the length as if an edge had been added between the roots of i
		// and j.
		mutable std::vector<std::size_t> distance;

		public:
		DisjointSetUnion(std::size_t const size)
				: isRoot(size, true),
					parent(size, 1),
					parity(size, false),
					distance(size, 0) {}

		std::size_t find(std::size_t const i) const {
			if (this->isRoot[i]) {
				return i;
			}
			auto rI{this->find(this->parent[i])};
			this->parity[i] = this->parity[i] ^ this->parity[this->parent[i]];
			this->distance[i] += this->distance[this->parent[i]];
			return this->parent[i] = rI;
		}
		inline std::size_t rank(std::size_t const i) const {
			return this->parent[this->find(i)];
		}
		inline bool connected(std::size_t const i, std::size_t const j) const {
			auto rI{this->find(i)}, rJ{this->find(j)};
			return rI == rJ;
		}
		inline std::size_t parityToRoot(std::size_t const i) const {
			this->find(i);
			return this->parity[i];
		}
		inline std::size_t distanceToRoot(std::size_t const i) const {
			this->find(i);
			return this->distance[i];
		}
		// Returns false if no join happened; otherwise true.
		inline bool
		join(std::size_t const i, std::size_t const j, std::size_t length = 0) {
			std::size_t rI{this->find(i)}, rJ{this->find(j)};
			if (rI == rJ) {
				return false;
			}
			if (this->parent[rI] > this->parent[rJ]) {
				std::swap(rI, rJ);
			}
			this->parent[rJ] += this->parent[rI];
			this->isRoot[rI] = false;
			this->parent[rI] = rJ;
			// i and j may be swapped here but it is okay.
			this->parity[rI] = this->parity[i] ^ this->parity[j] ^ (length % 2);
			this->distance[rI] = length;
			return true;
		}
	};
}

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

namespace Rain::Algorithm {
	// Segment tree with lazy propagation, supporting range queries and range
	// updates in O(ln N) and O(N) memory.
	//
	// Based on <https://codeforces.com/blog/entry/18051>. Earlier iterations of
	// this data structure have higher constant factor but enable more intuitive
	// modifications. This policy-based structure requires a policy of the
	// following interface:
	//
	// static constexpr Value DEFAULT_VALUE: Identity values at creation and
	// aggregation.
	//
	// static constexpr Update DEFAULT_UPDATE: Identify value of an update.
	//
	// static void apply(Value &value, Update const &update, std::size_t range):
	// Fully apply an update to a leaf node.
	//
	// static Result aggregate(Result const &left, Result const &right):
	// Aggregate two results from queries on children. Aggregating with a Result
	// converted from a default Value should do nothing.
	//
	// static void retrace( Value &value, Value const &left, Value const &right,
	// std::size_t range): Aggregate values from two children while retracing an
	// update. Aggregating with a default Value should do nothing.
	//
	// static void split(Update const &update, Update &left, Update &right,
	// std::size_t range): Split a lazy update into its children updates.
	template <typename Policy>
	class SegmentTreeLazy {
		public:
		using Value = typename Policy::Value;
		using Update = typename Policy::Update;
		using Result = typename Policy::Result;

		protected:
		// Aggregate values at each node.
		std::vector<Value> values;

		// True iff node has a pending lazy update to propagate.
		std::vector<bool> lazy;

		// Lazily-stored updates.
		std::vector<Update> updates;

		// Height of the highest node in the tree.
		std::size_t const HEIGHT;

		public:
		// Segment tree for a segment array of size size.
		SegmentTreeLazy(std::size_t const size)
				: values(2 * size, Policy::DEFAULT_VALUE),
					lazy(values.size(), false),
					updates(values.size(), Policy::DEFAULT_UPDATE),
					HEIGHT{mostSignificant1BitIdx(values.size())} {}

		protected:
		// Propagate all ancestors of nodes in a given inclusive underlying range.
		void propagate(std::size_t left, std::size_t right) {
			std::size_t level{this->HEIGHT}, range{1_zu << (this->HEIGHT - 1)};
			for (left += this->values.size() / 2, right += this->values.size() / 2;
					 level > 0;
					 --level, range >>= 1) {
				for (std::size_t i{left >> level}; i <= (right >> level); ++i) {
					if (this->lazy[i]) {
						Policy::apply(this->values[i * 2], this->updates[i], range);
						Policy::apply(this->values[i * 2 + 1], this->updates[i], range);
						Policy::split(
							this->updates[i],
							this->updates[i * 2],
							this->updates[i * 2 + 1],
							range);
						this->lazy[i * 2] = this->lazy[i * 2 + 1] = true;

						this->updates[i] = Policy::DEFAULT_UPDATE;
						this->lazy[i] = false;
					}
				}
			}
		}

		public:
		// Queries an inclusive range, propagating if necessary then aggregating.
		Result query(std::size_t left, std::size_t right) {
			this->propagate(left, left);
			this->propagate(right, right);
			Value resLeft{Policy::DEFAULT_VALUE}, resRight{Policy::DEFAULT_VALUE};
			for (left += this->values.size() / 2,
					 right += this->values.size() / 2 + 1;
					 left < right;
					 left /= 2, right /= 2) {
				if (left % 2 == 1) {
					resLeft = Policy::aggregate(resLeft, this->values[left++]);
				}
				if (right % 2 == 1) {
					resRight = Policy::aggregate(this->values[--right], resRight);
				}
			}
			return Policy::aggregate(resLeft, resRight);
		}

		// Lazy update an inclusive range.
		void update(std::size_t left, std::size_t right, Update const &update) {
			this->propagate(left, left);
			this->propagate(right, right);
			// Only retrace updates once left or right node has been changed.
			bool changedLeft{false}, changedRight{false};
			std::size_t range{1};
			for (left += this->values.size() / 2,
					 right += this->values.size() / 2 + 1;
					 left < right;
					 left /= 2, right /= 2, range *= 2) {
				if (changedLeft) {
					Policy::retrace(
						this->values[left - 1],
						this->values[left * 2 - 2],
						this->values[left * 2 - 1],
						range);
				}
				if (changedRight) {
					Policy::retrace(
						this->values[right],
						this->values[right * 2],
						this->values[right * 2 + 1],
						range);
				}
				if (left % 2 == 1) {
					Policy::apply(this->values[left++], update, range);
					this->lazy[left - 1] = true;
					this->updates[left - 1] = update;
					changedLeft = true;
				}
				if (right % 2 == 1) {
					Policy::apply(this->values[--right], update, range);
					this->lazy[right] = true;
					this->updates[right] = update;
					changedRight = true;
				}
			}
			for (left--; right > 0; left /= 2, right /= 2, range *= 2) {
				if (changedLeft) {
					Policy::retrace(
						this->values[left],
						this->values[left * 2],
						this->values[left * 2 + 1],
						range);
				}
				if (changedRight && (!changedLeft || left != right)) {
					Policy::retrace(
						this->values[right],
						this->values[right * 2],
						this->values[right * 2 + 1],
						range);
				}
			}
		}
	};
}

namespace Rain::Algorithm {
	// Segment tree without lazy propagation nor range updates.
	//
	// Implements the policy pattern. Policy must implement the following
	// interface (omitted from being an actual interface, as static virtual
	// functions are not supported):
	//
	// static constexpr Value DEFAULT_VALUE: Identity values at creation and
	// aggregation.
	//
	// static void apply(Value &value, Update const &update): Fully apply
	// an update to a leaf node.
	//
	// static Result aggregate(Result const &left, Result const &right):
	// Aggregate two results from queries on children. Aggregating with a Result
	// converted from a default Value should do nothing.
	//
	// static void retrace(Value &value, Value const &left, Value const &right):
	// Aggregate values from two children while retracing an update. Aggregating
	// with a default Value should do nothing.
	template <typename Policy>
	class SegmentTree {
		public:
		using Value = typename Policy::Value;
		using Update = typename Policy::Update;
		using Result = typename Policy::Result;

		protected:
		// Aggregate values at each node.
		std::vector<Value> values;

		public:
		// Segment tree for a segment array of size size.
		SegmentTree(std::size_t const size)
				: values(2 * size, Policy::DEFAULT_VALUE) {}

		// Queries an inclusive range.
		Result query(std::size_t left, std::size_t right) {
			Value resLeft{Policy::DEFAULT_VALUE}, resRight{Policy::DEFAULT_VALUE};
			for (left += this->values.size() / 2,
					 right += this->values.size() / 2 + 1;
					 left < right;
					 left /= 2, right /= 2) {
				// Order of aggregation matters for non-commutative operations.
				if (left % 2 == 1) {
					resLeft = Policy::aggregate(resLeft, this->values[left++]);
				}
				if (right % 2 == 1) {
					resRight = Policy::aggregate(this->values[--right], resRight);
				}
			}
			return Policy::aggregate(resLeft, resRight);
		}

		// Point update an index.
		void update(std::size_t idx, Update const &update) {
			idx += this->values.size() / 2;
			Policy::apply(this->values[idx], update);
			for (idx /= 2; idx >= 1; idx /= 2) {
				Policy::retrace(
					this->values[idx], this->values[idx * 2], this->values[idx * 2 + 1]);
			}
		}
	};
}

class SumDeltaPolicy {
	public:
	using Value = LL;
	using Update = LL;
	using Result = LL;

	static constexpr Value DEFAULT_VALUE{0};
	// static constexpr Update DEFAULT_UPDATE{0};
	static void apply(Value &value, Update const &update) { value += update; }
	static Result aggregate(Result const &left, Result const &right) {
		return left + right;
	}
	static void retrace(Value &value, Value const &left, Value const &right) {
		value = left + right;
	}
	// static void
	// split(Update const &update, Update &left, Update &right, std::size_t range)
	// { 	left += update; 	right += update;
	// }
};

class MinDeltaPolicy {
	public:
	using Value = LL;
	using Update = LL;
	using Result = LL;

	static constexpr Value DEFAULT_VALUE{LLONG_MAX / 2};
	// static constexpr Update DEFAULT_UPDATE{0};
	static void apply(Value &value, Update const &update) {
		value = min(value, value + update);
	}
	static Result aggregate(Result const &left, Result const &right) {
		return min(left, right);
	}
	static void retrace(Value &value, Value const &left, Value const &right) {
		value = min(left, right);
	}
	// static void
	// split(Update const &update, Update &left, Update &right, std::size_t range)
	// { 	left += update; 	right += update;
	// }
};

class MinUpdatePolicy {
	public:
	using Value = LL;
	using Update = LL;
	using Result = LL;

	static constexpr Value DEFAULT_VALUE{LLONG_MAX / 2};
	// static constexpr Update DEFAULT_UPDATE{0};
	static void apply(Value &value, Update const &update) {
		value = min(value, update);
	}
	static Result aggregate(Result const &left, Result const &right) {
		return min(left, right);
	}
	static void retrace(Value &value, Value const &left, Value const &right) {
		value = min(left, right);
	}
	// static void
	// split(Update const &update, Update &left, Update &right, std::size_t range)
	// { 	left += update; 	right += update;
	// }
};

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
		scx.back()[i] = -i - 1;
	}
	RF(i, mc, -1) {
		RF(j, 0, N) {
			if (chain[A[j]] == i) {
				scx[i][j] = A[j];
			} else if (scx[i + 1][j] < 0) {
				scx[i][j] = scx[i + 1][j];
			} else {
				scx[i][j] = tot[scx[i + 1][j]];
			}
		}
	}

	vector<pair<LL, LL>> Q1;
	vector<pair<LL, pair<LL, LL>>> Q(M);
	RF(i, 0, M) {
		LL t, l, r;
		cin >> t >> l >> r;
		if (t == 2) {
			Q1.push_back({r - 1, l - 1});
		}
		Q[i] = {t, {l, r}};
	}
	sort(Q1.begin(), Q1.end());

	unordered_map<pair<LL, LL>, LL, Rain::Random::SplitMixHash<pair<LL, LL>>> q1x;
	vector<unordered_map<LL, LL>> rocc(mc + 1);
	vector<FenwickTree<LL>> rft;
	RF(i, 0, mc + 1) {
		rft.emplace_back(N);
	}
	LL prev{0};
	RF(i, 0, Q1.size()) {
		if (q1x.count({Q1[i].second + 1, Q1[i].first + 1})) {
			continue;
		}
		for (; prev <= Q1[i].first; prev++) {
			RF(j, 0, mc + 1) {
				if (rocc[j].count(scx[j][prev])) {
					rft[j].modify(rocc[j][scx[j][prev]], -1);
				}
				rocc[j][scx[j][prev]] = prev;
				rft[j].modify(rocc[j][scx[j][prev]], 1);
			}
		}
		RF(j, mc, -1) {
			if (
				rft[j].sum(Q1[i].first) -
					(Q1[i].second == 0 ? 0LL : rft[j].sum(Q1[i].second - 1)) ==
				1) {
				q1x[{Q1[i].second + 1, Q1[i].first + 1}] = j;
				break;
			}
		}
	}

	SegmentTree<MinUpdatePolicy> mdst(N);
	FenwickTree<LL> sdft(N);
	RF(i, 0, N) {
		mdst.update(i, chain[A[i]]);
		sdft.modify(i, chain[A[i]]);
	}
	vector<LL> cixc(N), rep(N + 1);
	DisjointSetUnion nonzero(N + 1);
	RF(i, 0, N) {
		cixc[i] = chain[A[i]];
		rep[i] = i;
	}
	rep[N] = N;
	RF(i, N - 1, -1) {
		if (cixc[i] != 0) {
			continue;
		}
		LL newrep{max(rep[nonzero.find(i)], rep[nonzero.find(i + 1)])};
		nonzero.join(i, i + 1);
		rep[nonzero.find(i)] = newrep;
	}

	RF(i, 0, M) {
		if (Q[i].first == 1) {
			LL j{Q[i].second.first - 1};
			if (cixc[j] == 0) {
				j = rep[nonzero.find(j)];
			}
			while (j <= Q[i].second.second - 1) {
				cixc[j]--;
				mdst.update(j, cixc[j]);
				sdft.modify(j, -1);
				if (cixc[j] == 0) {
					LL newrep{max(rep[nonzero.find(j)], rep[nonzero.find(j + 1)])};
					nonzero.join(j, j + 1);
					rep[nonzero.find(j)] = newrep;
				}
				j = rep[nonzero.find(j + 1)];
			}
		} else {
			LL q1xj{q1x[Q[i].second]},
				mdstq{mdst.query(Q[i].second.first - 1, Q[i].second.second - 1)};
			q1xj = min(q1xj, mdstq);
			cout << sdft.sum(Q[i].second.second - 1) -
					(Q[i].second.first == 1 ? 0LL : sdft.sum(Q[i].second.first - 2)) -
					q1xj * (Q[i].second.second - Q[i].second.first + 1)
					 << '\n';
		}
	}

	return 0;
}
