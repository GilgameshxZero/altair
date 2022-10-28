#include <fstream>
#include <time.h>

void main ()
{
	std::ofstream out ("Problem 1 Test Data.txt");
	int a;

	srand (time (NULL));

	for (a = 0;a < 50000;a++)
	{
		if (rand () % 2 == 0)
			out << "(";
		else
			out << ")";
	}

	out.close ();
}