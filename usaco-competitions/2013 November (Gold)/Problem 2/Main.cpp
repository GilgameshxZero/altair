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

int main ()
{
	std::ifstream in ("sight.in");
	std::ofstream out ("sight.out");
	vector<pair<double, bool> > angle;
	const double PI = 3.141592653589793236433;
	int N, R, ans = 0, num = 0;

	in >> N >> R;
	for (long long a = 0, x, y;a < N;a++)
	{
		in >> x >> y;
		double D = sqrt ((double)(x * x + y * y)), theta = atan2 ((double)y, (double)x), alpha = acos ((double)R/D);

		angle.push_back (make_pair (theta - alpha, true));
		angle.push_back (make_pair (theta + alpha, false));

		//num is init to # of points right of x = R line.
		if (x >= R)
			num++;
	}

	for (int a = 0;a < angle.size ();a++)
	{
		if (angle[a].first < 0)
			angle[a].first += 2 * PI;
		if (angle[a].first > 2 * PI)
			angle[a].first -= 2 * PI;
	}

	sort (angle.begin (), angle.end ());
	//ans = num * (num - 1) / 2;

	for (int a = 0;a < angle.size ();a++)
	{
		if (angle[a].second == true) //Add.
			ans += num++;
		else
			num--;
	}

	out << ans << "\n";
	out.close ();

	return 0;
}