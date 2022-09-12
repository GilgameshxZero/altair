/*
ID: yangchess1
PROG: contact
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Node
{
	int frequency;
	Node *left;
	Node *right;
};

struct SubArray
{
	string code;
	int frequency;
};

void CreateTree (Node *node, int level)
{
	node->frequency = 0;

	if (level >= 12)
	{
		node->left = NULL;
		node->right = NULL;
		return;
	}
	
	node->left = new Node;
	CreateTree (node->left, level + 1);
	node->right = new Node;
	CreateTree (node->right, level + 1);
}

void AddFreq (Node *tree, string sequence)
{
	if (sequence.length () == 0)
		return;

	if (sequence[0] == '0')
	{
		tree->left->frequency++;
		AddFreq (tree->left, sequence.substr (1, sequence.length () - 1));
	}
	else if (sequence[0] == '1')
	{
		tree->right->frequency++;
		AddFreq (tree->right, sequence.substr (1, sequence.length () - 1));
	}
}

void StoreFreq (Node *tree, int level, int min, int max, string code, vector<SubArray> *largest)
{
	SubArray temp;
	int a;
	bool insert = false;

	if (level > max)
		return;

	temp.code = code;
	temp.frequency = tree->frequency;

	//See if worthy to put in array
	if (level >= min)
	{
		for (a = largest->size () - 1;a >= 0;a--)
		{
			if (temp.frequency < (*largest)[a].frequency)
			{
				(*largest).insert ((*largest).begin () + a + 1, temp);
				insert = true;
				break;
			}
			else if (temp.frequency == (*largest)[a].frequency)
			{
				if (temp.code.length () > (*largest)[a].code.length ())
				{
					(*largest).insert ((*largest).begin () + a + 1, temp);
					insert = true;
					break;
				}
				else if (temp.code.length () == (*largest)[a].code.length ())
				{
					if (temp.code > (*largest)[a].code)
					{
						(*largest).insert ((*largest).begin () + a + 1, temp);
						insert = true;
						break;
					}
				}
			}			
		}

		//If not inserted
		if (insert == false)
			(*largest).insert ((*largest).begin (), temp);
	}

	//Test the next two nodes
	StoreFreq (tree->left, level + 1, min, max, code + "0", largest);
	StoreFreq (tree->right, level + 1, min, max, code + "1", largest);
}

void DeleteTree (Node *node)
{
	if (node->left != NULL && node->right != NULL)
	{
		DeleteTree (node->left);
		DeleteTree (node->right);
		delete node->left;
		delete node->right;
		node->left = NULL;
		node->right = NULL;
	}
}

int main ()
{
	ifstream in;
	ofstream out;
	vector<SubArray> largest;
	string sequence;
	Node tree;
	int A, B, N;
	int a, b, c, d, e;
	char temp;

	cerr << "1...\n";

	CreateTree (&tree, 0);

	cerr << "2...\n";

	in.open ("contact.in");
	in >> A >> B >> N;

	cerr << "3...\n";

	while (true)
	{
		temp = in.get ();

		if (temp == '0' || temp == '1')
			sequence += temp;
		else if (temp == '\n')
			continue;
		else
			break;
	}

	in.close ();

	cerr << "4...\n";

	//Get frequencies
	c = sequence.length () - B + 1;
	for (a = 0;a < c;a++)
		AddFreq (&tree, sequence.substr (a, B));

	cerr << "5...\n";

	a = c;
	b = B - 1;
	d = sequence.length ();

	if (c < 0)
	{
		a = 0;
		b = B - 1 + c;
	}

	for (;a < d;a++)
	{
		AddFreq (&tree, sequence.substr (a, b));
		b--;
	}

	cerr << "6...\n";

	//Read off frequencies and only store the largest N of them
	StoreFreq (&tree, 0, A, B, "", &largest);

	cerr << "7...\n";

	out.open ("contact.out");

	//Now output
	b = largest.size ();
	c = -1;
	e = 0;
	for (a = 0;a < b;a++)
	{
		if (largest[a].frequency == 0)
			break;
		else if (largest[a].frequency != c)
		{
			d = 0;
			e++;

			if (e > N)
				break;

			if (a == 0)
				out << largest[a].frequency << "\n" << largest[a].code;
			else
				out << "\n" << largest[a].frequency << "\n" << largest[a].code;
		}
		else
		{
			if (d == 5)
			{
				out << "\n" << largest[a].code;
				d = 0;
			}
			else
			{
				out << " " << largest[a].code;
				d++;
			}
		}

		c = largest[a].frequency;
	}

	out << "\n";
	out.close ();

	cerr << "8...\n";

	//Free memory
	DeleteTree (&tree);

	return 0;
}