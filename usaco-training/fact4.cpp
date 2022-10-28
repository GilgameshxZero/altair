/*
ID: yangchess1
PROG: fact4
LANG: C++
*/

/*
Algorithm: SIMPLE
*/

#include <fstream>

int main ()
{
	using namespace std;

	ifstream in;
	ofstream out;
	int num, extra2 = 0, rdigit = 1;
	int a, b;

	in.open ("fact4.in");
	in >> num;
	in.close ();

	for (a = 2;a <= num;a++)
	{
		b = a;

		while (b % 2 == 0)
		{
			extra2++;
			b /= 2;
		}

		while (b % 5 == 0)
		{
			extra2--;
			b /= 5;
		}

		//Last digit
		rdigit  = (rdigit * b) % 10;
	}

	//* on extra2
	for (a = 0;a < extra2;a++)
		rdigit = (rdigit * 2) % 10;

	out.open ("fact4.out");
	out << rdigit << "\n";
	out.close ();

	return 0;
}