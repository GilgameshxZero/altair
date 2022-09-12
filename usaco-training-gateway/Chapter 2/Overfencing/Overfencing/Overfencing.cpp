/*
ID: yangchess1
PROG: maze1
LANG: C++
*/

#include <fstream>
#include <string>
#include <queue>

using namespace std;

struct Point
{
	bool visited;
	int distance;
	int row;
	int column;
};

Point point[100][38];
char maze[201][77];
queue<Point *> qpnt;

int markdist (Point *p, int distance, int largest)
{
	if (p->distance <= 0)
		p->distance = distance;
	else if (distance < p->distance)
		p->distance = distance;

	if (p->distance > largest)
		return p->distance;
	
	return largest;
}

int abv (int x)
{
	if (x < 0)
		return -x;
	return x;
}

int bfs (Point *p)
{
	/*point[x][y].visited = true;
	
	if (point[x][y].distance <= 0)
		point[x][y].distance = distance;
	else if (distance < point[x][y].distance)
		point[x][y].distance = distance;

	if (point[x][y].distance > dist)
		dist = point[x][y].distance;

	if (maze[(x + 1) * 2 - 2][(y + 1) * 2 - 1] == ' ' && point[x - 1][y].visited == false)
		bfs (x - 1, y, distance + 1);
	if (maze[(x + 1) * 2 - 1][(y + 1) * 2] == ' ' && point[x][y + 1].visited == false)
		bfs (x, y + 1, distance + 1);
	if (maze[(x + 1) * 2][(y + 1) * 2 - 1] == ' ' && point[x + 1][y].visited == false)
		bfs (x + 1, y, distance + 1);
	if (maze[(x + 1) * 2 - 1][(y + 1) * 2 - 2] == ' ' && point[x][y - 1].visited == false)
		bfs (x, y - 1, distance + 1);*/

	/*point[x][y].visited = true;

	if (maze[(x + 1) * 2 - 2][(y + 1) * 2 - 1] == ' ')
		markdist (x - 1, y, distance + 1);
	if (maze[(x + 1) * 2 - 1][(y + 1) * 2] == ' ')
		markdist (x, y + 1, distance + 1);
	if (maze[(x + 1) * 2][(y + 1) * 2 - 1] == ' ')
		markdist (x + 1, y, distance + 1);
	if (maze[(x + 1) * 2 - 1][(y + 1) * 2 - 2] == ' ')
		markdist (x, y - 1, distance + 1);

	if (maze[(x + 1) * 2 - 2][(y + 1) * 2 - 1] == ' ' && point[x - 1][y].visited == false)
		bfs (x - 1, y, distance + 1);
	if (maze[(x + 1) * 2 - 1][(y + 1) * 2] == ' ' && point[x][y + 1].visited == false)
		bfs (x, y + 1, distance + 1);
	if (maze[(x + 1) * 2][(y + 1) * 2 - 1] == ' ' && point[x + 1][y].visited == false)
		bfs (x + 1, y, distance + 1);
	if (maze[(x + 1) * 2 - 1][(y + 1) * 2 - 2] == ' ' && point[x][y - 1].visited == false)
		bfs (x, y - 1, distance + 1);*/

	int a, x, y, distance, largest = 0;

	largest = markdist (p, 1, largest);
	qpnt.push (p);
	qpnt.front ()->visited = true;
	
	for (a = 0;a < qpnt.size ();a++)
	{
		x = qpnt.front ()->row;
		y = qpnt.front ()->column;
		distance = qpnt.front ()->distance;
		qpnt.pop ();
		a--;

		if (maze[(x + 1) * 2 - 2][(y + 1) * 2 - 1] == ' ')
			largest = markdist (&point[x - 1][y], distance + 1, largest);
		if (maze[(x + 1) * 2 - 1][(y + 1) * 2] == ' ')
			largest = markdist (&point[x][y + 1], distance + 1, largest);
		if (maze[(x + 1) * 2][(y + 1) * 2 - 1] == ' ')
			largest = markdist (&point[x + 1][y], distance + 1, largest);
		if (maze[(x + 1) * 2 - 1][(y + 1) * 2 - 2] == ' ')
			largest = markdist (&point[x][y - 1], distance + 1, largest);

		if (maze[(x + 1) * 2 - 2][(y + 1) * 2 - 1] == ' ' && point[x - 1][y].visited == false)
		{
			qpnt.push (&point[x - 1][y]);
			point[x - 1][y].visited = true;
		}
		if (maze[(x + 1) * 2 - 1][(y + 1) * 2] == ' ' && point[x][y + 1].visited == false)
		{
			qpnt.push (&point[x][y + 1]);
			point[x][y + 1].visited = true;
		}
		if (maze[(x + 1) * 2][(y + 1) * 2 - 1] == ' ' && point[x + 1][y].visited == false)
		{
			qpnt.push (&point[x + 1][y]);
			point[x + 1][y].visited = true;
		}
		if (maze[(x + 1) * 2 - 1][(y + 1) * 2 - 2] == ' ' && point[x][y - 1].visited == false)
		{
			qpnt.push (&point[x][y - 1]);
			point[x][y - 1].visited = true;
		}
	}

	return largest;
}

int main ()
{
	ifstream input;
	ofstream output;
	int length, height, count = 0;
	int x[2], y[2];
	int a, b;

	input.open ("maze1.in");
	input >> length >> height;
	input.get ();

	for (a = 0;a < height * 2 + 1;a++)
	{
		for (b = 0;b < length * 2 + 1;b++)
		{
			maze[a][b] = input.get ();

			if ((a == 0 || a == height * 2 || b == 0 || b == length * 2) && maze[a][b] == ' ')
			{
				x[count] = (abv (a - 1) - 1) / 2.0 + 0.5;
				y[count++] = (abv (b - 1) - 1) / 2.0 + 0.5;
				maze[a][b] = '+';
			}
		}

		input.get ();
	}
	
	input.close ();

	for (a = 0;a < height;a++)
	{
		for (b = 0;b < length;b++)
		{
			point[a][b].visited = false;
			point[a][b].distance = 0;
			point[a][b].row = a;
			point[a][b].column = b;
		}
	}

	bfs (&point[x[0]][y[0]]);

	for (a = 0;a < height;a++)
		for (b = 0;b < length;b++)
			point[a][b].visited = false;

	output.open ("maze1.out");
	output << bfs (&point[x[1]][y[1]]) << "\n";
	output.close ();

	return 0;
}