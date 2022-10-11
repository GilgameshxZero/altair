/*
PROG: ratios
LANG: C++
ID: yangchess1
*/

#include <fstream>

#define INFINITY 100000

struct Ratio
{
	int x;
	int y;
	int z;
};

int main ()
{
	std::ifstream in ("ratios.in");
	std::ofstream out ("ratios.out");
	Ratio goal, l, m, n;
	int a, b, c, x, y, z, ans[4] = {INFINITY, INFINITY, INFINITY, INFINITY};
	float p, q, r, s;

	//Read in the input
	in >> goal.x >> goal.y >> goal.z >> l.x >> l.y >> l.z >> m.x >> m.y >> m.z >> n.x >> n.y >> n.z;
	in.close ();

	//Brute-force it
	for (a = 0;a <= 100;a++)
	{
		for (b = 0;b <= 100;b++)
		{
			for (c = 0;c <= 100;c++)
			{
				x = l.x * a + m.x * b + n.x * c;
				y = l.y * a + m.y * b + n.y * c;
				z = l.z * a + m.z * b + n.z * c;

				//Test for 0s
				if (x == 0 && y == 0 && z == 0)
					continue;

				if (a == 99 && b == 99 && c == 99)
					a=a;

				//Test if it is a multiple of the goal
				if (y == 0)
					p = INFINITY;
				else
					p = static_cast<float>(x) / static_cast<float>(y);
				if (z == 0)
					q = INFINITY;
				else
					q = static_cast<float>(y) / static_cast<float>(z);
				
				if (goal.y == 0)
					r = INFINITY;
				else
					r = static_cast<float>(goal.x) / static_cast<float>(goal.y);
				if (goal.z == 0)
					s = INFINITY;
				else
					s = static_cast<float>(goal.y) / static_cast<float>(goal.z);

				if (p == r && q == s && static_cast<float>(x) / static_cast<float>(goal.x) == static_cast<float>(x / goal.x) && a + b + c < ans[0] + ans[1] + ans[2] && x >= goal.x)
				{
					//Save the answer for comparison later
					ans[0] = a;
					ans[1] = b;
					ans[2] = c;
					ans[3] = x / goal.x;
				}
			}
		}
	}

	if (ans[3] == INFINITY)
	{
		out << "NONE\n";
		out.close ();

		return 0;
	}

	out << ans[0] << " " << ans[1] << " " << ans[2] << " " << ans[3] << "\n";
	out.close ();

	return 0;
}