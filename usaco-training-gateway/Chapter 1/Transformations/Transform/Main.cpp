/*
ID: yangchess1
PROG: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main ()
{
	ifstream input;
	ofstream output;
	int number, x, y, a, b, before[10][10], after[10][10], middle[10][10], same = 0;
	bool answer[6], five[3];
	string temp;

	input.open ("transform.in");
	input >> number;

	for (x = 0;x < 6;x++)
		answer[x] = false;

	for (x = 0;x < 3;x++)
		five[x] = false;

	for (x = 0;x < number;x++)
	{
		input >> temp;

		for (y = 0;y < number;y++)
			before[x][y] = temp[y];
	}

	for (x = 0;x < number;x++)
	{
		input >> temp;

		for (y = 0;y < number;y++)
			after[x][y] = temp[y];
	}

	input.close ();

	//Test for #1
	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (before[y][x] == after[x][number - 1 - y])
				same++;
		}
	}

	if (same == number * number)
		answer[0] = true;

	same = 0;

	//Test for #2
	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (before[y][x] == after[number - 1 - y][number - 1 - x])
				same++;
		}
	}

	if (same == number * number)
		answer[1] = true;

	same = 0;

	//Test for #3
	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (before[y][x] == after[number - 1 - x][y])
				same++;
		}
	}

	if (same == number * number)
		answer[2] = true;

	same = 0;

	//Test for #4
	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (before[y][x] == after[y][number - 1 - x])
				same++;
		}
	}

	if (same == number * number)
		answer[3] = true;

	same = 0;

	//Test for #5
	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			middle[y][number - 1 - x] = before[y][x];
		}
	}

	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (middle[y][x] == after[x][number - 1 - y])
				same++;
		}
	}

	if (same == number * number)
		five[0] = true;

	same = 0;

	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (middle[y][x] == after[number - 1 - y][number - 1 - x])
				same++;
		}
	}

	if (same == number * number)
		five[1] = true;

	same = 0;

	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (middle[y][x] == after[number - 1 - x][y])
				same++;
		}
	}

	if (same == number * number)
		five[2] = true;

	if (five[0] == true || five[1] == true || five[2] == true)
		answer[4] = true;

	same = 0;

	//Test for #6
	for (x = 0;x < number;x++)
	{
		for (y = 0;y < number;y++)
		{
			if (before[x][y] == after[x][y])
				same++;
		}
	}

	if (same == number * number)
		answer[5] = true;

	output.open ("transform.out");

	for (x = 0;x < 6;x++)
	{
		if (answer[x] == true)
		{
			output << x + 1 << "\n";
			break;
		}
	}

	if (answer[0] == false && answer[1] == false && answer[2] == false && answer[3] == false && answer[4] == false && answer[5] == false) 
		output << "7\n";

	output.close ();

	return 0;
}