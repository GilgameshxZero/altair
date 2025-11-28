#if defined(__GNUC__) && !defined(__clang__) && !defined(__MINGW32__)
#pragma GCC target("avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, from, to) \
	for (LL x(from), _to(to), _delta{x < _to ? 1LL : -1LL}; x != _to; x += _delta)

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		string S;
		cin >> N >> K >> S;
		LL SP{0}, IE{0}, VE{0}, IVE{0}, SL{0}, BS{0}, CR{0};
		vector<bool> IEX(N, false), VEX(N, false);
		RF(i, 0, N) {
			if (S[i] == '?') {
				SP++;
				if (i < N - 1 && (S[i + 1] == 'V' || S[i + 1] == 'X')) {
					IEX[i] = true;
				}
				if (i > 0 && S[i - 1] == 'I') {
					VEX[i] = true;
				}
				if (IEX[i] && VEX[i]) {
					IVE++;
				} else if (IEX[i]) {
					IE++;
				} else if (VEX[i]) {
					VE++;
				} else {
					CR++;
				}
			} else {
				SL += CR / 2;
				CR = 0;
				if (S[i] == 'I') {
					BS += 1;
					if (i < N - 1 && (S[i + 1] == 'V' || S[i + 1] == 'X')) {
						BS -= 2;
					}
				} else if (S[i] == 'V') {
					BS += 5;
				} else if (S[i] == 'X') {
					BS += 10;
				}
			}
		}
		SL += CR / 2;
		CR = 0;
		// cout << BS << ' ' << SP << ' ' << IE << ' ' << VE << ' ' << IVE << ' ' << SL
		// 		 << '\n';
		RF(i, 0, K) {
			LL CX, CV, CI;
			cin >> CX >> CV >> CI;
			LL NX, NV, NI, sp{SP};
			NI = min(CI, sp);
			sp -= NI;
			NV = min(CV, sp);
			sp -= NV;
			NX = min(CX, sp);
			LL Z{BS + NI + NV * 5 + NX * 10};
			LL NVX{NX + NV};
			LL FIE{min(IE, NI)};
			NI -= FIE;
			Z -= FIE * 2;
			LL FVE{min(VE, NVX)};
			NVX -= FVE;
			Z -= FVE * 2;
			LL FSL{min(SL, min(NI, NVX))};
			NI -= FSL;
			NVX -= FSL;
			Z -= FSL * 2;
			LL ive{IVE}, FIVEI{min(ive, NI)};
			ive -= FIVEI;
			NI -= FIVEI;
			Z -= FIVEI * 2;
			LL FIVEV{min(ive, NVX)};
			ive -= FIVEV;
			NVX -= FIVEV;
			Z -= FIVEV * 2;
			cout << Z << '\n';
		}
	}

	return 0;
}
