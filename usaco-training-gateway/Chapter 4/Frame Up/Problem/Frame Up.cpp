/*
ID: yangchess1
LANG: C++
PROB: frameup
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

int cframe = 0;
bool restriction[26][26], frames[26];

//Rescursive function used to find solutions.
void FindSolutions (vector<string> *solution, string order)
{
	vector<int> children;
	int a, b;

	if (order.length () == cframe)
	{
		solution->push_back (order);
		return;
	}

	for (a = 0;a < 26;a++)
	{
		if (frames[a] == true)
		{
			//Check if this vertice has an in-degree of 0.
			for (b = 0;b < 26;b++)
				if (restriction[b][a] == true)
					break;

			//Remove this vertice from the graph, and recurse.
			if (b == 26)
			{
				for (b = 0;b < 26;b++)
				{
					if (restriction[a][b] == true)
					{
						restriction[a][b] = false;
						children.push_back (b);
					}
				}

				frames[a] = false;
				FindSolutions (solution, static_cast<char>(a + 'A') + order);
				frames[a] = true;

				for (b = 0;b < children.size ();b++)
					restriction[a][children[b]] = true;

				children.clear ();
			}
		}
	}
}

int main ()
{
	std::ifstream in ("frameup.in");
	std::ofstream out ("frameup.out");
	vector<string> solution;
	int cx, cy, top, left, right, bottom;
	char matrix[30][30];
	int a, b, c;

	in >> cy >> cx;

	for (a = 0;a < cy;a++)
		for (b = 0;b < cx;b++)
			in >> matrix[a][b];

	in.close ();

	for (a = 0;a < 26;a++)
	{
		frames[a] = false;

		for (b = 0;b < 26;b++)
			restriction[a][b] = false;
	}

	//Determine the locations of all the frames. Do so by finding all points of the frame we can see, and taking the largest and smallest x and y locations to locate the border of that frame.
	for (a = 'A';a <= 'Z';a++) //Search for the frame lettered a.
	{
		top = cy;
		left = cx;
		right = -1;
		bottom = -1;

		for (b = 0;b < cy;b++)
		{
			for (c = 0;c < cx;c++)
			{
				if (matrix[b][c] == a)
				{
					if (b < top)
						top = b;
					if (c < left)
						left = c;
					if (c > right)
						right = c;
					if (b > bottom)
						bottom = b;
				}
			}
		}

		//Did we find this frame?
		if (top != cy)
		{
			//Determine restrictions with this frame. If another letter appears on the track of one frame, we specify a restriction that the frame of the other letter is atop the original frame.
			frames[a - 'A'] = true;
			cframe++;

			//Top edge.
			for (b = left;b <= right;b++)
				if (matrix[top][b] != a)
					restriction[matrix[top][b] - 'A'][a - 'A'] = true;
		
			//Bottom edge.
			for (b = left;b <= right;b++)
				if (matrix[bottom][b] != a)
					restriction[matrix[bottom][b] - 'A'][a - 'A'] = true;
		
			//Left edge.
			for (b = top;b <= bottom;b++)
				if (matrix[b][left] != a)
					restriction[matrix[b][left] - 'A'][a - 'A'] = true;
		
			//Right edge.
			for (b = top;b <= bottom;b++)
				if (matrix[b][right] != a)
					restriction[matrix[b][right] - 'A'][a - 'A'] = true;
		}
	}

	//Perform a loop similar to Floyd-Warshall on our restrictions. With this Floyd-Warshall, we can find all restrictions such as b->c provided b->a and a->c.
	for (a = 0;a < 26;a++)
	{
		for (b = 0;b < 26;b++)
		{
			for (c = 0;c < 26;c++)
			{
				if (restriction[b][a] == true && restriction[a][c] == true)
					restriction[b][c] = true;
			}
		}
	}

	FindSolutions (&solution, "");

	sort (solution.begin (), solution.end ());

	for (a = 0;a < solution.size ();a++)
		out << solution[a] << "\n";

	out.close ();

	return 0;
}