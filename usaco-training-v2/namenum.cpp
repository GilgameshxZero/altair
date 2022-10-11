/*
ID: yangchess1
PROG: namenum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int power (int x, int y)
{
	int a = 1, b;
	
	for (b = 0;b < y;b++)
		a = a * x;

	return a;
}
int main ()
{
	ifstream input;
	ifstream input_2;
	ofstream output;
	int x, y, z = 0, a, b,c = 0;
	string answer[100], acceptable[4000], number, name, temp, letter[8] = {"ABC","DEF","GHI","JKL","MNO","PRS","TUV","WXY"};
	bool hold = false;

	input.open ("namenum.in");
	input >> number;
	input.close ();

	b = number.length ();

	input_2.open ("dict.txt");

	for (x = 0;x < 5000;x++)
	{
		input_2 >> temp;

		if (temp.length () == b)
		{
			acceptable[z] = temp;
			z++;
		}
	}

	for (x = 0;x < b;x++)
	{
		a = number[x] - 50;

		for (y = 0;y < z;y++)
		{
			if (acceptable[y][x] == letter[a][0] || acceptable[y][x] == letter[a][1] || acceptable[y][x] == letter[a][2])
			{
				acceptable[c] = acceptable[y];
				c++;
			}
		}

		z = c;
		c = 0;
	}

	input_2.close ();

	output.open ("namenum.out");

	if (z == 0)
		output << "NONE\n";
	else
	{
		for (x = 0;x < z;x++)
			output << acceptable[x] << "\n";
	}
	
	output.close ();

	return 0;
}