/*
ID: yangchess1
LANG: C++
PROB: nuggets
*/

#include <queue>
#include <fstream>

int main ()
{
	const int MAX_PACKAGE_SIZE = 256;

	std::ifstream in ("nuggets.in");
	std::ofstream out ("nuggets.out");
	std::queue<int> enum_todo;
	int nnuggets[10], coptions, current_enum, mods_left, sm_nug = MAX_PACKAGE_SIZE;
	bool possible_mod[MAX_PACKAGE_SIZE], top_bound;
	int a, b;

	//Initialize all possible_mod to false for later use.
	for (a = 0;a < 256;a++)
		possible_mod[a] = false;

	in >> coptions;

	for (a = 0;a < coptions;a++)
	{
		in >> nnuggets[a];

		//If all possible purchases can be made, output 0.
		if (nnuggets[a] == 1)
		{
			out << "0\n";
			out.close ();
			
			return 0;
		}

		//Test if this is the smallest nugget packaging size. This small size will be used later.
		if (nnuggets[a] < sm_nug)
			sm_nug = nnuggets[a];
	}

	//We still have to satisfy sm_nug mods in order to complete the problem. See later for description about mods.
	mods_left = sm_nug;

	in.close ();

	//If the numbers' GCD is greater than 1, then there is no upper bound to the impossible number, if GCD = 1, then there is one.
	for (a = 2;a <= 256;a++)
	{
		top_bound = false;

		//If a single number a divides all the numbers, then there is no upper bound.
		for (b = 0;b < coptions;b++)
		{
			if (static_cast<float>(nnuggets[b]) / static_cast<float>(a) != static_cast<float>(nnuggets[b] / a))
				top_bound = true;
		}

		if (top_bound == false)
		{
			out << "0\n";
			out.close ();
			
			return 0;
		}
	}

	//If a number x is possible, then the numbers x + nnuggets[a] for all valid a will be possible. We save what we need to enumerate in a queue. Once we have found all mods for the smallest value of packaging, we take this last number we found, and subtract the smallest value of packaging to get our answer. We initialize the number 0 as possible.
	enum_todo.push (0);

	while (!enum_todo.empty ())
	{
		current_enum = enum_todo.front ();
		enum_todo.pop ();

		//Mark that we used this mod.
		if (possible_mod[current_enum % sm_nug] == false)
		{
			possible_mod[current_enum % sm_nug] = true;
			mods_left--;

			//If we have used all the mods, we are basically done.
			if (mods_left == 0)
				break;

			//Enumerate this number.
			for (a = 0;a < coptions;a++)
				enum_todo.push (current_enum + nnuggets[a]);
		}
	}

	out << current_enum - sm_nug << "\n";
	out.close ();

	return 0;
}