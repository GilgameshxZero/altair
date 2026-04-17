#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
// Bugfix: <https://codeforces.com/blog/entry/135127>.
#include <string>
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

LL const MAX_S_LENGTH{1000000}, COMP_THRESH{8};
array<vector<LL>, MAX_S_LENGTH> X, XX;
array<LL, MAX_S_LENGTH> R, RR;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	string S;
	cin >> S;

	RF(i, 0, S.length()) {
		R[i] = S[i] - 'a';
	}
	LL MR{26};
	vector<LL> Y;
	RF(i, 0, 20) {
		RF(j, 0, S.length()) {
			X[R[(j + (1LL << i)) % S.length()]].push_back(j);
		}
		RF(j, 0, MR) {
			for (auto &k : X[j]) {
				XX[R[k]].push_back(k);
			}
			X[j].clear();
		}
		LL r{-1}, rr{-1};
		Y.clear();
		RF(j, 0, MR) {
			for (auto &k : XX[j]) {
				if (rr != R[(k + (1LL << i)) % S.length()]) {
					rr = R[(k + (1LL << i)) % S.length()];
					r++;
				}
				RR[k] = r;
				if (Y.size() < COMP_THRESH) {
					Y.push_back(k);
				}
			}
			rr = -1;
			XX[j].clear();
		}
		MR = r + 1;
		// cout << MR << '\n';
		swap(R, RR);
		if (R[Y.back()] > 0) {
			break;
		}
		bool stop{true};
		RF(i, 0, S.length()) {
			if (R[i] != RR[i]) {
				stop = false;
				break;
			}
		}
		if (stop) {
			break;
		}
	}
	vector<string> Z;
	RF(i, 0, Y.size()) {
		Z.push_back(S.substr(Y[i]) + S.substr(0, Y[i]));
	}
	cout << *min_element(Z.begin(), Z.end()) << '\n';

	return 0;
}
