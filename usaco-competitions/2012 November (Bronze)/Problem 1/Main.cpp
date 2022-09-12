#include <fstream>
#include <string>

int main ()
{
	std::ifstream in ("cowfind.in");
	std::ofstream out ("cowfind.out");
	std::string grass;
	long long answer = 0;
	int left_paren = 0;
	int a;

	in >> grass;
	in.close ();

	//Loop through the grass once and find the number of pairs of )) after each (( (also, add them).
	for (a = 0;a < grass.length () - 1;a++)
	{
		if (grass[a] == '(' && grass[a + 1] == '(')
			left_paren++;
		else if (grass[a] == ')' && grass[a + 1] == ')')
			answer += left_paren;
	}

	out << answer << "\n";
	out.close ();

	return 0;
}