#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
int main() {
	int N;
	cin >> N;
	if (filesystem::exists("test.txt")) {
		cout << "alf";
	} else {
		cout << "beata";
	}
}