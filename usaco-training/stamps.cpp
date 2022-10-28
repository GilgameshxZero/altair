/*
ID: yangchess1
PROG: stamps
LANG: C++
*/

#include <fstream>
#include <iostream>

using namespace std;

int bestcstamp[2100000];

int main ()
{
	ifstream in;
	ofstream out;
	const int INFINITY = 1000000000;
	int cstamp, cstampval, stampval[50], emptycstamp = INFINITY;
	int a, b;

	cerr << "Initializing...\n";

	for (a = 0;a < 2000000;a++)
		bestcstamp[a] = INFINITY;

	cerr << "Getting cstamp and cstampval...\n";

	in.open ("stamps.in");
	in >> cstamp >> cstampval;
	in.get ();

	cerr << "Getting stampval...\n";

	//As they are created, add elements to the vector with cstamps = 1
	for (a = 0;a < cstampval;a++)
	{
		in >> stampval[a];
		cerr << "\tStampval optained: " << stampval[a] << "\n";

		bestcstamp[stampval[a] - 1] = 1;
	}

	cerr << "Opening stamps.out...\n";

	in.close ();
	out.open ("stamps.out");

	cerr << "Base case test...\n";

	//Test for base case: 1
	if (bestcstamp[0] == 0)
	{
		out << "0\n";
		out.close ();
		return 0;
	}

	cerr << "Program: Maintainence...\n";

	//For every number we have a value for, we try to add every stamp onto it to create another postage and if that postage cstamp is smaller than the existing, we update it, until we reach a number with value INFINITY, and then we output that num - 1
	for (a = 1;true;a++)
	{
		//If the value we are going to test does not exist or has value INFINITY, we exit
		if (bestcstamp[a - 1] == INFINITY)
		{
			out << a - 1 << "\n";
			out.close ();
			return 0;
		}

		for (b = 0;b < cstampval;b++)
		{
			//Update the value if needed
			if (1 + bestcstamp[a - 1] < bestcstamp[a + stampval[b] - 1] && bestcstamp[a - 1] < cstamp)
				bestcstamp[a + stampval[b] - 1] = 1 + bestcstamp[a - 1];
		}
	}

	cerr << "Finished!\n";

	return 1;
}