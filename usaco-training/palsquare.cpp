/*
ID: yangchess1
PROG: palsquare
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
int power (int x, int y)
{
	if (y == 0)
		return 1;
	return x * power (x, y - 1);
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
	int base, x;

	input.open ("palsquare.in");
	input >> base;
	input.close ();

	output.open ("palsquare.out");

	for (x = 1;x <= 300;x++)
	{
		if (palin (convert (power (x,2),base)))
			output << convert (x,base) << " " << convert (power (x,2),base) << "\n";
	}

	output.close ();

	return 0;
}