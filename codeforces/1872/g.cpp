#if defined(__GNUC__) && !defined(__clang__)
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
		LL N;
		cin >> N;
		vector<LL> A(N);
		RF(i, 0, N) {
			cin >> A[i];
		}
		vector<LL> B[3];
		vector<pair<LL, LL>> D;
		B[0].push_back(0);
		RF(i, 0, N) {
			if (A[i] == 1) {
				if (i != 0 && A[i - 1] != 1) {
					B[0].push_back(0);
					D.back().second = i - 1;
				}
				B[0].back()++;
			} else {
				if (i == 0 || A[i - 1] == 1) {
					B[1].push_back(1);
					B[2].push_back(0);
					D.push_back({i, N - 1});
				}
				B[1].back() *= A[i];
				B[2].back() += A[i];
			}
		}
		if (B[0].size() > B[1].size()) {
			B[0].pop_back();
		}
		if (B[1].empty()) {
			cout << "1 1\n";
			continue;
		}

		// X-intersection, seg-slope, seg-Y-intercept, seg-id.
		map<LD, pair<pair<LD, LD>, LL>> hull;
		// seg-slope, hull-it.
		multimap<LD, decltype(hull)::iterator> hx;
		LD compression{1}, shift{0};
		hull[0].first = {(LD)B[1].back(), -(LD)B[2].back()};
		hull.begin()->second.second = B[1].size() - 1;
		hx.insert({(LD)B[1].back(), hull.begin()});
		LD Z{(LD)B[1].back() - B[2].back()};
		pair<LL, LL> Y{D.back()};
		RF(i, B[1].size() - 2, -1) {
			if (B[1][i] - B[2][i] > Z) {
				Z = (LD)B[1][i] - B[2][i];
				Y = D[i];
			}

			auto j{prev(hull.upper_bound(B[1][i] * compression))};
			LD slope{j->second.first.first * compression},
				intercept{j->second.first.second + shift},
				candidate{slope * B[1][i] + intercept - B[0][i] - B[2][i]};
			if (candidate > Z) {
				Z = candidate;
				Y = {D[i].first, D[j->second.second].second};
			}

			slope = B[1][i] / compression;
			intercept = -B[0][i] - B[2][i] - shift;
			auto k{hx.lower_bound(slope)};
			while (k != hx.end()) {
				auto l{k->second};
				pair<LD, LD> valid{
					l->first, next(l) == hull.end() ? 1e30 : next(l)->first};
				LD intersection{
					(intercept - l->second.first.second) /
					(l->second.first.first - slope)};
				if (intersection < valid.first) {
					hull.erase(l);
					k = hx.erase(k);
				} else if (intersection > valid.second) {
					break;
				} else {
					hull[intersection] = l->second;
					hull.erase(l);
					break;
				}
			}
			k = hx.upper_bound(slope);
			if (k != hx.begin()) {
				k = prev(k);
				while (true) {
					auto l{k->second};
					pair<LD, LD> valid{l == hull.begin() ? 0 : prev(l)->first, l->first};
					LD intersection{
						(intercept - l->second.first.second) /
						(l->second.first.first - slope)};
					if (intersection < valid.first) {
						hull.erase(l);
						if (k == hx.begin()) {
							hx.erase(k);
							break;
						} else {
							auto kk{prev(k)};
							hx.erase(k);
							k = kk;
						}
					} else if (intersection > valid.second) {
						LL ALERT{0};
						break;
					} else {
						auto m{hull.insert({intersection, {{slope, intercept}, i}}).first};
						hx.insert({slope, m});
						break;
					}
				}
			}
			if (hull.empty()) {
				auto m{hull.insert({0, {{slope, intercept}, i}}).first};
				hx.insert({slope, m});
			}

			compression *= B[1][i];
			shift -= B[0][i] + B[2][i];
		}
		cout << Y.first + 1 << ' ' << Y.second + 1 << '\n';
	}

	return 0;
}
