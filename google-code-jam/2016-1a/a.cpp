#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main ()
{
	ifstream in ("in.txt");
	ofstream out ("out.txt");
	int tt;

	in >> tt;

	for (int t = 1;t <= tt;t++)
	{
		out << "Case #" << t << ": ";

		string s;
		in >> s;

		string opt = s.substr (0, 1);
		for (int a = 1;a < s.length ();a++)
		{
			if (s[a] + opt >= opt + s[a])
				opt = s[a] + opt;
			else
				opt = opt + s[a];
		}

		out << opt << '\n';
	}

	in.close ();
	out.close ();
}