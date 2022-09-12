/*
ID: yangchess1
PROG: money
LANG: C++
*/

#include <fstream>
using namespace std;

int main ()
{
	ifstream in;
	ofstream out;
	unsigned short a, b, amount, types, current_value;
	unsigned long long int solutions[10001];

	for (a = 1;a < 10001;a++)
		solutions[a] = 0;

	solutions[0] = 1;

	in.open ("money.in");
	in >> types >> amount;

	for (a = 0;a < types;a++)
	{
		in >> current_value;

		for (b = current_value;b <= amount;b++)
			solutions[b] += solutions[b - current_value];
	}

	in.close ();

	out.open ("money.out");
	out << solutions[amount] << "\n";
	out.close ();

	return 0;
}