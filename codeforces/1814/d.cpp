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

	LL T;
	cin >> T;
	while (T--) {
		LL N, K;
		cin >> N >> K;
		vector<LL> F(N), D(N);
		vector<pair<LL, LL>> P(N);
		RF(i, 0, N) {
			cin >> F[i];
		}
		RF(i, 0, N) {
			cin >> D[i];
			P[i] = {F[i] * D[i], i};
		}
		sort(P.begin(), P.end());

		if (P.back().first - P[0].first <= K) {
			cout << "0\n";
			continue;
		}
		LL low{0}, high{N}, mid;
		while (low + 1 < high) {
			mid = (low + high) / 2;

			multiset<LL> planets;
			set<pair<LL, LL>> orbiters;
			vector<LL> orbit(N);
			RF(i, 0, N - mid) {
				planets.insert(P[i].first);
			}
			RF(i, N - mid, N) {
				if (F[P[i].second] > K) {
					orbit[P[i].second] =
						((*planets.rbegin() - K + F[P[i].second] - 1) / F[P[i].second]) *
						F[P[i].second];
					orbiters.insert({orbit[P[i].second], P[i].second});
				}
			}
			bool possible;
			RF(i, 0, mid + 1) {
				possible = true;
				if (*planets.rbegin() - *planets.begin() > K) {
					possible = false;
				}
				while (!orbiters.empty() &&
							 orbiters.rbegin()->first - *planets.begin() <= K &&
							 (orbiters.rbegin()->first - orbiters.begin()->first > K ||
								*planets.rbegin() - orbiters.begin()->first > K)) {
					orbit[orbiters.begin()->second] = max(
						orbiters.begin()->first + F[orbiters.begin()->second],
						((*planets.rbegin() - K + F[orbiters.begin()->second] - 1) /
						 F[orbiters.begin()->second]) *
							F[orbiters.begin()->second]);
					orbiters.insert(
						{orbit[orbiters.begin()->second], orbiters.begin()->second});
					orbiters.erase(orbiters.begin());
				}
				if (
					!orbiters.empty() &&
					(orbiters.rbegin()->first - *planets.begin() > K ||
					 orbiters.rbegin()->first - orbiters.begin()->first > K ||
					 *planets.rbegin() - orbiters.begin()->first > K)) {
					possible = false;
				}
				if (i != mid) {
					planets.insert(P[i + N - mid].first);
					planets.erase(planets.find(P[i].first));
					if (F[P[i + N - mid].second] > K) {
						orbiters.erase(
							{orbit[P[i + N - mid].second], P[i + N - mid].second});
					}
					if (F[P[i].second] > K) {
						orbit[P[i].second] =
							((*planets.rbegin() - K + F[P[i].second] - 1) / F[P[i].second]) *
							F[P[i].second];
						orbiters.insert({orbit[P[i].second], P[i].second});
					}
				}
				if (possible) {
					break;
				}
			}

			if (possible) {
				high = mid;
			} else {
				low = mid;
			}
		}
		cout << high << '\n';
	}

	return 0;
}
