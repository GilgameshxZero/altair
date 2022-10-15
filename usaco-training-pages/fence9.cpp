/*
ID: yangchess1
PROG: fence9
LANG: C++
*/

#include <cmath>
#include <fstream>

bool LineIntersection (double intersection[2], double p1[2], double p2[2], double p3[2], double p4[2])
{
	double a = (p4[0] - p3[0]) * (p1[1] - p3[1]) - (p4[1] - p3[1]) * (p1[0] - p3[0]), 
		b = (p4[1] - p3[1]) * (p2[0] - p1[0]) - (p4[0] - p3[0]) * (p2[1] - p1[1]);

	if (b == 0)
		return false;

	intersection[0] = p1[0] + (p2[0] - p1[0]) * a / b;
	intersection[1] = p1[1] + (p2[1] - p1[1]) * a / b;

	return true;
}

int main ()
{
	std::ifstream in ("fence9.in");
	std::ofstream out ("fence9.out");
	double vertex[2], origin[2], x_int[2];
	double p[2], q[2], r[2], s[2];
	int a, b, c, d, total_cows;

	in >> vertex[0] >> vertex[1] >> x_int[0];
	in.close ();

	//Some initialization of variables. Check here from later code to see what was initial.
	origin[0] = origin[1] = x_int[1] = r[0] = 0;
	total_cows = 0;
	s[0] = 1;

	//We find the number of lattice points in each horozontal lattice row, and then add them up to output.
	for (a = 1;a < vertex[1];a++)
	{
		//Find the points on the two sides of the triangle that have y-coordinate a. We intersect a horozontal line y = a with each of the sides to find those points. We save those points in p and q.
		r[1] = s[1] = static_cast<double>(a);
		LineIntersection (p, origin, vertex, r, s);
		LineIntersection (q, vertex, x_int, r, s);

		//Let b and c be the start and end of the lattice points in this lattice row, inclusive
		b = static_cast<int>(floor (p[0])) + 1; //Round down
		c = static_cast<int>(ceil (q[0])) - 1; //Round up

		//Let d be the number of lattice points in this row.
		d = c - b + 1;

		//If we can fit cows here.
		if (d > 0)
			total_cows += d;
	}

	out << total_cows << "\n";
	out.close ();

	return 0;
}