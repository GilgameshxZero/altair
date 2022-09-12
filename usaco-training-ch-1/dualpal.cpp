/*
ID: yangchess1
PROG: dualpal
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int mod (int x, int y)
{
	return x - ((int)(x / y)) * y;
}
int floor (int x, int y)
{
	return (int)(x / y);
}
string convert (int x,int base)
{
	string rtrn;
	int y = x;
	char a;

	while (true)
	{
		if (mod (y,base) < 10)
			rtrn = (char)((char)(mod (y,base)) + 48) + rtrn;
		else if (mod (y,base) < 20)
		{
			a = (char)(((char)(mod (y,base) - 10)) + 17);
			rtrn = (char)(a + 48) + rtrn;
		}
		else
			rtrn = 'K' + rtrn;

		y = floor (y,base);

		if (y == 0)
			break;
	}

	return rtrn;
}
bool palin (string x)
{
	int a;
	bool rtrn = true;

	for (a = 0;a < floor (x.length (),2);a++)
	{
		if (x[a] != x[x.length () - a - 1])
			rtrn = false;
	}

	return rtrn;
}
int main ()
{
	ifstream input;
	ofstream output;
	int numbers, barrier;
	int a, b = 0;

	input.open ("dualpal.in");
	input >> numbers >> barrier;
	input.close ();

	output.open ("dualpal.out");

	while (numbers != 0)
	{
		barrier++;

		for (a = 2;a < 11;a++)
		{
			if (palin (convert (barrier,a)))
				b++;
		}

		if (b >=2)
		{
			output << barrier << "\n";
			numbers--;
		}

		b = 0;
	}

	output.close ();

	return 0;
}