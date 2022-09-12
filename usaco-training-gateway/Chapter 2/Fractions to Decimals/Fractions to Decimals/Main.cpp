/*
PROG: fracdec
ID: yangchess1
LANG: C++
*/

#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

struct Remainder
{
	bool used;
	int place;
};

string int_to_str (int);

int main ()
{
	ifstream in;
	ofstream out;
	string ans;
	Remainder rem[100000];
	int a, b, c, r, d, t;

	//Initialize
	for (a = 0;a < 100000;a++)
	{
		rem[a].used = false;
		rem[a].place = 0;
	}

	//Input remainder and divisor
	in.open ("fracdec.in");
	in >> r >> d;
	in.close ();
	out.open ("fracdec.out");

	//Take integer portion first
	if (r >= d)
	{
		t = r / d;
		r = r % d;
		ans = int_to_str (t) + ".";
	}
	else
		ans = "0.";

	//Test for integer
	if (r == 0)
	{
		out << ans << "0\n";
		out.close ();

		return 0;
	}

	//Test for repeating. If true, then restart test. If not, then directly output
	while (true)
	{
		//If nothing left and no repeating digits
		if (r == 0)
		{
			out << ans << "\n";
			out.close ();

			return 0;
		}

		//If repeating, mark flag and exit
		if (rem[r].used == true)
		{
			ans.insert (rem[r].place, 1, '(');
			ans += ')';

			break;
		}
		else //If not yet repeating
		{
			//Mark remainder as accessed
			rem[r].used = true;
			rem[r].place = ans.length ();

			//Move in 1 digit for long division
			r *= 10;

			//Long divide and record
			t = r / d;
			r = r % d;
			ans += int_to_str (t);
		}
	}
	
	//Now, we test to see if ans.length () exceeds 76 chars, then break it up into lines
	while (ans.length () > 76)
	{
		out << ans.substr (0, 76) << "\n";
		ans = ans.substr (76, ans.length () - 76);
	}

	out << ans << "\n";
	out.close ();

	return 0;
}

//Turns and int into equivalent string
string int_to_str (int i)
{
	ostringstream outstr;
	outstr << i;
	return outstr.str ();
}