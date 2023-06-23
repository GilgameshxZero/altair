#include <bits/stdc++.h>
int main() {
	int N;
	std::cin >> N;
	std::cout << (N % 69 % 29 % 4 < N % 2 * 3 ? "alf" : "beata");
}