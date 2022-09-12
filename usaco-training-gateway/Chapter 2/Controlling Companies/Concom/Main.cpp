/*
ID: yangchess1
PROG: concom
LANG: C++
*/

#include <fstream>
#include <string>
using namespace std;

bool control[100][100];
int share[100][100];

void updatecontrol (short control, short division)
{
	short a;

	if (::control[control][division])
		return;

	::control[control][division] = true;

	for (a = 0;a < 100;a++)
		share[control][a] += share[division][a];

	for (a = 0;a < 100;a++)
		if (::control[a][control])
			updatecontrol (a, division);

	for (a = 0;a < 100;a++)
		if (share[control][a] > 50)
			updatecontrol (control, a);
}

void newshare (short owner, short seller, short percentage)
{
	short a;

	for (a = 0;a < 100;a++)
		if (control[a][owner] == true)
			share[a][seller] += percentage;

	for (a = 0;a < 100;a++)
		if (share[a][seller] > 50)
			updatecontrol (a, seller);
}

int main ()
{
	ifstream in;
	ofstream out;
	short a, b, c, d, number;

	for (a = 0;a < 100;a++)
		control[a][a] = true;

	in.open ("concom.in");
	in >> number;

	for (a = 0;a < number;a++)
	{
		in >> b;
		in >> c;
		in >> d;
		newshare (b - 1, c - 1, d);
	}

	in.close ();

	out.open ("concom.out");
	
	for (a = 0;a < 100;a++)
		for (b = 0;b < 100;b++)
			if (control[a][b] == true && a != b)
				out << a + 1 << " " << b + 1 << "\n";

	out.close ();

	return 0;
}