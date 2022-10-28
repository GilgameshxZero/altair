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

#define RF(x, from, to) \
	for (long long x = from, rfDir = from < to ? 1 : -1; x != to; x += rfDir)

using namespace std;

// Compute partial match table (also known as the failure function) (used in
// KMP) for a string.
//
// The partial match table specifies where to "rewind" the matching process to
// if it failes on a given character. Ex:
// i    | 0  | 1 | 2  | 3 | 4  | 5 | 6  | 7 | 8 | 9
// S[i] | A  | B | A  | C | A  | B | A  | B | C |
// T[i] | -1 | 0 | -1 | 1 | -1 | 0 | -1 | 3 | 2 | 0
inline std::vector<std::size_t> computeKmpPartialMatch(
	char const *const cStr,
	std::size_t const cStrLen) {
	std::vector<std::size_t> partialMatch(cStrLen + 1);

	// This represents -1, i.e. we can resume matching for the first character
	// of the string at the next position in the text.
	partialMatch[0] = SIZE_MAX;

	// How far into search string s we must begin (to our best knowledge) if we
	// mismatch.
	std::size_t candidate = 0;

	for (std::size_t a = 1; a < cStrLen; a++) {
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
	for (std::size_t a = 0; a < haystackLen;) {
		if (haystack[a] == needle[candidate]) {
			a++;
			candidate++;
			if (candidate == needleLen) {
				searchResult = haystack + a - candidate;
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

	return std::make_pair(const_cast<char *>(searchResult), candidate);
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
	return std::make_pair(searchRes.first - haystack.c_str(), searchRes.second);
}
inline std::pair<std::size_t, std::size_t> kmpSearch(
	std::string const &haystack,
	std::string const &needle,
	std::vector<std::size_t> const &partialMatch = {},
	std::size_t candidate = 0) {
	return kmpSearch(
		haystack, needle.c_str(), needle.length(), partialMatch, candidate);
}

/* ---------------------------- End of template. ---------------------------- */

int main(int, char const *[]) {
#if !defined(ONLINEJUDGE) && (defined(__APPLE__) || defined(__MACH__))
	std::freopen("../build/i.default.txt", "r", stdin);
	std::freopen("../build/o.default.txt", "w", stdout);
#endif

	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);

	string C, S, T;
	cin >> C >> S >> T;

	auto pmS{computeKmpPartialMatch(S)}, pmT{computeKmpPartialMatch(T)};

	vector<vector<vector<LL>>> s(
		C.length() + 1,
		vector<vector<LL>>(
			S.length(), vector<LL>(T.length(), numeric_limits<int>::min())));
	s[0][0][0] = 0;

	RF(i, 0, C.length()) {
		RF(j, 0, S.length()) {
			RF(k, 0, T.length()) {
				char lmin, lmax;
				if (C[i] == '*') {
					lmin = 'a';
					lmax = 'z';
				} else {
					lmin = lmax = C[i];
				}

				for (char l{lmin}; l <= lmax; l++) {
					size_t nj(j), nk(k);
					LL ds{0};
					while (nj != SIZE_MAX && l != S[nj]) {
						nj = pmS[nj];
					}
					nj++;
					// Now, nj contains the number of matched characters, with l, in S.
					if (nj == S.length()) {
						ds++;
						nj = pmS[nj];
					}
					while (nk != SIZE_MAX && l != T[nk]) {
						nk = pmT[nk];
					}
					nk++;
					if (nk == T.length()) {
						ds--;
						nk = pmT[nk];
					}

					s[i + 1][nj][nk] = max(s[i + 1][nj][nk], s[i][j][k] + ds);
				}
			}
		}
	}

	// RF(i, 0, C.length() + 1) {
	// 	RF(j, 0, S.length()) {
	// 		RF(k, 0, T.length()) {
	// 			cout << s[i][j][k] << ' ';
	// 		}
	// 		cout << endl;
	// 	}
	// 	cout << endl << endl;
	// }

	LL ans{numeric_limits<int>::min()};
	RF(j, 0, S.length()) {
		RF(k, 0, T.length()) {
			ans = max(ans, s[C.length()][j][k]);
		}
	}
	cout << ans;

	return 0;
}
