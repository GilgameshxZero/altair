#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC target( \
	"avx", "avx2", "fma", "bmi", "bmi2", "popcnt", "lzcnt")
#pragma GCC optimize("Ofast", "unroll-loops")
#endif

#include <bits/stdc++.h>

using LL = long long;
using LD = long double;
using namespace std;

#define RF(x, f, t)                                      \
	for (LL x(f), _t(t), _d{x < _t ? 1LL : -1LL}; x != _t; \
			 x += _d)

pair<LL const, LL const> const RKM[]{
	{1031, 1000000007},
	{1033, 1000000009},
	{1039, 1000000021},
	{1049, 1000000033},
	{1051, 1000000087},
	{1061, 1000000093},
	{1063, 1000000097},
	{1069, 1000000103},
	// {1031, 1000000123},
	// {1031, 1000000181},
	// {1031, 1000000207},
	// {1031, 1000000223},
	// {1031, 1000000241},
	// {1031, 1000000271},
	// {1031, 1000000289},
	// {1031, 1000000297},
};
LL const cRKM{sizeof(RKM) / sizeof(pair<LL, LL>)};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	LL T;
	cin >> T;
	while (T--) {
		string S;
		cin >> S;

		vector<LL> R;
		R.push_back(26);
		RF(i, 0, S.length()) {
			if (S[i] == 'a') {
				R.back()++;
			} else {
				R.push_back(S[i] - 'a');
				R.push_back(26);
			}
		}
		if (R.size() == 1) {
			cout << S.length() - 1 << '\n';
			continue;
		}

		array<vector<LL>, cRKM> pre;
		RF(i, 0, cRKM) {
			pre[i].push_back(0);
			RF(j, 0, R.size()) {
				pre[i].push_back(
					(pre[i].back() * RKM[i].first + R[j]) %
					RKM[i].second);
			}
		}
		array<vector<LL>, cRKM> p;
		RF(i, 0, cRKM) {
			p[i].push_back(1);
			RF(j, 0, R.size()) {
				p[i].push_back(
					(p[i].back() * RKM[i].first) % RKM[i].second);
			}
		}

		LL Z{0};
		for (LL i{1}; i < R.size(); i += 2) {
			if (R.size() / 2 % ((i + 1) / 2) != 0) {
				continue;
			}
			array<LL, cRKM> needle;
			RF(j, 0, cRKM) {
				needle[j] = (pre[j][i + 1] -
										 pre[j][1] * p[j][i] % RKM[j].second +
										 RKM[j].second) %
					RKM[j].second;
			}
			bool fail{false};
			LL maxLPad{R[0]}, maxRPad{R[i + 1]},
				minGap{LLONG_MAX};
			for (LL k{i + 2 + i - 1}; k < R.size() && !fail;
					 k += i + 1) {
				maxLPad = min(maxLPad, R[k - i]);
				maxRPad = min(maxRPad, R[k + 1]);
				if (k - i > 0) {
					minGap = min(minGap, R[k - i]);
				}
				RF(j, 0, cRKM) {
					if (
						needle[j] !=
						(pre[j][k + 1] -
						 pre[j][k - i + 1] * p[j][i] % RKM[j].second +
						 RKM[j].second) %
							RKM[j].second) {
						fail = true;
						break;
					}
				}
			}
			if (!fail) {
				maxLPad -= 26;
				maxRPad -= 26;
				minGap -= 26;
				if (maxLPad + maxRPad <= minGap) {
					Z += (maxLPad + 1) * (maxRPad + 1);
				} else {
					Z += (maxRPad + 1) * (minGap - maxRPad + 1);
					Z += (maxRPad + 1) * (maxRPad) / 2;
					Z -=
						(minGap - maxLPad + 1) * (minGap - maxLPad) / 2;
				}
			}
		}
		cout << Z << '\n';
	}

	return 0;
}
