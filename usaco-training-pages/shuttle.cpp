/*
ID: yangchess1
LANG: C++
PROB: shuttle
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main ()
{
	std::ifstream in ("shuttle.in");
	std::ofstream out ("shuttle.out");
	int solution[169], state[25], marbles, csol = 0;
	int a, b, c;

	in >> marbles;
	in.close ();

	for (a = 0;a < marbles;a++)
	{
		state[a] = -1;
		state[a + marbles + 1] = 1;
	}

	state[marbles] = 0;

	//There's a specific pattern to the problem. It consists of 3 steps: interlace the marbles; flip the interlaced marbles to the other side; finish up. There's patterns to the steps too, and it's slightly different for odd and even numbers. The hard part is programming (and finding) the pattern, not time limits or optimizations.
	//Step 1: interlace the marbles (even n: WBWBWB..._, odd n: _WBWBWB...).
	for (a = 0, c = marbles * 2;a < marbles;a++)
	{
		//"Hop" the last 'a' white marbles (first 'a' counting from the right). This is different depending on whether 'a' is odd or even.
		if (a % 2 == 0)
		{
			for (c = marbles * 2, b = 0;c >= 0 && b < a;c--)
			{
				if (state[c] == -1)
				{
					state[c] = 0;
					state[c + 2] = -1;
					solution[csol++] = c;
					b++;
				}
			}
		}
		else
		{
			for (c = 0, b = 0;c <= marbles * 2 && b < a;c++)
			{
				if (state[c] == 1)
				{
					state[c] = 0;
					state[c - 2] = 1;
					solution[csol++] = c;
					b++;
				}
			}
		}

		//"Move" the next white marble on the left of 'c'. This is different depending on whether 'a' is odd or even.
		if (a % 2 == 0)
		{
			for (;c >= 0;c--)
			{
				if (state[c] == -1)
				{
					state[c] = 0;
					state[c + 1] = -1;
					solution[csol++] = c;
					break;
				}
			}
		}
		else
		{
			for (;c <= marbles * 2;c++)
			{
				if (state[c] == 1)
				{
					state[c] = 0;
					state[c - 1] = 1;
					solution[csol++] = c;
					break;
				}
			}
		}
	}

	//Step 2: reverse the interlace (even n: _BWBWBW..., odd n: BWBWBW..._).
	//"Hop" all the W's over, starting from the right. This is different depending on whether 'marbles' is odd or even.
	if (marbles % 2 == 0)
	{
		for (a = marbles * 2;a >= 0;a--)
		{
			if (state[a] == -1)
			{
				state[a] = 0;
				state[a + 2] = -1;
				solution[csol++] = a;
			}
		}
	}
	else
	{
		for (a = 0;a <= marbles * 2;a++)
		{
			if (state[a] == 1)
			{
				state[a] = 0;
				state[a - 2] = 1;
				solution[csol++] = a;
			}
		}
	}

	//Step 3: finish.
	for (a = marbles;a > 0;a--)
	{
		//"Move" the leftmost black marble that can be "moved". This is different depending on whether 'a' is odd or even.
		if (a % 2 == 0)
		{
			for (b = 1;b <= marbles * 2;b++)
			{
				if (state[b] ==	1 && state[b - 1] == 0)
				{
					state[b] = 0;
					state[b - 1] = 1;
					solution[csol++] = b;
					break;
				}
			}
		}
		else
		{
			for (b = marbles * 2 - 1;b >= 0;b--)
			{
				if (state[b] ==	-1 && state[b + 1] == 0)
				{
					state[b] = 0;
					state[b + 1] = -1;
					solution[csol++] = b;
					break;
				}
			}
		}

		//"Hop" the remaining unscanned black marbles. This is different depending on whether 'a' is odd or even.
		if (a % 2 == 0)
		{
			for (c = 0;b <= marbles * 2 && c < a - 1;b++)
			{
				if (state[b] == 1)
				{
					state[b] = 0;
					state[b - 2] = 1;
					solution[csol++] = b;
					c++;
				}
			}
		}
		else
		{
			for (c = 0;b >= 0 && c < a - 1;b--)
			{
				if (state[b] == -1)
				{
					state[b] = 0;
					state[b + 2] = -1;
					solution[csol++] = b;
					c++;
				}
			}
		}
	}

	out << solution[0] + 1;

	for (b = 1, a = 1;a < csol;a++, b++)
	{
		if (b == 20)
		{
			b = 0;
			out << "\n" << solution[a] + 1;
		}
		else
			out << " " << solution[a] + 1;
	}

	out << "\n";
	out.close ();

	return 0;
}