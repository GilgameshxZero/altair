/*
ID: yangchess1
LANG: C++
PROB: lgame
*/

/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

Backup this program every so often in the Backup files in case something goes wrong later.

Max's and mins: numeric_limits<type_name>::min().
*/

#include <algorithm>
#include <bitset>
#include <limits>
#include <climits>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector> 

using namespace std;

std::string word[40000];

//Class instead of struct, it has an initializer function.
class Node
{
	public:
		Node ()
		{
			for (int a = 0;a < 26;a++)
				next[a] = NULL;

			end = false;
			back = NULL;
		}

		Node *next[26];
		Node *back;
		bool end;
};

//A recursive function that searches for the solution using a DFS on the tree. 'sum' is the number of points accumulated up to a certain point.
void FindSolutions (Node *current, vector<string> *solution, int *score, int *points, string letter, Node *root, int cword, int sum, string lsum)
{
	string substr[2];
	bool duplicate;
	char nletter;
	int space;

	//Check first if the root is a word itself. From there we need to decide if we can create a second word.
	if (current->end == true)
	{
		if (sum >= *score)
		{
			//If we already have a pair of words as lsum, then we will order the two words first before we push_back.
			for (space = 0;space < lsum.length () && lsum[space] != ' ';space++);

			if (space != lsum.length ())
			{
				substr[0] = lsum.substr (0, space);
				substr[1] = lsum.substr (space + 1, lsum.length () - space - 1);

				if (substr[0] > substr[1])
					lsum = substr[1] + " " + substr[0];
				else
					lsum = substr[0] + " " + substr[1];
			}

			if (sum > *score)
				solution->clear ();

			*score = sum;
			solution->push_back (lsum);
		}

		//If there is no space and more than 2 letters remaining, we can search for another word.
		if (letter.length () > 2)
			FindSolutions (root, solution, score, points, letter, root, cword, sum, lsum + " ");
	}

	//Given the list of letters (letter), we loop through all of them, and recurse on the letters that can be built onto the existing (current).
	for (int a = 0;a < letter.length ();a++)
	{
		//Only if we can add another letter onto this root.
		if (current->next[letter[a] - 97] != NULL)
		{
			//Make sure we haven't went over this letter before, because there may be duplicate letters.
			duplicate = false;

			for (int b = 0;b < a;b++)
			{
				if (letter[b] == letter[a])
					duplicate = true;
			}

			if (duplicate == false)
			{
				nletter = letter[a];
				letter.erase (letter.begin () + a);
				FindSolutions (current->next[nletter - 97], solution, score, points, letter, root, cword, sum + points[nletter - 97], lsum + nletter);
				letter.insert (letter.begin () + a, nletter);
			}
		}
	}
}

int main ()
{
	std::ifstream in ("lgame.in"), dict ("lgame.dict");
	std::ofstream out ("lgame.out");
	vector<string> solution;
	string letter = "";
	Node root, *current, *previous;
	int points[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7}, cword = 0, score = 0;

	do
		letter += in.get ();
	while (letter[letter.length () - 1] != '\n');

	in.close ();
	letter = letter.substr (0, letter.length () - 1); //Disregard the '\n'.

	do
		dict >> word[cword];
	while (word[cword++] != ".");

	dict.close ();
	cword--; //Disregard the '.'.

	//Set up the trie. It's pretty self-explanatory.
	for (int a = 0;a < cword;a++)
	{
		current = &root;

		for (int b = 0;b < word[a].length ();b++)
		{
			if (current->next[word[a][b] - 97] == NULL)
				current->next[word[a][b] - 97] = new Node;

			previous = current;
			current = current->next[word[a][b] - 97];
			current->back = previous;
		}

		current->end = true;
	}

	FindSolutions (&root, &solution, &score, points, letter, &root, cword, 0, "");

	//Sort the solutions.
	sort (solution.begin (), solution.end ());

	//Output our solutions and high score. As all pairs of words will appear twice (our algorithm does it like that), and since it is sorted, we will output only if the solution differs from the previous one.
	out << score << "\n" << solution[0] << "\n";

	for (int a = 1;a < solution.size ();a++)
	{
		if (solution[a] != solution[a - 1])
			out << solution[a] << "\n";
	}

	out.close ();
	
	return 0;
}