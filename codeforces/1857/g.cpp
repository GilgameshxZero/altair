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

	// Persistent DSU based on
	// <https://codeforces.com/blog/entry/22031?#comment-266919>. Does not store
	// additional distance and parity extensions, and does not do path
	// compression. Overall runtime is hence O(N\ln N).
	//
	// Stores an additional extension to track the number of edges per connected
	// component.
	class DisjointSetUnionPersistent {
		private:
		mutable std::vector<bool> isRoot;
		// If a node is root, parent[node] stores the size of the component instead.
		mutable std::vector<std::size_t> parent;
		// cEdges[root] stores the number of edges in a connected component,
		// including those added via ineffective `join`s.
		mutable std::vector<std::size_t> cEdges;

		// History of changes for persistence.
		mutable std::stack<std::size_t> actions, actionParams;

		public:
		DisjointSetUnionPersistent(std::size_t const size)
				: isRoot(size, true), parent(size, 1), cEdges(size, 0) {}

		std::size_t find(std::size_t const i) const {
			if (this->isRoot[i]) {
				return i;
			}
			return this->find(this->parent[i]);
		}
		inline std::size_t rank(std::size_t const i) const {
			return this->parent[this->find(i)];
		}
		inline bool connected(std::size_t const i, std::size_t const j) const {
			auto rI{this->find(i)}, rJ{this->find(j)};
			return rI == rJ;
		}
		inline std::size_t countEdges(std::size_t const i) const {
			return this->cEdges[this->find(i)];
		}
		// Returns false if no join happened; otherwise true.
		inline bool join(std::size_t const i, std::size_t const j) {
			std::size_t rI{this->find(i)}, rJ{this->find(j)};
			if (rI == rJ) {
				this->actions.push(1);
				this->actionParams.push(rI);
				this->cEdges[rI]++;
				return false;
			}
			if (this->parent[rI] > this->parent[rJ]) {
				std::swap(rI, rJ);
			}
			this->actions.push(0);
			this->actionParams.push(this->parent[rI]);
			this->actionParams.push(rJ);
			this->actionParams.push(rI);
			this->parent[rJ] += this->parent[rI];
			this->cEdges[rJ] += this->cEdges[rI] + 1;
			this->isRoot[rI] = false;
			this->parent[rI] = rJ;
			return true;
		}

		// Returns the size of the history at the current time. Rewinds should
		// rewind until the history is some previous size.
		inline std::size_t countActions() const { return this->actions.size(); }
		// Rewinds the last action in the history.
		inline void rewind() {
			auto type{this->actions.top()};
			this->actions.pop();
			if (type == 0) {
				// Join.
				std::size_t rI{this->actionParams.top()};
				this->actionParams.pop();
				std::size_t rJ{this->actionParams.top()};
				this->actionParams.pop();
				std::size_t rankI{this->actionParams.top()};
				this->actionParams.pop();
				this->parent[rI] = rankI;
				this->isRoot[rI] = true;
				this->cEdges[rJ] -= this->cEdges[rI] + 1;
				this->parent[rJ] -= rankI;
			} else if (type == 1) {
				// Ineffective join.
				std::size_t rI{this->actionParams.top()};
				this->actionParams.pop();
				this->cEdges[rI]--;
			}
		}
	};
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
	template <typename Integer, std::size_t MODULUS_OUTER = 0>
	class ModulusField {
		public:
		Integer const MODULUS;
		Integer value;

		// If the integer specified is signed and negative, we want to wrap it back
		// to the positives first.
		template <
			typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		ModulusField(OtherInteger const &value = 0)
				: MODULUS{MODULUS_OUTER},
					value(
						value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
											: value % this->MODULUS) {}

		template <
			typename OtherInteger = std::size_t,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField(Integer const &modulus, OtherInteger const &value = 0)
				: MODULUS{modulus},
					value(
						value < 0 ? this->MODULUS - ((0 - value) % this->MODULUS)
											: value % this->MODULUS) {}

		// Builds a ModulusField<Integer, MODULUS_OUTER> type, but with the same
		// underlying modulus value. Uses more specialized SFINAE to differentiate
		// otherwise identical signatures.
		template <
			typename OtherInteger,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER != 0>::type * = nullptr>
		static ModulusField<Integer, MODULUS_OUTER> build(
			OtherInteger const &value) {
			return {value};
		}

		template <
			typename OtherInteger,
			std::size_t MODULUS_INNER = MODULUS_OUTER,
			typename std::enable_if<MODULUS_INNER == 0>::type * = nullptr>
		ModulusField<Integer, MODULUS_OUTER> build(
			OtherInteger const &value) const {
			return {this->MODULUS, value};
		}

		// Assignment operators need to be overloaded as this class stores an
		// additional modulus, which implicitly deletes the default assignment
		// operator.
		ModulusField<Integer, MODULUS_OUTER> &operator=(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			// Runtime moduli may not actually be the same, so we need to take an
			// additional mod here.
			this->value = other.value % this->MODULUS;
			return *this;
		}
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS_OUTER> &operator=(OtherInteger const &other) {
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
		inline bool operator==(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			// Ignores modulus comparison! Important.
			return this->value == other.value;
		}
		inline bool operator==(ModulusField<Integer, MODULUS_OUTER> const &other) {
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
		inline bool operator!=(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return !(*this == other);
		}
		inline bool operator!=(ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) != other;
		}
		// Other comparison operators don't make that much sense under modulus.

		// Unary.
		inline ModulusField<Integer, MODULUS_OUTER> operator-() const {
			return 0 - *this;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator-() {
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
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			OtherInteger const &other) const {
			return *this + build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			OtherInteger const &other) {
			return std::as_const(*this) + other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return build(this->value + other.value);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator+(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) + other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator+=(
			OtherInteger const &other) {
			return *this = *this + other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator++() {
			return *this += 1;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator++(int) {
			auto tmp(*this);
			*this += 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			OtherInteger const &other) const {
			return *this - build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			OtherInteger const &other) {
			return std::as_const(*this) - other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return build(this->value + this->MODULUS - other.value);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator-(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) - other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator-=(
			OtherInteger const &other) {
			return *this = *this - other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator--() {
			return *this -= 1;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			OtherInteger const &other) const {
			return *this * build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			OtherInteger const &other) {
			return std::as_const(*this) * other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			return build(this->value * other.value);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator*(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) * other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator*=(
			OtherInteger const &other) {
			return *this = *this * other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			OtherInteger const &other) const {
			return *this / build(other);
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			OtherInteger const &other) {
			return std::as_const(*this) / other;
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			ModulusField<Integer, MODULUS_OUTER> const &other) const {
			// This is only true if this has a multiplicative inverse, which is always
			// true if the modulus is prime.
			return *this * other.power(this->MODULUS - 2);
		}
		inline ModulusField<Integer, MODULUS_OUTER> operator/(
			ModulusField<Integer, MODULUS_OUTER> const &other) {
			return std::as_const(*this) / other;
		}
		template <typename OtherInteger>
		inline ModulusField<Integer, MODULUS_OUTER> &operator/=(
			OtherInteger const &other) {
			return *this = *this / other;
		}

		// The following are algorithmic functions based on the modulus field
		// properties.

		// Versions of C++ before C++17 should use static member functions intead of
		// static inline member variables. static inline
		// std::vector<ModulusField<Integer, MODULUS_OUTER>> 	&factorials() {
		// static std::vector<ModulusField<Integer, MODULUS_OUTER>> factorials;
		// return factorials;
		// }
		// static inline std::vector<ModulusField<Integer, MODULUS_OUTER>>
		// 	&invFactorials() {
		// 	static std::vector<ModulusField<Integer, MODULUS_OUTER>>
		// invFactorials; 	return invFactorials;
		// }
		static inline std::vector<ModulusField<Integer, MODULUS_OUTER>> factorials,
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
		inline ModulusField<Integer, MODULUS_OUTER> choose(
			std::size_t const K) const {
			std::size_t const N{static_cast<std::size_t>(this->value)};
			if (K < 0 || K > N) {
				return build(0);
			}
			return factorials[N] * invFactorials[K] * invFactorials[N - K];
		}

		// O(ln N) exponentiation.
		template <typename OtherInteger>
		ModulusField<Integer, MODULUS_OUTER> power(
			OtherInteger const &exponent) const {
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

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator+(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) + right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator-(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) - right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator*(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) * right;
}

template <typename OtherInteger, typename Integer, std::size_t MODULUS_OUTER>
inline Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> operator/(
	OtherInteger const &left,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return right.build(left) / right;
}

// Ease-of-use streaming operators.
template <typename Integer, std::size_t MODULUS_OUTER>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> const &right) {
	return stream << right.value;
}
template <typename Integer, std::size_t MODULUS_OUTER>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::ModulusField<Integer, MODULUS_OUTER> &right) {
	stream >> right.value;
	right.value = (right.modulus + right.value) % right.modulus;
	return stream;
}

using namespace Rain::Algorithm;
using MF = ModulusField<LL, 998244353>;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, S;
		cin >> N >> S;
		vector<pair<LL, pair<LL, LL>>> G;
		RF(i, 0, N - 1) {
			G.push_back({});
			cin >> G.back().second.first >> G.back().second.second >> G.back().first;
			G.back().second.first--;
			G.back().second.second--;
		}
		sort(G.begin(), G.end());
		DisjointSetUnion D(N);
		MF Z{1};
		for (auto &i : G) {
			LL J(D.find(i.second.first)), K(D.find(i.second.second)), j(D.rank(J)),
				k(D.rank(K)), p{-j * (j - 1) / 2 - k * (k - 1) / 2};
			MF c{1 + S - i.first};
			D.join(J, K);
			p += (j + k) * (j + k - 1) / 2 - 1;
			Z *= c.power(p);
		}
		cout << Z << '\n';
	}

	return 0;
}
