/*
Excuse the bad practices (massive headers, using namespace). They are for a faster coding.

When submitting the program, define DEBUG 0. When debugging, define DEBUG 1. In the program, for debugging information, use if (DEBUG){...} such that when it is submitted we don't have that code there.

Backup this program every so often in the Backup.txt files in case something goes wrong later.

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

//#define DEBUG 0
#define DEBUG 1

struct Node
{
	unsigned long long value[4]; //0: no endpoints. 1: left endpoint only. 2: right endpoint only. 3: both endpoints.
	Node *left, *right, *parent;

	Node ()
	{
		left = right = parent = NULL;
		value[0] = value[1] = value[2] = value[3] = 0;
	}

	Node (Node *nleft, Node *nright, Node *nparent, int v1, int v2, int v3, int v4)
	{
		left = nleft;
		right = nright;
		parent = nparent;
		value[0] = v1;
		value[1] = v2;
		value[2] = v3;
		value[3] = v4;
	}
};

unsigned long long cmach, cdays, mach[40000], ans;
Node *root, *nodes[40000];

Node *ConstructNode (int low, int high, Node *parent)
{
	if (low == high)
	{
		nodes[low] = new Node (NULL, NULL, parent, 0, 0, 0, mach[low]);
		return nodes[low];
	}

	Node *r = new Node;

	r->left = ConstructNode (low, (low + high) / 2, r);
	r->right = ConstructNode ((low + high) / 2 + 1, high, r);
	r->parent = parent;
	r->value[0] = max (max (r->left->value[0] + r->right->value[0], r->left->value[0] + r->right->value[1]), r->left->value[2] + r->right->value[0]);
	r->value[1] = max (max (r->value[0], r->left->value[1] + r->right->value[0]), max(r->left->value[1] + r->right->value[1], r->left->value[3] + r->right->value[0]));
	r->value[2] = max (max (r->value[0], r->left->value[0] + r->right->value[2]), max(r->left->value[2] + r->right->value[2], r->left->value[0] + r->right->value[3]));
	r->value[3] = max (max (max (r->value[1], r->value[2]), max (r->left->value[1] + r->right->value[2], r->left->value[1] + r->right->value[3])), r->left->value[3] + r->right->value[2]);

	return r;
}

void PropogateUpdate (Node *node)
{
	if (node->parent == NULL)
		return;
	
	node->parent->value[0] = max (max (node->parent->left->value[0] + node->parent->right->value[0], node->parent->left->value[0] + node->parent->right->value[1]), node->parent->left->value[2] + node->parent->right->value[0]);
	node->parent->value[1] = max (max (node->parent->value[0], node->parent->left->value[1] + node->parent->right->value[0]), max(node->parent->left->value[1] + node->parent->right->value[1], node->parent->left->value[3] + node->parent->right->value[0]));
	node->parent->value[2] = max (max (node->parent->value[0], node->parent->left->value[0] + node->parent->right->value[2]), max(node->parent->left->value[2] + node->parent->right->value[2], node->parent->left->value[0] + node->parent->right->value[3]));
	node->parent->value[3] = max (max (max (node->parent->value[1], node->parent->value[2]), max (node->parent->left->value[1] + node->parent->right->value[2], node->parent->left->value[1] + node->parent->right->value[3])), node->parent->left->value[3] + node->parent->right->value[2]);
	PropogateUpdate (node->parent);

	return;
}

int main ()
{
	std::ifstream in ("optmilk.in");
	std::ofstream out ("optmilk.out");
	
	in >> cmach >> cdays;

	for (int a = 0;a < cmach;a++)
		in >> mach[a];

	//Construct our heirarchy tree.
	root = ConstructNode (0, cmach - 1, NULL);

	//Input the updates one by one and use DP to update our load tree each time.
	for (int a = 0, b, c;a < cdays;a++)
	{
		in >> b >> c;
		//mach[b - 1] = c;
		nodes[b - 1]->value[3] = c;

		PropogateUpdate (nodes[b - 1]);
		ans += root->value[3];
	}

	in.close ();
	out << ans << "\n";
	out.close ();

	return 0;
}