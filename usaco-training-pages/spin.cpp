/*
ID: yangchess1
LANG: C++
PROG: spin
*/

//Algorithm: 360 seconds will return all to normal. So look there.

#include <fstream>
#include <vector>
#include <iostream>

struct Wheel
{
	int speed;
	int cwedge;
	int wedgeext[100];
	int wedgestart[100];
};

void add_intersect (Wheel *a, int astart, int aext, int bstart, int bext)
{
	int rstart, rend, aend = astart + aext, bend = bstart + bext;

	//Get them to the same level
	if (aend >= 360)
	{
		if (bend < 360)
		{
			bstart += 360;
			bend += 360;
		}
	}
	else
	{
		if (bend >= 360)
		{
			astart += 360;
			aend += 360;
		}
	}

	//Largest start, Lowest end
	if (astart > bstart)
		rstart = astart;
	else
		rstart = bstart;

	if (aend < bend)
		rend = aend;
	else
		rend = bend;

	//Add intersection if intersects
	if (rend >= rstart)
	{
		if (rstart > 360)
		{
			rstart -= 360;
			rend -= 360;
		}

		(*a).wedgestart[(*a).cwedge] = rstart;
		(*a).wedgeext[(*a).cwedge++] = rend - rstart;
	}
}

int main ()
{
	std::ifstream in;
	std::ofstream out;
	std::vector<Wheel> wheels;
	Wheel empty_wheel, *current_wheel, test_wheel[2];
	int a, b, c, d, cwheel = 0;

	empty_wheel.cwedge = 0;
	empty_wheel.speed = 0;

	//Read in data
	in.open ("spin.in");

	while (!in.eof ())
	{
		cwheel++;
		wheels.push_back (empty_wheel);
		current_wheel = &wheels.back ();
		in >> (*current_wheel).speed >> (*current_wheel).cwedge;

		//Test for end of file
		if (in.eof ())
		{
			cwheel--;
			break;
		}

		for (a = 0;a < (*current_wheel).cwedge;a++)
		{
			in >> (*current_wheel).wedgestart[a] >> (*current_wheel).wedgeext[a];

			//Move all wedge data back by the speed for easier calculations later because we increment by the speed
			(*current_wheel).wedgestart[a] -= (*current_wheel).speed;
		}

		//Take extra \n at end so we can test for EOF
		in.get ();
	}

	in.close ();
	out.open ("spin.out");

	//Find all intersections in 360 secs
	for (a = 0;a < 360;a++) //a is seconds
	{
		//Add speed to all the wheel's wedges
		for (b = 0;b < cwheel;b++)
		{
			for (c = 0;c < wheels[b].cwedge;c++)
			{
				wheels[b].wedgestart[c] += wheels[b].speed;

				//Check if it is larger
				if (wheels[b].wedgestart[c] >= 360)
					wheels[b].wedgestart[c] -= 360;
			}
		}

		//Now check for intersections
		test_wheel[1] = wheels[0]; //Used with rotation later

		for (b = 1;b < cwheel;b++)
		{
			//Rotate test wheels
			test_wheel[0] = test_wheel[1];
			test_wheel[1] = empty_wheel;

			//Test intersection between all wedges
			for (c = 0;c < test_wheel[0].cwedge;c++)
			{
				for (d = 0;d < wheels[b].cwedge;d++)
					add_intersect (&test_wheel[1], test_wheel[0].wedgestart[c], test_wheel[0].wedgeext[c], wheels[b].wedgestart[d], wheels[b].wedgeext[d]);
			}
		}

		//If we have any intersection... take the smallest one and output. Else, keep searching
		if (test_wheel[1].cwedge > 0)
		{
			out << a << "\n";
			out.close ();
			return 0;
		}
	}

	//If after 360 seconds with no intersection... Output none
	out << "none\n";
	out.close ();

	return 0;
}