/*
ID: yangchess1
PROG: inflate
LANG: C++
*/
//Knapsack unbounded algorithm.

#include <fstream>

//Constants
const unsigned short MAXPROBLEMS = 10000;

using namespace std;

int main ()
{
	ifstream in;
	ofstream out;
	unsigned int best[MAXPROBLEMS + 1];
	unsigned short time, classes, length, points;
	unsigned short a, b;

	in.open ("inflate.in");
	in >> time >> classes;

	//Initialize the `best` array to 0. The best array is an array representing the best number of points for a specific time limit
	for (a = 0;a < MAXPROBLEMS + 1;a++)
		best[a] = 0;

	for (a = 0;a < classes;a++)
	{
		//Get another problem
		in >> points >> length;

		//Greedy algorithm: update best times (look at the time needed to solve this specific problem (`length`) and if the best[time - length] + pts (if we use this problem instead) is better than best[time], update that)
		for (b = length;b <= time;b++)
		{
			if (best[b - length] + points > best[b])
				best[b] = best[b - length] + points;
		}
	}
	
	in.close ();
	out.open ("inflate.out");
	
	//Because the best number of points is always when there is more time, output the last best[] variable
	out << best[time] << "\n";
	out.close ();

	return 0;
}