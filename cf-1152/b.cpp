#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include <queue>
#include <utility>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef long long ll;

int main ()
{
	ios_base::sync_with_stdio (false);

#ifndef ONLINE_JUDGE
	freopen ("input0.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
#endif

	int x;
	cin >> x;

	string binary = bitset<32>(x).to_string();
	
	vector<int> output;


	bool start = false;
	for (int i = 0; i < 32; ++i) {
		if (start && binary[i - 1] == '0') {
			int n = 32 - i;
			output.insert(output.begin(), 32 - i);
		}
		if (!(start) && binary[i] == '1') {
			start = true;
		}
	}
	if (binary[31] == '1') {
		output.insert(output.begin(), 0);
	} else {
		output.insert(output.begin(), 1);
	}

	cout << 2*output.size()-1 << endl;

	for (int j = 0; j < output.size(); ++j) {
		cout << output[j] << " ";
	}

	return 0;
}