/*
ID: yangchess1
PROG: clocks
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string moves[9] = {"ABDE","ABC","BCEF","ADG","BDEFH","CFI","DEGH","GHI","EFHI"}, answer;
int clocks[9], mirror[9], times[9];
bool done = false;
void solve (int move)
{
	int a, b, c = 0, d;
	char e;

	if (done == false)
	{
		for (a = 0;a < 4;a++)
		{
			times[move] = a;

			if (move > 0)
				solve (move - 1);
			else
			{
				for (b = 0;b < 9;b++)
				{
					for (c = 0;c < times[b];c++)
					{
						for (d = 0;d < moves[b].length ();d++)
						{
							mirror[moves[b][d] - 65] += 3;
						}
					}
				}

				c = 0;

				for (b = 0;b < 9;b++)
				{
					if (mirror[b] % 12 == 0)
						c++;
				}

				if (c == 9)
				{
					for (b = 0;b < 9;b++)
					{
						for (d = 0;d < times[b];d++)
						{
							e = b + 49;
							answer += e;
						}
					}

					done = true;
					break;
				}

				for (b = 0;b < 9;b++)
					mirror[b] = clocks[b];
			}

			if (c == 9)
				break;
		}
	}
}
int main ()
{
	ifstream input;
	ofstream output;
	int a;

	input.open ("clocks.in");
	
	for (a = 0;a < 9;a++)
	{
		input >> clocks[a];
		mirror[a] = clocks[a];
	}

	input.close ();
	output.open ("clocks.out");

	solve (8);

	for (a = 0;a < answer.length () - 1;a++)
		output << answer[a] << " ";

	output << answer[answer.length () - 1] << "\n";

	output.close ();

	return 0;
}