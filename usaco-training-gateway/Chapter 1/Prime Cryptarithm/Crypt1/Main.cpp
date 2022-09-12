/*
ID:yangchess1
PROG:crypt1
LANG:C++
*/
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

int digits[10], numbers;

int power (int x, int y)
{
	int a, b = 1;

	for (a = 0;a < y;a++)
		b = b * x;

		return b;
}

int digit (int number, int place)
{
	
	int a = power (10,place);

	if (place == 0)
		return number % 10;
	else
	{
		return (number % (a * 10) - number % a) / a;
	}
}

int places (int number)
{
	int x, y = 0,a;

	for (x = 7;x--;x >= 0)
	{
		a = digit (number,x);
		if (digit (number,x) != 0)
			break;
		else
			y++;
	}

	return 7 - y;
}

bool valid (int a)
{
	int x, y, z = 0, b = places (a),c;

	for (x = 0;x < b;x++)
	{
		c = digit (a,x);
		for (y = 0;y < numbers;y++)
		{
			if (c == digits[y])
				z++;
		}
	}

	if (z == b)
		return true;
	else
		return false;
}

int main ()
{
	ifstream input;
	ofstream output;
	int a, b, c, d, e, one = 0, two = 0, three, four, five, solutions = 0;

	input.open ("crypt1.in");
	input >> numbers;

	for (a = 0;a < numbers;a++)
		input >> digits[a];

	input.close ();

	for (a = 0;a < numbers;a++)
	{
		one += 100 * digits[a];
		for (b = 0;b < numbers;b++)
		{
			one += 10 * digits[b];
			for (c = 0;c < numbers;c++)
			{
				one += digits[c];
				for (d = 0;d < numbers;d++)
				{
					two += 10 * digits[d];
					for (e = 0;e < numbers;e++)
					{
						two += digits[e];

						three = digit (two,0) * one;
						four = digit (two,1) * one;
						five = two * one;

						if (valid (three) && valid (four) && valid (five) && places (three) == 3 && places (four) == 3 && places (five) == 4)
							solutions++;

						two -= digits[e];
					}
					two = 0;
				}
				one -= digits[c];
			}
			one -= digits[b] * 10;
		}
		one = 0;
	}

	output.open ("crypt1.out");
	output << solutions << "\n";
	output.close ();

	return 0;
}