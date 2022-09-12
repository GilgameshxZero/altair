#include <fstream>
#include <string>

int main ()
{
	std::ifstream in ("typo.in");
	std::ofstream out ("typo.out");
	std::string parenthesis;
	bool flip_flag = false;
	int length, cposition = 0, excess_left = 0, right_count = 0, cleft_2 = 0;
	int a;

	in >> parenthesis;
	in.close ();

	//Traverse the string once.
	length = parenthesis.length ();

	for (a = 0;a < length;a++)
	{
		if (parenthesis[a] == '(')
			excess_left++;
		else
		{
			excess_left--;
			right_count++;
		}

		if (excess_left >= 2 && parenthesis[a] == '(')
			cleft_2++;

		if (excess_left == 1)
			cleft_2 = 0;

		//It's illegal!
		if (excess_left < 0 && flip_flag == false)
		{
			flip_flag = true;
			cposition = right_count;
			excess_left += 2;
		}
		else if (excess_left < 0 && flip_flag == true)
		{
			out << "0\n";
			out.close ();
		}
	}

	if (excess_left == 0 && flip_flag == false || excess_left != 0 && flip_flag == true)
	{
		out << "0\n";
		out.close ();
	}
	else if (excess_left == 0 && flip_flag == true)
	{	
		out << cposition << "\n";
		out.close ();
	}
	else if (excess_left == 2 && flip_flag == false)
	{	
		out << cleft_2 << "\n";
		out.close ();
	}
	else
	{	
		out << "0\n";
		out.close ();
	}

	return 0;
}