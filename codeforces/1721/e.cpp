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

#pragma hdrstop	 // ------------------------------------------------------------

namespace Rain::Algorithm {
	// Compute partial match table (also known as the failure function) (used in
	// KMP) for a string.
	//
	// The partial match table specifies where to "rewind" the matching process to
	// if it failes on a given character.
	inline std::vector<std::size_t> computeKmpPartialMatch(
		char const *const cStr,
		std::size_t const cStrLen) {
		std::vector<std::size_t> partialMatch(cStrLen + 1);

		// This represents -1, i.e. we can resume matching for the first character
		// of the string at the next position in the text.
		partialMatch[0] = SIZE_MAX;

		// How far into search string s we must begin (to our best knowledge) if we
		// mismatch.
		std::size_t candidate{0};

		for (std::size_t a{1}; a < cStrLen; a++) {
			if (cStr[a] == cStr[candidate]) {
				partialMatch[a] = partialMatch[candidate];
			} else {
				partialMatch[a] = candidate;
				while (candidate != SIZE_MAX && cStr[a] != cStr[candidate]) {
					candidate = partialMatch[candidate];
				}
			}
			candidate++;
		}

		partialMatch[cStrLen] = candidate;
		// C++17: guaranteed either NRVO or move.
		return partialMatch;
	}
	inline std::vector<std::size_t> computeKmpPartialMatch(std::string const &s) {
		return computeKmpPartialMatch(s.c_str(), s.length());
	}

	// KMP search for needle in haystack, in O(N+M). Optionally pass a candidate
	// parameter if want to continue from a previous search. Returns a pair of
	// (match, candidate). The match is nullptr if no match found, otherwise
	// returns a char * to the first character of the first match found. The
	// candidate is the updated candidate at the termination of the search.
	inline std::pair<char *, std::size_t> kmpSearch(
		char const *const haystack,
		std::size_t const haystackLen,
		char const *const needle,
		std::size_t const needleLen,
		std::vector<std::size_t> const &partialMatch = {},
		std::size_t candidate = 0) {
		// Use these variables, which are set based on whether or not default
		// partialMatch and candidate were passed in.
		std::vector<std::size_t> const &partialMatchProxy =
			partialMatch.size() == 0 ? computeKmpPartialMatch(needle) : partialMatch;

		char const *searchResult = nullptr;

		for (std::size_t a{0}; a < haystackLen;) {
			if (haystack[a] == needle[candidate]) {
				a++;
				candidate++;
				if (candidate == needleLen) {
					searchResult = haystack + a - candidate;
					break;
				}
			} else {
				// Use the partial match table to resume if a match fails.
				candidate = partialMatchProxy[candidate];
				if (candidate == SIZE_MAX) {
					a++;
					candidate = 0;
				}
			}
		}

		return {const_cast<char *>(searchResult), candidate};
	}
	inline std::pair<char *, std::size_t> kmpSearch(
		char const *const haystack,
		std::size_t haystackLen,
		std::string const &needle,
		std::vector<std::size_t> const &partialMatch = {},
		std::size_t candidate = 0) {
		return kmpSearch(
			haystack,
			haystackLen,
			needle.c_str(),
			needle.length(),
			partialMatch,
			candidate);
	}
	// The first element of returned pair will be out of range if not found.
	inline std::pair<std::size_t, std::size_t> kmpSearch(
		std::string const &haystack,
		char const *const needle,
		std::size_t const needleLen,
		std::vector<std::size_t> const &partialMatch = {},
		std::size_t candidate = 0) {
		std::pair<char *, std::size_t> searchRes = kmpSearch(
			haystack.c_str(),
			haystack.length(),
			needle,
			needleLen,
			partialMatch,
			candidate);
		return {searchRes.first - haystack.c_str(), searchRes.second};
	}
	inline std::pair<std::size_t, std::size_t> kmpSearch(
		std::string const &haystack,
		std::string const &needle,
		std::vector<std::size_t> const &partialMatch = {},
		std::size_t candidate = 0) {
		return kmpSearch(
			haystack, needle.c_str(), needle.length(), partialMatch, candidate);
	}
}

using namespace Rain::Algorithm;

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;
	auto pm{computeKmpPartialMatch(S)};
	LL Q;
	cin >> Q;
	auto oc{pm.back()};
	LL oc2{0};
	for (std::size_t a{0}; a < S.length();) {
		if (S[a] == S[oc2]) {
			a++;
			oc2++;
			if (oc2 == S.length()) {
				oc2 = pm[oc2];
			}
		} else {
			// Use the partial match table to resume if a match fails.
			oc2 = pm[oc2];
			if (oc2 == SIZE_MAX) {
				a++;
				oc2 = 0;
			}
		}
	}
	RF(i, 0, Q) {
		string T;
		cin >> T;
		S += T;
		auto candidate{pm.back()};
		pm.resize(S.size() + 1);
		RF(j, S.size() - T.size(), S.size()) {
			if (S[j] == S[candidate]) {
				pm[j] = pm[candidate];
			} else {
				pm[j] = candidate;
				while (candidate != SIZE_MAX && S[j] != S[candidate]) {
					candidate = pm[candidate];
				}
			}
			candidate++;
		}
		pm.back() = candidate;
		candidate = oc2;
		vector<LL> ans;
		for (LL j(S.size() - T.size()); j < S.size();) {
			if (S[j] == S[candidate]) {
				j++;
				candidate++;
				ans.push_back(candidate);
			} else {
				// Use the partial match table to resume if a match fails.
				candidate = pm[candidate];
				if (candidate == SIZE_MAX) {
					j++;
					candidate = 0;
					ans.push_back(candidate);
				}
			}
		}
		RF(j, 0, ans.size()) {
			cout << ans[j] << ' ';
		}
		cout << '\n';
		S.resize(S.size() - T.size());
		pm.resize(S.size() + 1);
		pm.back() = oc;
	}

	return 0;
}
