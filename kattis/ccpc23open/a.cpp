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

int main(int, char const *[]) {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL W, H, N, M;
	cin >> W >> H >> N >> M;

	vector<LL> X(N), Y(N), R(N);
	RF(i, 0, N) {
		cin >> X[i] >> Y[i] >> R[i];
	}

	auto hdist{[](LL X, LL Y, LL YY, LL XL, LL XH) {
		LL XP;
		if (X < XL) {
			XP = XL;
		} else if (X > XH) {
			XP = XH;
		} else {
			XP = X;
		}
		return (XP - X) * (XP - X) + (YY - Y) * (YY - Y);
	}};
	auto vdist{[](LL X, LL Y, LL XX, LL YL, LL YH) {
		LL YP;
		if (Y < YL) {
			YP = YL;
		} else if (Y > YH) {
			YP = YH;
		} else {
			YP = Y;
		}
		return (YP - Y) * (YP - Y) + (XX - X) * (XX - X);
	}};

	RF(i, 0, M) {
		LL XL, YL;
		cin >> XL >> YL;
		LL XH{XL + W}, YH{YL + H};
		bool good{true};
		RF(j, 0, N) {
			if (X[j] >= XL && X[j] <= XH && Y[j] >= YL && Y[j] <= YH) {
				good = false;
				break;
			}
		}
		RF(j, 0, N) {
			good &= hdist(X[j], Y[j], YL, XL, XH) > R[j] * R[j];
			good &= vdist(X[j], Y[j], XH, YL, YH) > R[j] * R[j];
			good &= hdist(X[j], Y[j], YH, XL, XH) > R[j] * R[j];
			good &= vdist(X[j], Y[j], XL, YL, YH) > R[j] * R[j];
		}
		cout << (good ? "DOOMSLUG GO!" : "DOOMSLUG STOP!") << '\n';
	}

	return 0;
}
