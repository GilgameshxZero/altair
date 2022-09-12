/*
ID:yangchess1
PROG:calfflac
LANG:C++
*/
#include <fstream>
#include <string>
#include <stdio.h>
int map[30000], start, end, longest = 0, length;
std::string simplify;
void find (int left, int right)
{
	while (left >= 0 && right <= length)
	{
		if (simplify[left] == simplify[right])
		{
			left--;
			right++;
		}
		else
			break;
	}

	if (right - left - 1 > longest)
	{
		longest = right - left - 1;
		start = map[left + 1];
		end = map[right - 1];
	}
}
int main ()
{
	std::ifstream input;
	std::ofstream output;
	char a;
	std::string text;
	int x, y, z = 0;

	input.open ("calfflac.in");

	while (!input.eof ())
	{
		a = input.get ();
		if (a >= 0)
			text += a;
	}

	y = text.length ();

	for (x = 0;x < y;x++)
	{
		if (text[x] > 64 && text[x] < 91)
		{
			simplify += (char)(text[x] + 32);
			map[z] = x;
			z++;
		}
		else if (text[x] > 96 && text[x] < 123)
		{
			simplify += text[x];
			map[z] = x;
			z++;
		}
	}

	length = simplify.length ();

	for (x = 1;x <= length;x++)
	{
		find (x - 1,x + 1);
		find (x,x + 1);
	}

	output.open ("calfflac.out");
	output << longest << "\n";

	if (longest == 1)
		output << text[0];
	else
	{
		for (x = start;x <= end;x++)
			output << text[x];
	}

	output << "\n";
	output.close ();

	return 0;
}