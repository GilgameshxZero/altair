#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>
#include <functional>

using namespace std;

int main () {
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	int n;
	in >> n;

	vector<int> prc (n);
	int total = 0;
	for (int a = 0;a < n;a++)
		in >> prc[a],
		total += prc[a];

	sort (prc.begin (), prc.end (), greater<int> ());
	for (int a = 2;a < n;a += 3)
		total -= prc[a];

	out << total;

	in.close ();
	out.close ();

	return 0;
}