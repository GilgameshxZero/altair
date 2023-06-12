#include <bits/stdc++.h>
using namespace std;
int main() {
	ifstream in("o.default.txt");
	string S;
	in >> S;
	in.close();
	int N;
	cin >> N;
	cout << (S == "0" ? "alf" : "beata");
	return 0;
}
