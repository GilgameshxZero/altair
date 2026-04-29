#if defined(__GNUC__) && !defined(__clang__) &&            \
	!defined(__MINGW32__)
	// Bugfix: <https://codeforces.com/blog/entry/135127>.
	#include <string>
	#pragma GCC target(                                      \
		"avx",                                                 \
		"avx2",                                                \
		"fma",                                                 \
		"bmi",                                                 \
		"bmi2",                                                \
		"popcnt",                                              \
		"lzcnt")
	#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

#include <../build/version.hpp>
#include <rain.hpp>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                    \
	for (                                                    \
		LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL};     \
		x != _to;                                              \
		x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	cout << "Hello world!" << endl;
	cout << RAIN_VERSION_MAJOR << '.' << RAIN_VERSION_MINOR
			 << '.' << RAIN_VERSION_REVISION << '.'
			 << RAIN_VERSION_BUILD << endl;

	return 0;
}
