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

	LL N;
	cin >> N;
	vector<LL> A(1);
	cin >> A[0];
	RF(i, 1, N) {
		LL x;
		cin >> x;
		if (A.back() == 0 || x == 0) {
			A.push_back(x);
		} else {
			A.back() = max(A.back(), x);
		}
	}
	vector<LL> B;
	if (A.size() >= 3) {
		B.push_back(A[0]);
		B.push_back(A[1]);
		RF(i, 2, A.size()) {
			if (B.size() >= 2 && B[B.size() - 2] == 0 && B.back() == 2 && A[i] == 0) {
				B.pop_back();
				B.back() = 3;
			} else {
				B.push_back(A[i]);
			}
		}
		A.swap(B);
		B.clear();
	}

	B.push_back(A[0]);
	RF(i, 1, A.size()) {
		if (
			B.back() == 0 && (A[i] == 1 || A[i] == 2) ||
			(B.back() == 1 || B.back() == 2) && A[i] == 0) {
			B.back() = 4;
		} else {
			B.push_back(A[i]);
		}
	}
	A.swap(B);
	B.clear();

	cout << A.size() << '\n';

	return 0;
}
