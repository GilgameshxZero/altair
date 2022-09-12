/*
ID: yangchess1
PROG: ride
LANG: C++
*/

#include <fstream>
#include <string>

using namespace std;

int value (string);

int main ()
{
	ifstream input;
	ofstream output;
	string a, b;

	input.open ("ride.in");
	input >> a >> b;
	input.close ();
	output.open ("ride.out");

	if (value (a) == value (b))
		output << "GO\n";
	else
		output << "STAY\n";

	output.close ();

	return 0;
}
int value (string name)
{
	int rtrn = 1, a;

	for (a = 0;a < name.length ();a++)
		rtrn *= (name[a] - 64);

	return rtrn % 47;
}