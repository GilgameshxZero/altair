#if defined(__GNUC__) && !defined(__clang__) && \
	!defined(__MINGW32__)
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

LL const M{998244353};

void toCanonical(
	LL N,
	vector<vector<LL>> &E,
	vector<LL> &P,
	vector<LL> &S,
	vector<LL> &R,
	vector<LL> &C,
	LL i) {
	S[i] = 1;
	R[i] = 1;
	for (auto &j : E[i]) {
		if (j == P[i]) {
			continue;
		}
		P[j] = i;
		toCanonical(N, E, P, S, R, C, j);
		S[i] += S[j];
		R[i] += R[j];
	}
	if (S[i] % 2 == 0 && P[i] != -1) {
		C.push_back(R[i]);
		R[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	array<LL, 200001> PM;
	PM[0] = 1;
	RF(i, 1, PM.size()) {
		PM[i] = i * PM[i - 1] % M;
	}

	LL _T;
	cin >> _T;
	while (_T--) {
		LL N;
		cin >> N;
		vector<vector<LL>> E(N);
		RF(i, 0, N - 1) {
			LL U, V;
			cin >> U >> V;
			U--;
			V--;
			E[U].push_back(V);
			E[V].push_back(U);
		}
		vector<LL> P(N), S(N), R(N), C;
		P[0] = -1;
		toCanonical(N, E, P, S, R, C, 0);
		// cout << "Canons: ";
		// RF(i, 0, C.size()) {
		// 	cout << C[i] << ' ';
		// }
		// cout << '\n';
		LL ZP{1};
		RF(i, 0, C.size()) {
			ZP = ZP * C[i] % M;
		}
		if (C.empty()) {
			cout << 1 << '\n';
			continue;
		}
		if (C.size() == 1) {
			cout << R[0] * ZP % M << '\n';
			continue;
		}
		vector<LL> YOA[2];
		YOA[0].resize(C.size());
		YOA[1].resize(C.size());
		YOA[0][0] = C[0];
		RF(i, 1, C.size()) {
			YOA[0][i] = YOA[0][i - 1] * C[i] % M;
		}
		YOA[1].back() = C.back();
		RF(i, C.size() - 2, -1) {
			YOA[1][i] = YOA[1][i + 1] * C[i] % M;
		}
		LL ZOA{
			R[0] * YOA[0][C.size() - 2] % M +
			R[0] * YOA[1][1] % M};
		RF(i, 1, C.size() - 1) {
			ZOA =
				(ZOA + R[0] * YOA[0][i - 1] % M * YOA[1][i + 1]) %
				M;
		}
		cout << ZP * ZOA % M * PM[C.size() - 1] % M << '\n';
	}

	return 0;
}
