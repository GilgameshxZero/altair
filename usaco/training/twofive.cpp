/*
ID: yangchess1
PROG: twofive
LANG: C++
*/

#define ONLINE_JUDGE

#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__) && !defined(ONLINE_JUDGE)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to)                                   \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; \
			 x != _to;                                          \
			 x += _delta)

LL count(
	array<array<array<array<array<LL, 6>, 6>, 6>, 6>, 6> &D,
	array<pair<LL, LL>, 25> &F,
	array<LL, 5> S) {
	if (
		S[0] < S[1] || S[1] < S[2] || S[2] < S[3] ||
		S[3] < S[4]) {
		return 0;
	}
	if (S[0] > 5) {
		return 0;
	}
	if (S[4] == 5) {
		return 1;
	}
	if (D[S[0]][S[1]][S[2]][S[3]][S[4]] == -1) {
		LL i{accumulate(S.begin(), S.end(), 0LL)};
		if (F[i].first != -1) {
			if (S[F[i].first] != F[i].second) {
				D[S[0]][S[1]][S[2]][S[3]][S[4]] = 0;
			} else {
				S[F[i].first]++;
				D[S[0]][S[1]][S[2]][S[3]][S[4]] = count(D, F, S);
			}
		} else {
			D[S[0]][S[1]][S[2]][S[3]][S[4]] =
				count(D, F, {S[0] + 1, S[1], S[2], S[3], S[4]}) +
				count(D, F, {S[0], S[1] + 1, S[2], S[3], S[4]}) +
				count(D, F, {S[0], S[1], S[2] + 1, S[3], S[4]}) +
				count(D, F, {S[0], S[1], S[2], S[3] + 1, S[4]}) +
				count(D, F, {S[0], S[1], S[2], S[3], S[4] + 1});
		}
	}
	return D[S[0]][S[1]][S[2]][S[3]][S[4]];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
#ifdef ONLINE_JUDGE
	std::freopen("twofive.in", "r", stdin);
	std::freopen("twofive.out", "w", stdout);
#endif

	array<array<array<array<array<LL, 6>, 6>, 6>, 6>, 6> D,
		DD;
	RF(i, 0, 6) {
		RF(j, 0, 6) {
			RF(k, 0, 6) {
				RF(l, 0, 6) {
					D[i][j][k][l].fill(-1);
				}
			}
		}
	}
	DD = D;
	array<pair<LL, LL>, 25> F;
	F.fill({-1, -1});
	F[0] = {0, 0};

	char C;
	cin >> C;
	if (C == 'N') {
		LL N;
		cin >> N;
		string Z(25, ' ');
		LL M{0};
		RF(i, 0, 25) {
			RF(j, 0, 25) {
				if (F[j].first != -1) {
					continue;
				}
				F[j] = {i / 5, i % 5};
				LL m{count(D, F, {0, 0, 0, 0, 0})};
				D = DD;
				if (M + m >= N) {
					break;
				}
				M += m;
				F[j] = {-1, -1};
			}
		}
		RF(i, 0, 25) {
			Z[F[i].first * 5 + F[i].second] = 'A' + i;
		}
		cout << Z << '\n';
	} else {
		string W;
		cin >> W;
		LL Z{0};
		RF(i, 0, 25) {
			RF(j, 0, W[i] - 'A') {
				if (F[j].first != -1) {
					continue;
				}
				F[j] = {i / 5, i % 5};
				Z += count(D, F, {0, 0, 0, 0, 0});
				D = DD;
				F[j] = {-1, -1};
			}
			F[W[i] - 'A'] = {i / 5, i % 5};
		}
		cout << Z + 1 << '\n';
	}

	return 0;
}
