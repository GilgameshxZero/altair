/*
ID: yangchess1
PROG: runround
LANG: C++
*/
//Description: Find first runaround number bigger than input. A runaround number is number like 81362, where when
//going number of digits on current digit, end up with first and visit every digit when starting with first. To 
//be a runaround number, the number must also have unique digits and no 0's. For example 81362: 8 -> 6 -> 2 -> 1 -> 3 -> 8.

//Headers and definitions
#include <fstream>
#include <string>
using namespace std;

//Globals

//Prototypes
bool is_runaround (unsigned long long int number);
unsigned long long int exponent (unsigned long long int base, unsigned long long int exponent);

//Functions
int main ()
{
	ifstream input;
	ofstream output;
	unsigned long long int start;

	input.open ("runround.in");			//Input starting number
	input >> start;
	input.close ();

	while (true)			//Solve problem
	{
		start++;

		if (is_runaround (start) == true)			//If runaround, output and exit
		{
			output.open ("runround.out");
			output << start << "\n";
			output.close ();
			return 0;
		}
	}
}
unsigned long long int exponent (unsigned long long int base, unsigned long long int exponent)
{
	int a = base;

	base = 1;

	for (;exponent > 0;exponent--)
		base *= a;

	return base;
}
bool is_runaround (unsigned long long int number)
{
	int a, b;
	int length = 0, start = 0;
	string x;
	long long n = 1;
	bool flag = true, digits[10];

	for (a = 0;a < 9;a++)
		digits[a] = false;

	for (a = 1;;a++)			//Find length of number
	{
		if (number / n > 10)
			length++;
		else
			break;
		n *= 10;
	}

	length++;

	for (a = length - 1;a >= 0;a--)			//Convert number into string x
	{
		x += static_cast<char>(48 + number / exponent (10,a));
		number %= exponent (10,a);
	}

	for (a = 0;a < length;a++)			//Test for unique digits and no 0's
	{
		if (x[a] == '0')
			return false;

		if (digits[x[a] - 48 - 1] == true)
			return false;

		digits[x[a] - 48 - 1] = true;
	}

	a = 0;

	while (true)			//Test if number is runaround
	{
		if (x[a] == 'X')			//If reaches a reached number before going back to beginning, exit
		{
			flag = false;
			break;
		}

		b = x[a] - 48 + a;			//Calculate next visit digit
		x[a] = 'X';

		a = b % length;

		if (a == 0)			//If back to beginning, check to see if all 'X's; if so, true, else, false
		{
			for (b = 0;b < length;b++)
			{
				if (x[b] != 'X')
				{
					flag = false;
					break;
				}
			}

			break;
		}
	}

	return flag;

}