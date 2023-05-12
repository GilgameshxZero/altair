/*
ID: yangchess1
LANG: C++
PROG: game1
*/

#include <fstream>

int main ()
{
	std::ifstream in ("game1.in");
	std::ofstream out ("game1.out");
	int board_size, *total, **best, a, b;

	in >> board_size;

	//Allocate total array and best array
	total = new int [board_size + 1]; //total[board number] = sum of the first 'board number' boards
	best = new int *[board_size - 1]; //best[starting board index from 0][ending board index from 0 - 1]

	for (a = 0;a < board_size - 1;a++)
		best[a] = new int [board_size - 1];

	//Initialize total[0] and total[1]
	total[0] = 0; //Sum of the first '0' boards
	in >> total[1]; //First board

	//Input the elements and save them in the total array. While doing this, also calculate best array.
	for (a = 1;a < board_size;a++)
	{
		in >> total[a + 1];
		total[a + 1] += total[a];

		if (total[a + 1] - total[a] >= total[a] - total[a - 1]) //If this board is bigger than the last
			best[a - 1][a - 1] = total[a + 1] - total[a]; //The best of these two boards is the bigger one
		else
			best[a - 1][a - 1] = total[a] - total[a - 1]; //Other case

		//Calculate best of a-2...a (actually a-1 in best), a-3...a, a-4...a, ... using recurrence relations
		for (b = a - 2;b >= 0;b--)
		{
			if (best[b][a - 2] >= best[b + 1][a - 1])
				best[b][a - 1] = (total[a + 1] - total[b]) - best[b + 1][a - 1];
			else
				best[b][a - 1] = (total[a + 1] - total[b]) - best[b][a - 2];
		}
	}

	in.close ();
	out << best[0][board_size - 2] << " " << total[board_size] - best[0][board_size - 2] << "\n";
	out.close ();

	//Free memory
	delete[] total;

	for (a = 0;a < board_size - 1;a++)
		delete[] best[a];

	delete[] best;

	return 0;
}