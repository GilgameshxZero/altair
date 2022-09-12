/*
PROG: comehome
ID: yangchess1
LANG: C++
*/

#include <fstream>

using namespace std;

int main ()
{
	ifstream in;
	ofstream out;
	char temp[2];
	int tint, num, a, b, c;
	int dist[53][53][53];
	int ismallest = 1000000000;
	char csmallest = '*';

	//INITIALIZE
	for (b = 0;b < 53;b++)
		for (c = 0;c < 53;c++)
			dist[0][b][c] = 1000000000;

	in.open ("comehome.in");
	in >> num;

	for (a = 0;a < num;a++)
	{
		in >> temp[0];

		if (temp[0] < 95)
			temp[0] -= 38;
		else
			temp[0] -= 96;

		in >> temp[1];

		if (temp[1] < 95)
			temp[1] -= 38;
		else
			temp[1] -= 96;

		in >> tint;

		if (tint < dist[0][temp[0]][temp[1]])
			dist[0][temp[1]][temp[0]] = dist[0][temp[0]][temp[1]] = tint;
	}

	in.close ();

	//START ALGORITHM
	for (a = 1;a < 53;a++)
		for (b = 1;b < 53;b++)
			for (c = 1;c < 53;c++)
			{
				if (dist[a - 1][b][c] <= dist[a - 1][b][a] + dist[a - 1][a][c])
					dist[a][b][c] = dist[a - 1][b][c];
				else
					dist[a][b][c] = dist[a - 1][b][a] + dist[a - 1][a][c];
			}

	for (a = 27;a < 52;a++)
	{
		if (dist[52][52][a] < ismallest)
		{
			ismallest = dist[52][52][a];
			csmallest = a + 38;
		}
	}

	out.open ("comehome.out");
	out << csmallest << " " << ismallest << "\n";
	out.close ();

	return 0;
}