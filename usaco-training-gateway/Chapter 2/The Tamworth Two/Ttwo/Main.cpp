/*
ID: yangchess1
PROG: ttwo
LANG: C++
*/

#include <fstream>
#include <string>
using namespace std;

struct point
{
	int x;
	int y;
	int direction;
};

int main ()
{
	ifstream in;
	ofstream out;
	point cow, farmer;
	int a, b, c, d, e, f, minute = 0;
	char map[10][10], temp;

	cow.direction = farmer.direction = 0; //Up

	in.open ("ttwo.in");
	
	for (a = 0;a < 10;a++)
	{
		for (b = 0;b < 10;b++)
		{
			temp = in.get ();

			if (temp == 'C')
			{
				cow.x = a;
				cow.y = b;
				map[a][b] = '.';
			}
			if (temp == 'F')
			{
				farmer.x = a;
				farmer.y = b;
				map[a][b] = '.';
			}
			else
				map[a][b] = temp;
		}

		in.get (); //Dump end of line
	}

	in.close ();

	while (minute <= 160000)
	{
		//Test if same
		if (farmer.x == cow.x && farmer.y == cow.y)
			break;

		//Move farmer
		if (farmer.direction == 0)
		{
			if (farmer.x == 0 || map[farmer.x - 1][farmer.y] == '*')
				farmer.direction = 1;
			else if (map[farmer.x - 1][farmer.y] != '*')
				farmer.x--;
		}
		else if (farmer.direction == 1)
		{
			if (farmer.y == 9 || map[farmer.x][farmer.y + 1] == '*')
				farmer.direction = 2;
			else if (map[farmer.x][farmer.y + 1] != '*')
				farmer.y++;
		}
		else if (farmer.direction == 2)
		{
			if (farmer.x == 9 || map[farmer.x + 1][farmer.y] == '*')
				farmer.direction = 3;
			else if (map[farmer.x + 1][farmer.y] != '*')
				farmer.x++;
		}
		else if (farmer.direction == 3)
		{
			if (farmer.y == 0 || map[farmer.x][farmer.y - 1] == '*')
				farmer.direction = 0;
			else if (map[farmer.x][farmer.y - 1] != '*')
				farmer.y--;
		}

		//Move cow
		if (cow.direction == 0)
		{
			if (cow.x == 0 || map[cow.x - 1][cow.y] == '*')
				cow.direction = 1;
			else if (map[cow.x - 1][cow.y] != '*')
				cow.x--;
		}
		else if (cow.direction == 1)
		{
			if (cow.y == 9 || map[cow.x][cow.y + 1] == '*')
				cow.direction = 2;
			else if (map[cow.x][cow.y + 1] != '*')
				cow.y++;
		}
		else if (cow.direction == 2)
		{
			if (cow.x == 9 || map[cow.x + 1][cow.y] == '*')
				cow.direction = 3;
			else if (map[cow.x + 1][cow.y] != '*')
				cow.x++;
		}
		else if (cow.direction == 3)
		{
			if (cow.y == 0 || map[cow.x][cow.y - 1] == '*')
				cow.direction = 0;
			else if (map[cow.x][cow.y - 1] != '*')
				cow.y--;
		}

		minute++;
	}
	
	if (minute > 160000)
		minute = 0;

	out.open ("ttwo.out");
	out << minute << "\n";
	out.close ();

	return 0;
}