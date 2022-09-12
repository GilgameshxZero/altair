/*
ID: yangchess1
PROG: cowtour
LANG: C++
*/

#include <fstream>
#include <cmath>

using namespace std;

struct Point
{
	int x, y, group;
	double dist;
};

bool matrix[150][150];
int num;
Point pasture[150];

double pythag (Point a, Point b)
{
	return sqrt (static_cast<double>((a.x - b.x)*(a.x - b.x)) + static_cast<double>((a.y - b.y)*(a.y - b.y)));
}

void mark (int field, int group)
{
	int a;

	pasture[field].group = group;

	for (a = 0;a < num;a++)
	{
		if (matrix[field][a] && pasture[a].group == -1)
			mark (a, group);
	}
}

int main ()
{
	ifstream in;
	ofstream out;
	int ngroup = 0, a, b, c;
	double dist[150][150], diam[150], smallest, largest, t;

	//Initialize
	for (a = 0;a < 150;a++)
		for (b = 0;b < 150;b++)
			dist[a][b] = 100000000.0;

	in.open ("cowtour.in");
	in >> num;

	//Get points
	for (a = 0;a < num;a++)
		in >> pasture[a].x >> pasture[a].y;

	in.get ();

	//Mark edges
	for (a = 0;a < num;a++)
	{
		for (b = 0;b < num;b++)
		{
			matrix[a][b] = in.get () - 48;

			if (matrix[a][b])
				dist[a][b] = pythag (pasture[a], pasture[b]);
		}

		in.get ();
	}

	//DFS the groups out
	for (a = 0;a < num;a++)
		pasture[a].group = -1;

	for (a = 0;a < num;a++)
	{
		if (pasture[a].group == -1) //If not assigned a group yet
			mark (a, ngroup++);
	}

	//Floyd Warshall the shortest paths
	for (a = 0;a < num;a++)
		for (b = 0;b < num;b++)
			for (c = 0;c < num;c++)
			{
				if (dist[b][a] + dist[a][c] < dist[b][c])
					dist[b][c] = dist[b][a] + dist[a][c];
			}

	//Find longest distance from every pasture
	for (a = 0;a < num;a++)
	{
		largest = 0;

		for (b = 0;b < num;b++)
		{
			if (b != a && dist[a][b] != 100000000.0 && dist[a][b] > largest)
				largest = dist[a][b];
		}

		pasture[a].dist = largest;
	}

	//Find diameter of each field group
	for (a = 0;a < 150;a++)
		diam[a] = 0;

	for (a = 0;a < num;a++)
	{
		if (pasture[a].dist > diam[pasture[a].group])
			diam[pasture[a].group] = pasture[a].dist;
	}

	//Draw path between all points and test for smallest diameter
	smallest = 100000000.0;

	for (a = 0;a < num;a++)
	{
		for (b = 0;b < num;b++)
		{
			if (pasture[a].group != pasture[b].group)
			{
				largest = t = pythag (pasture[a], pasture[b]) + pasture[a].dist + pasture[b].dist;
				t = diam[pasture[a].group];

				if (t > largest)
					largest = t;

				t = diam[pasture[b].group];

				if (t > largest)
					largest = t;

				if (largest < smallest)
					smallest = largest;
			}
		}
	}

	//Output answer
	out.open ("cowtour.out");
	out.setf (ios::fixed);
	out.precision (6);
	out << smallest << "\n";
	out.close ();

	return 0;
}