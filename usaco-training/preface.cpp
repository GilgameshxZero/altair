/*
ID: yangchess1
PROG: preface
LANG: C++
*/
#include <fstream>
#include <string>
using namespace std;
string translate (int number);
int main ()
{
	ifstream in;
	ofstream out;
	int pages, largest;
	int a, b, c;
	string number;
	long long count[7];
	char numeral[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

	in.open ("preface.in");
	in >> pages;
	in.close ();

	for (a = 0;a < 7;a++)
		count[a] = 0;

	for (a = 1;a <= pages;a++)
	{
		number = translate (a);

		for (b = 0;b < 7;b++)
			for (c = 0;c < number.length ();c++)
				if (number[c] == numeral[b])
					count[b]++;
	}

	out.open ("preface.out");

	for (a = 0;a < 7;a++)
		if (count[a] > 0)
			largest = a + 1;
	
	for (a = 0;a < largest;a++)
		out << numeral[a] << " " << count[a] << "\n";

	out.close ();

	return 0;
}
string translate (int number)
{
	string rtrn;
	int a;

	for (a = 0;a < number / 1000;a++)
		rtrn += "M";

	number = number % 1000;

	if (number / 100 == 4)
		rtrn += "CD";
	if (number / 100 == 9)
		rtrn += "CM";
	if (number / 100 >= 5 && number / 100 != 9)
	{
		rtrn += "D";
		number -= 500;
	}
	if (number / 100 < 4)
	{
		for (a = 0;a < number / 100;a++)
			rtrn += "C";
	}

	number = number % 100;

	if (number / 10 == 4)
		rtrn += "XL";
	if (number / 10 == 9)
		rtrn += "XC";
	if (number / 10 >= 5 && number / 10 != 9)
	{
		rtrn += "L";
		number -= 50;
	}
	if (number / 10 < 4)
	{
		for (a = 0;a < number / 10;a++)
			rtrn += "X";
	}

	number = number % 10;

	if (number == 4)
		rtrn += "IV";
	if (number == 9)
		rtrn += "IX";
	if (number >= 5 && number != 9)
	{
		rtrn += "V";
		number -= 5;
	}
	if (number < 4)
	{
		for (a = 0;a < number;a++)
			rtrn += "I";
	}

	return rtrn;
}