#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int need[1000001];

int main () {
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	int n;
	in >> n;

	vector<int> prc (n);
	for (int a = 0; a < n; a++)
		in >> prc[a];

	int ans = 0;

	for (int a = 0;a < n;a++)
	{
		if (need[prc[a]] > 0)
			need[prc[a]]--;
		else
			ans++;
		if (prc[a] != 1)
			need[prc[a] - 1]++;
	}

	out << ans;

	in.close ();
	out.close ();

	return 0;
}