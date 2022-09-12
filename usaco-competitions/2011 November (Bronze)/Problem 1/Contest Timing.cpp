#include <fstream>

using namespace std;

int main ()
{
	ifstream in;
	ofstream out;
	int day, hour, min, t;

	in.open ("ctiming.in");
	in >> day >> hour >> min;
	in.close ();

	if (day == 11)
	{
		if (hour == 11)
			t = min - 11;
		else
			t = 49 + (hour - 12) * 60 + min;
	}
	else
		t = 49 + 60 * 12 + (day - 12) * 24 * 60 + hour * 60 + min;

	out.open ("ctiming.out");
	out << t << "\n";
	out.close ();

	return 0;
}