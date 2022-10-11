/*
ID: yangchess1
LANG: C++
PROB: wissqu
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
#include <stack>

using namespace std;

struct Move
{
	char letter;
	int x, y;
};

struct SOrder
{
	vector<Move> exist;
	Move update;
};

char grid[6][6]; //Add a row for borders.

//Validate a square for a letter.
bool Validate (char letter, int x, int y)
{
	static int a, b;

	for (a = x - 1;a <= x + 1;a++)
		for (b = y - 1;b <= y + 1;b++)
			if (grid[a][b] == letter)
				return false;

	return true;
}

int main ()
{
	std::ifstream in ("wissqu.in");
	std::ofstream out ("wissqu.out");
	vector<Move> ans;
	stack<SOrder> s;
	SOrder t;
	int a, b, cherd[5], cans = 0;
	char c;
	bool replaced[6][6];

	for (a = 0;a < 6;a++)
		for (b = 0;b < 6;b++)
		{
			grid[a][b] = '-';
			replaced[a][b] = false;
		}

	for (a = 1;a <= 4;a++)
		for (b = 1;b <= 4;b++)
			in >> grid[a][b];

	in.close ();

	cherd[0] = cherd[1] = cherd[2] = cherd[4] = 3;
	cherd[3] = 4;

	//Set up first-move-'D'.
	for (a = 1;a <= 4;a++)
		for (b = 1;b <= 4;b++)
			if (Validate ('D', a, b))
			{
				s.push (SOrder ());
				s.top ().update.letter = 'D';
				s.top ().update.x = a;
				s.top ().update.y = b;
			}

	//Inline DFS.
	while (!s.empty ())
	{
		t = s.top ();
		s.pop ();

		if (t.update.letter >= 97) //A reverse update message is lowercase.
		{
			cherd[grid[t.update.x][t.update.y] - 65]++;
			grid[t.update.x][t.update.y] = t.update.letter - 32;
			replaced[t.update.x][t.update.y] = false;
		}
		else //Uppercase, standard message.
		{
			if (t.exist.size () == 15) //This message completes a sequence, it's an answer.
			{
				t.exist.push_back (t.update);

				//Compare answers lexicographically.
				if (cans++ == 0)
					ans = t.exist;
				else
					for (a = 0;;)
					{
						if (t.exist[a].letter < ans[a].letter)
						{
							ans = t.exist;
							break;
						}
						else if (t.exist[a].letter > ans[a].letter)
							break;
						else
						{
							if (t.exist[a].x < ans[a].x)
							{
								ans = t.exist;
								break;
							}
							else if (t.exist[a].x > ans[a].x)
								break;
							else
							{
								if (t.exist[a].y < ans[a].y)
								{
									ans = t.exist;
									break;
								}
								else if (t.exist[a].y > ans[a].y)
									break;
								else
									a++;
							}
						}
					}
			}
			else
			{
				//Insert a reversal message.
				c = t.update.letter;
				t.update.letter = grid[t.update.x][t.update.y] + 32; //Make lowercase.
				s.push (t);

				//Update the grid and move update to existing.
				cherd[c - 65]--;
				t.update.letter = c;
				grid[t.update.x][t.update.y] = t.update.letter;
				t.exist.push_back (t.update);
				replaced[t.update.x][t.update.y] = true;

				//Search the letters and add any possible updates to stack.
				for (c = 'A';c <= 'E';c++)
					if (cherd[c - 65] > 0)
						for (a = 1;a <= 4;a++)
							for (b = 1;b <= 4;b++)
								if (replaced[a][b] == false && Validate (c, a, b))
								{
									t.update.letter = c;
									t.update.x = a;
									t.update.y = b;
									s.push (t);
								}
			}
		}
	}

	for (a = 0;a < 16;a++)
		out << ans[a].letter << " " << ans[a].x << " " << ans[a].y << "\n";

	out << cans << "\n";
	out.close ();

	return 0;
}