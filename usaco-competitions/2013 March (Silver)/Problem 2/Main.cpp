/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Backup this program every so often in the Backup.txt files in case something goes wrong later.

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

//#define DEBUG 0
#define DEBUG 1

struct Enclosure
{
	int x1, x2, y1, y2;
};

Enclosure enclosure[50000];

int main ()
{
	std::ifstream in ("painting.in");
	std::ofstream out ("painting.out");
	int enc_count, answer;

	in >> enc_count;
	answer = enc_count;

	for (int a = 0;a < enc_count;a++)
		in >> enclosure[a].x1 >> enclosure[a].y1 >> enclosure[a].x2 >> enclosure[a].y2;

	//Loop through all the enclosures and check if the current one is enclosed by any other.
	for (int a = 0;a < enc_count;a++)
	{
		for (int b = 0;b < enc_count;b++)
		{
			if (a != b)
			{
				//If enclosure a is inside b.
				if (enclosure[a].x1 >= enclosure[b].x1 && enclosure[a].x2 <= enclosure[b].x2 && enclosure[a].y1 >= enclosure[b].y1 && enclosure[a].y2 <= enclosure[b].y2)
				{
					//Move to the next a.
					enclosure[a].x1 = enclosure[a].x2 = enclosure[a].y1 = enclosure[a].x2 = -1;
					b = enc_count;
					answer--;
					continue;
				}
			}
		}
	}

	out << answer << "\n";
	out.close ();

	return 0;
}