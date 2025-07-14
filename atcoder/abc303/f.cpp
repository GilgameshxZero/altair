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
	// Forward declaration.
	template <std::size_t LOG_BITS, bool SIGNED>
	class BigInt;
}

namespace std {
	// Limits.
	template <std::size_t LOG_BITS, bool SIGNED>
	class numeric_limits<Rain::Algorithm::BigInt<LOG_BITS, SIGNED>> {
		public:
		using ThisInt = Rain::Algorithm::BigInt<LOG_BITS, SIGNED>;

		static constexpr ThisInt min() {
			return {
				numeric_limits<typename ThisInt::SmallerIntUnsigned>::min(),
				numeric_limits<typename ThisInt::SmallerInt>::min()};
		};
		static constexpr ThisInt max() {
			return {
				numeric_limits<typename ThisInt::SmallerIntUnsigned>::max(),
				numeric_limits<typename ThisInt::SmallerInt>::max()};
		};
	};
}

namespace Rain::Algorithm {
	// Shorthands.
	template <std::size_t LOG_BITS>
	using BigIntSigned = BigInt<LOG_BITS, true>;

	template <std::size_t LOG_BITS>
	using BigIntUnsigned = BigInt<LOG_BITS, false>;

	// Maps log bits to the system type or big int type. Helps with template
	// specialization recursion.
	template <std::size_t LOG_BITS, bool SIGNED>
	class BigIntTypeMap {
		public:
		using Type = BigInt<LOG_BITS, SIGNED>;
	};

	// Template recursion base case 2**5 = 32. Requires 64-bit integer to be
	// available to support the overflow multiplication & division defined later.
	template <>
	class BigIntTypeMap<5, true> {
		public:
		using Type = std::int32_t;
	};
	template <>
	class BigIntTypeMap<5, false> {
		public:
		using Type = std::uint32_t;
	};

	// Overflow multiplication and division. Multiplication returns {low, high} of
	// the result. Division returns {low, high} of the result.
	template <std::size_t LOG_BITS, bool SIGNED>
	inline std::pair<
		typename BigIntTypeMap<LOG_BITS, false>::Type,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type>
	bigIntMultiply(
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type const &X,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type const &Y) {
		using ThisIntUnsigned = typename BigIntTypeMap<LOG_BITS, false>::Type;
		using ThisInt = typename BigIntTypeMap<LOG_BITS, SIGNED>::Type;
		auto [lll, llh]{bigIntMultiply<LOG_BITS - 1, false>(X.low, Y.low)};
		auto [lhl, lhh]{bigIntMultiply<LOG_BITS - 1, SIGNED>(X.low, Y.high)};
		auto [hll, hlh]{bigIntMultiply<LOG_BITS - 1, SIGNED>(X.high, Y.low)};
		auto [hhl, hhh]{bigIntMultiply<LOG_BITS - 1, SIGNED>(X.high, Y.high)};
		ThisIntUnsigned first{lll, 0};
		ThisInt second{0, hhh};
		char firstHighFlow{0}, secondLowFlow{0};
		firstHighFlow -= (llh < 0);
		first.high += llh;
		firstHighFlow +=
			(first.high >
			 std::numeric_limits<typename ThisIntUnsigned::SmallerInt>::max() - lhl);
		first.high += lhl;
		firstHighFlow +=
			(first.high >
			 std::numeric_limits<typename ThisIntUnsigned::SmallerInt>::max() - hll);
		first.high += hll;
		secondLowFlow -= (firstHighFlow < 0);
		second.low += firstHighFlow;
		secondLowFlow +=
			(lhh > 0 &&
			 second.low >
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::max() -
					 lhh) -
			(lhh < 0 &&
			 second.low <
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::min() -
					 lhh);
		second.low += lhh;
		secondLowFlow +=
			(hlh > 0 &&
			 second.low >
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::max() -
					 hlh) -
			(hlh < 0 &&
			 second.low <
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::min() -
					 hlh);
		second.low += hlh;
		secondLowFlow +=
			(hhl > 0 &&
			 second.low >
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::max() -
					 hhl) -
			(hhl < 0 &&
			 second.low <
				 std::numeric_limits<typename ThisInt::SmallerIntUnsigned>::min() -
					 hhl);
		second.low += hhl;
		second.high += secondLowFlow;
		return {first, second};
	}
	template <>
	inline std::pair<
		typename BigIntTypeMap<5, false>::Type,
		typename BigIntTypeMap<5, false>::Type>
	bigIntMultiply<5, false>(
		typename BigIntTypeMap<5, false>::Type const &X,
		typename BigIntTypeMap<5, false>::Type const &Y) {
		using ThisIntUnsigned = typename BigIntTypeMap<5, false>::Type;
		using ThisInt = typename BigIntTypeMap<5, false>::Type;

		std::uint64_t result{X};
		result *= Y;
		return {
			static_cast<ThisIntUnsigned>(result), static_cast<ThisInt>(result >> 32)};
	}
	template <>
	inline std::pair<
		typename BigIntTypeMap<5, false>::Type,
		typename BigIntTypeMap<5, true>::Type>
	bigIntMultiply<5, true>(
		typename BigIntTypeMap<5, true>::Type const &X,
		typename BigIntTypeMap<5, true>::Type const &Y) {
		using ThisIntUnsigned = typename BigIntTypeMap<5, false>::Type;
		using ThisInt = typename BigIntTypeMap<5, true>::Type;

		std::int64_t result{X};
		result *= Y;
		return {
			static_cast<ThisIntUnsigned>(result), static_cast<ThisInt>(result >> 32)};
	}

	template <std::size_t LOG_BITS, bool SIGNED>
	inline typename BigIntTypeMap<LOG_BITS, SIGNED>::Type bigIntDivide(
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type X,
		typename BigIntTypeMap<LOG_BITS, SIGNED>::Type Y) {
		using ThisInt = typename BigIntTypeMap<LOG_BITS, SIGNED>::Type;
		if (Y == 0) {
			throw std::runtime_error("Cannot divide by 0.");
		}

		bool negative((X < 0) ^ (Y < 0));
		if (X < 0) {
			X *= -1;
		}
		if (Y < 0) {
			Y *= -1;
		}
		if (Y == 1) {
			return negative ? -X : X;
		}

		ThisInt low{0}, high{X};
		while (low + 1 < high) {
			ThisInt mid{low + ((high - low) >> 1)};
			auto [productLow, productHigh]{bigIntMultiply<LOG_BITS, SIGNED>(mid, Y)};
			if (productHigh > 0 || productLow > X) {
				high = mid;
			} else {
				low = mid;
			}
		}
		return negative ? -low : low;
	}
	template <bool SIGNED>
	inline typename BigIntTypeMap<5, SIGNED>::Type bigIntDivide(
		typename BigIntTypeMap<5, SIGNED>::Type X,
		typename BigIntTypeMap<5, SIGNED>::Type Y) {
		return X / Y;
	}

	// Two ints of half the size form a larger int. Implements arithmetic, bit
	// shift, binary, and modulus operators, as well as comparison, i/o, and cast
	// operators. Unsigned overflow/underflow is well-defined, but not signed
	// overflow/underflow.
	template <std::size_t LOG_BITS, bool SIGNED>
	class BigInt {
		public:
		using ThisInt = BigInt<LOG_BITS, SIGNED>;
		using SmallerIntUnsigned =
			typename BigIntTypeMap<LOG_BITS - 1, false>::Type;
		using SmallerInt = typename BigIntTypeMap<LOG_BITS - 1, SIGNED>::Type;

		static std::size_t const halfBits{1_zu << (LOG_BITS - 1)};

		SmallerIntUnsigned low;
		SmallerInt high;

		template <
			typename Integer = int,
			typename std::enable_if<sizeof(Integer) * 8 <= halfBits>::type * =
				nullptr>
		BigInt(Integer const &value = 0) : low(value), high((value < 0) ? -1 : 0) {}
		template <
			typename Integer = int,
			typename std::enable_if<sizeof(Integer) * 8 == halfBits * 2>::type * =
				nullptr>
		BigInt(Integer const &value = 0)
				: low(static_cast<SmallerIntUnsigned>(value)),
					high(static_cast<SmallerInt>(value >> (1_zu << (LOG_BITS - 1)))) {}

		// Constructing with bool.
		BigInt(bool const value) : low(value ? 1 : 0), high(0) {}

		// Constructing with a larger int than storable is ill-advised and disabled.

		BigInt(SmallerIntUnsigned const &low, SmallerInt const &high = 0)
				: low(low), high(high) {}
		template <bool OTHER_SIGNED>
		BigInt(BigInt<LOG_BITS, OTHER_SIGNED> const &other)
				: low{other.low}, high(other.high) {}

		// Assignment.
		ThisInt &operator=(ThisInt const &other) {
			if (this == &other) {
				return *this;
			}
			this->low = other.low;
			this->high = other.high;
			return *this;
		}
		template <typename OtherInteger>
		ThisInt &operator=(OtherInteger const &other) {
			return *this = ThisInt(other);
		}

		// Comparison.
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const &other) const {
			return *this == ThisInt(other);
		}
		template <typename OtherInteger>
		inline bool operator==(OtherInteger const &other) {
			return std::as_const(*this) == other;
		}
		inline bool operator==(ThisInt const &other) const {
			return this->low == other.low && this->high == other.high;
		}
		inline bool operator==(ThisInt const &other) {
			return std::as_const(*this) == other;
		}
		template <typename OtherInteger>
		inline bool operator!=(OtherInteger const &other) const {
			return *this != ThisInt(other);
		}
		template <typename OtherInteger>
		inline bool operator!=(OtherInteger const &other) {
			return std::as_const(*this) != other;
		}
		inline bool operator!=(ThisInt const &other) const {
			return !(*this == other);
		}
		inline bool operator!=(ThisInt const &other) {
			return std::as_const(*this) != other;
		}
		template <typename OtherInteger>
		inline bool operator<(OtherInteger const &other) const {
			return *this < ThisInt(other);
		}
		template <typename OtherInteger>
		inline bool operator<(OtherInteger const &other) {
			return std::as_const(*this) < other;
		}
		inline bool operator<(ThisInt const &other) const {
			return this->high < other.high ||
				(this->high == other.high && this->low < other.low);
		}
		inline bool operator<(ThisInt const &other) {
			return std::as_const(*this) < other;
		}
		template <typename OtherInteger>
		inline bool operator<=(OtherInteger const &other) const {
			return *this <= ThisInt(other);
		}
		template <typename OtherInteger>
		inline bool operator<=(OtherInteger const &other) {
			return std::as_const(*this) <= other;
		}
		inline bool operator<=(ThisInt const &other) const {
			return *this < other || *this == other;
		}
		inline bool operator<=(ThisInt const &other) {
			return std::as_const(*this) <= other;
		}
		template <typename OtherInteger>
		inline bool operator>(OtherInteger const &other) const {
			return *this > ThisInt(other);
		}
		template <typename OtherInteger>
		inline bool operator>(OtherInteger const &other) {
			return std::as_const(*this) > other;
		}
		inline bool operator>(ThisInt const &other) const {
			return !(*this <= other);
		}
		inline bool operator>(ThisInt const &other) {
			return std::as_const(*this) > other;
		}
		template <typename OtherInteger>
		inline bool operator>=(OtherInteger const &other) const {
			return *this >= ThisInt(other);
		}
		template <typename OtherInteger>
		inline bool operator>=(OtherInteger const &other) {
			return std::as_const(*this) >= other;
		}
		inline bool operator>=(ThisInt const &other) const {
			return !(*this < other);
		}
		inline bool operator>=(ThisInt const &other) {
			return std::as_const(*this) >= other;
		}

		// Shift.
		template <typename OtherInteger>
		inline ThisInt operator>>(OtherInteger const &shift) const {
			if (shift >= halfBits * 2) {
				return 0;
			} else if (shift >= halfBits) {
				return ThisInt{static_cast<SmallerIntUnsigned>(this->high), 0} >>
					(shift - halfBits);
			}
			ThisInt tmp{this->low >> shift, this->high >> shift};
			SmallerInt lost{this->high - (tmp.high << shift)};
			return {tmp.low + (lost << (halfBits - shift)), tmp.high};
		}
		template <typename OtherInteger>
		inline ThisInt operator>>(OtherInteger const &shift) {
			return std::as_const(*this) >> shift;
		}
		template <typename OtherInteger>
		inline ThisInt &operator>>=(OtherInteger const &shift) {
			return *this = *this >> shift;
		}
		template <typename OtherInteger>
		inline ThisInt operator<<(OtherInteger const &shift) const {
			if (shift >= halfBits * 2) {
				return 0;
			} else if (shift >= halfBits) {
				return ThisInt{0, static_cast<SmallerInt>(this->low)}
				<< (shift - halfBits);
			}
			ThisInt tmp{this->low << shift, this->high << shift};
			SmallerIntUnsigned lost{this->low - (tmp.low >> shift)};
			return {
				tmp.low,
				tmp.high + static_cast<SmallerInt>(lost >> (halfBits - shift))};
		}
		template <typename OtherInteger>
		inline ThisInt operator<<(OtherInteger const &shift) {
			return std::as_const(*this) << shift;
		}
		template <typename OtherInteger>
		inline ThisInt &operator<<=(OtherInteger const &shift) {
			return *this = *this << shift;
		}

		// Binary.
		inline ThisInt operator&(ThisInt const &other) const {
			return {this->low & other.low, this->high & other.high};
		}
		inline ThisInt operator&(ThisInt const &other) {
			return std::as_const(*this) & other;
		}
		inline ThisInt operator|(ThisInt const &other) const {
			return {this->low & other.low, this->high & other.high};
		}
		inline ThisInt operator|(ThisInt const &other) {
			return std::as_const(*this) | other;
		}

		// Unary.
		inline ThisInt operator-() const { return 0 - *this; }
		inline ThisInt operator-() { return -std::as_const(*this); }

		// Cast.
		explicit operator bool() const { return *this != 0; }
		operator BigInt<LOG_BITS, !SIGNED>() const {
			return {
				this->low,
				static_cast<typename BigIntTypeMap<LOG_BITS - 1, !SIGNED>::Type>(
					this->high)};
		}
		operator typename BigIntTypeMap<5, SIGNED>::Type() const {
			if (this->high < 0) {
				auto tmp{
					std::numeric_limits<SmallerIntUnsigned>::max() - this->low + 1};
				return static_cast<typename BigIntTypeMap<5, SIGNED>::Type>(0 - tmp);
			}
			return static_cast<typename BigIntTypeMap<5, SIGNED>::Type>(this->low);
		}

		// Arithmetic.
		template <typename OtherInteger>
		inline ThisInt operator+(OtherInteger const &other) const {
			return *this + ThisInt(other);
		}
		template <typename OtherInteger>
		inline ThisInt operator+(OtherInteger const &other) {
			return *this + ThisInt(other);
		}
		inline ThisInt operator+(ThisInt const &other) const {
			// Unsigned overflow is well-defined.
			return {
				this->low + other.low,
				this->high + other.high +
					(other.low >
					 std::numeric_limits<SmallerIntUnsigned>::max() - this->low)};
		}
		inline ThisInt operator+(ThisInt const &other) {
			return std::as_const(*this) + other;
		}
		inline ThisInt &operator+=(ThisInt const &other) {
			return *this = *this + other;
		}
		inline ThisInt operator++() { return *this += 1; }
		inline ThisInt operator++(int) {
			auto tmp(*this);
			*this += 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ThisInt operator-(OtherInteger const &other) const {
			return *this - ThisInt(other);
		}
		template <typename OtherInteger>
		inline ThisInt operator-(OtherInteger const &other) {
			return *this - ThisInt(other);
		}
		inline ThisInt operator-(ThisInt const &other) const {
			// Unsigned overflow is well-defined.
			return {
				this->low - other.low,
				this->high - other.high - (this->low < other.low)};
		}
		inline ThisInt operator-(ThisInt const &other) {
			return std::as_const(*this) - other;
		}
		inline ThisInt &operator-=(ThisInt const &other) {
			return *this = *this - other;
		}
		inline ThisInt operator--() { return *this -= 1; }
		inline ThisInt operator--(int) {
			auto tmp(*this);
			*this -= 1;
			return tmp;
		}
		template <typename OtherInteger>
		inline ThisInt operator*(OtherInteger const &other) const {
			return *this * ThisInt(other);
		}
		template <typename OtherInteger>
		inline ThisInt operator*(OtherInteger const &other) {
			return *this * ThisInt(other);
		}
		inline ThisInt operator*(ThisInt const &other) const {
			auto [first, second]{bigIntMultiply<LOG_BITS, SIGNED>(*this, other)};
			if (second < 0) {
				auto tmp{
					std::numeric_limits<
						typename BigIntTypeMap<LOG_BITS, false>::Type>::max() -
					first + 1};
				return 0 - ThisInt(tmp.low, tmp.high);
			}
			return first;
		}
		inline ThisInt operator*(ThisInt const &other) {
			return std::as_const(*this) * other;
		}
		inline ThisInt &operator*=(ThisInt const &other) {
			return *this = *this * other;
		}
		template <typename OtherInteger>
		inline ThisInt operator/(OtherInteger const &other) const {
			return *this / ThisInt(other);
		}
		template <typename OtherInteger>
		inline ThisInt operator/(OtherInteger const &other) {
			return *this / ThisInt(other);
		}
		inline ThisInt operator/(ThisInt const &other) const {
			return bigIntDivide<LOG_BITS, SIGNED>(*this, other);
		}
		inline ThisInt operator/(ThisInt const &other) {
			return std::as_const(*this) / other;
		}
		inline ThisInt &operator/=(ThisInt const &other) {
			return *this = *this / other;
		}
		template <typename OtherInteger>
		inline ThisInt operator%(OtherInteger const &other) const {
			return *this % ThisInt(other);
		}
		template <typename OtherInteger>
		inline ThisInt operator%(OtherInteger const &other) {
			return *this % ThisInt(other);
		}
		inline ThisInt operator%(ThisInt const &other) const {
			auto quotient{*this / other};
			return *this - other * quotient;
		}
		inline ThisInt operator%(ThisInt const &other) {
			return std::as_const(*this) % other;
		}
		inline ThisInt &operator%=(ThisInt const &other) {
			return *this = *this % other;
		}
	};
}

template <typename OtherInteger, std::size_t LOG_BITS, bool SIGNED>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator+(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) + right;
}
template <typename OtherInteger, std::size_t LOG_BITS, bool SIGNED>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator-(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) - right;
}
template <typename OtherInteger, std::size_t LOG_BITS, bool SIGNED>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator*(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) * right;
}
template <typename OtherInteger, std::size_t LOG_BITS, bool SIGNED>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator/(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) / right;
}
template <typename OtherInteger, std::size_t LOG_BITS, bool SIGNED>
inline Rain::Algorithm::BigInt<LOG_BITS, SIGNED> operator%(
	OtherInteger const &left,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	return Rain::Algorithm::BigInt<LOG_BITS, SIGNED>(left) % right;
}

template <std::size_t LOG_BITS, bool SIGNED>
inline std::ostream &operator<<(
	std::ostream &stream,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> const &right) {
	if (right < 0) {
		stream.put('-');
		return stream << -right;
	}
	if (right > 9) {
		stream << (right / 10);
	}
	auto first{right % 10};
	auto second{
		static_cast<typename Rain::Algorithm::BigIntTypeMap<5, SIGNED>::Type>(
			first)};
	return stream.put(second + '0');
}
template <std::size_t LOG_BITS, bool SIGNED>
inline std::istream &operator>>(
	std::istream &stream,
	Rain::Algorithm::BigInt<LOG_BITS, SIGNED> &right) {
	std::string s;
	stream >> s;
	right = 0;
	for (char const &i : s) {
		right = right * 10 + (i - '0');
	}
	return stream;
}

using namespace Rain::Algorithm;
using BI = BigInt<7, false>;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL N;
	BI H;
	cin >> N >> H;
	vector<pair<LL, BI>> S;
	BI maxD{0};
	RF(i, 0, N) {
		LL X;
		BI Y;
		cin >> X >> Y;
		S.push_back({X, Y});
		maxD = max(maxD, X * Y);
	}
	sort(S.begin(), S.end());

	vector<pair<LL, pair<LL, BI>>> B;
	{
		priority_queue<pair<BI, pair<LL, LL>>> A;
		RF(i, 0, N) {
			A.push({S[i].second, {S[i].first, i}});
		}
		B.push_back({0, {A.top().second.second, 0}});
		BI D{0};
		LL argD{-1}, i{0};
		while (i < N) {
			LL X{S[i].first};
			while (B.back().first >= X) {
				B.pop_back();
			}
			while (i < N && S[i].first == X) {
				i++;
			}
			while (!A.empty() && A.top().second.first <= X) {
				if (A.top().first * A.top().second.first > D) {
					D = A.top().first * A.top().second.first;
					argD = A.top().second.second;
				}
				A.pop();
			}
			if (A.empty() || D > A.top().first * X) {
				B.push_back({X, {argD, 0}});
				if (!A.empty()) {
					B.push_back(
						{(D + A.top().first - 1) / A.top().first,
						 {A.top().second.second, 0}});
				}
			} else {
				B.push_back({X, {A.top().second.second, 0}});
			}
		}
	}

	RF(i, 1, B.size()) {
		B[i].second.second = B[i - 1].second.second +
			S[B[i - 1].second.first].second *
				(S[B[i - 1].second.first].first <= B[i - 1].first
					 ? S[B[i - 1].second.first].first * (B[i].first - B[i - 1].first)
					 : B[i].first * (B[i].first - 1) / 2 -
						 B[i - 1].first * (B[i - 1].first - 1) / 2);
		if (B[i].second.second >= H) {
			LL low{B[i].first - B[i - 1].first}, high{0}, mid;
			while (low - 1 > high) {
				mid = (low + high) / 2;
				BI cand{
					B[i - 1].second.second +
					S[B[i - 1].second.first].second *
						(S[B[i - 1].second.first].first <= B[i - 1].first
							 ? S[B[i - 1].second.first].first * mid
							 : mid * (mid + 1) / 2 + mid * (B[i - 1].first - 1))};
				if (cand >= H) {
					low = mid;
				} else {
					high = mid;
				}
			}
			cout << low + B[i - 1].first - 1;
			return 0;
		}
	}

	cout << B.back().first - 1 + (H - B.back().second.second + maxD - 1) / maxD;
	return 0;
}
