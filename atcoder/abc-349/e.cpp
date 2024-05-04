#if defined(__GNUC__) && !defined(__clang__)
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

array<array<LL, 3>, 3> A;
array<LL, 19683> D;
array<LL, 9> P3;

// Blue is 2 (false) or 0, Red is 1 (true).
bool isRedWin(LL board, bool turn) {
	if (P3[0] == 0) {
		P3[0] = 1;
		RF(i, 1, 9) {
			P3[i] = P3[i - 1] * 3;
		}
	}
	if (D[board] != 0) {
		return D[board] == 1;
	}

	vector<pair<LL, LL>> empty;
	array<array<LL, 3>, 3> B;
	LL bc{board};
	RF(i, 0, 3) {
		RF(j, 0, 3) {
			B[i][j] = bc % 3;
			bc /= 3;
			if (B[i][j] == 0) {
				empty.push_back({i, j});
			}
		}
	}
	RF(i, 0, 3) {
		if (B[i][0] == 2 && B[i][1] == 2 && B[i][2] == 2) {
			D[board] = 2;
			return false;
		}
		if (B[i][0] == 1 && B[i][1] == 1 && B[i][2] == 1) {
			D[board] = 1;
			return true;
		}
		if (B[0][i] == 2 && B[1][i] == 2 && B[2][i] == 2) {
			D[board] = 2;
			return false;
		}
		if (B[0][i] == 1 && B[1][i] == 1 && B[2][i] == 1) {
			D[board] = 1;
			return true;
		}
	}
	if (B[0][0] == 2 && B[1][1] == 2 && B[2][2] == 2) {
		D[board] = 2;
		return false;
	}
	if (B[0][0] == 1 && B[1][1] == 1 && B[2][2] == 1) {
		D[board] = 1;
		return true;
	}
	if (B[0][2] == 2 && B[1][1] == 2 && B[2][0] == 2) {
		D[board] = 2;
		return false;
	}
	if (B[0][2] == 1 && B[1][1] == 1 && B[2][0] == 1) {
		D[board] = 1;
		return true;
	}
	if (empty.size() == 0) {
		LL score[2]{0};
		RF(i, 0, 3) {
			RF(j, 0, 3) {
				score[B[i][j] % 2] += A[i][j];
			}
		}
		if (score[0] > score[1]) {
			D[board] = 2;
			return false;
		} else {
			D[board] = 1;
			return true;
		}
	}
	bool reachable[2]{false};
	RF(i, 0, empty.size()) {
		board += (turn ? 1 : 2) *
			P3[empty[i].first * 3 + empty[i].second];
		reachable[isRedWin(board, !turn) ? 1 : 0] = true;
		board -= (turn ? 1 : 2) *
			P3[empty[i].first * 3 + empty[i].second];
	}
	if (turn) {
		D[board] = reachable[1] ? 1 : 2;
		return reachable[1];
	}
	if (!turn) {
		D[board] = reachable[0] ? 2 : 1;
		return !reachable[0];
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	RF(i, 0, 3) {
		RF(j, 0, 3) {
			cin >> A[i][j];
		}
	}
	cout << (isRedWin(0, true) ? "Takahashi" : "Aoki")
			 << '\n';

	return 0;
}
