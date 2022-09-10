#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

struct Node
{
	int index;
	Node *pp, //Path parent.
		*left, *right, *par;

	Node ()
	{
		index = -1;
		pp = left = right = par = NULL;
	}
};

Node node[100000];
string temp;
int n, m;

//Rotates x with its parent.
void Rotate (Node *x)
{
	x->pp = x->par->pp;
	x->par->pp = NULL;

	if (x->par->left == x)
	{
		x->par->left = x->right;
		if (x->right != NULL)
			x->right->par = x->par;
		x->right = x->par;

		if (x->par->par != NULL)
		{
			if (x->par->par->left == x->par)
				x->par->par->left = x;
			else
				x->par->par->right = x;
		}

		x->par = x->par->par;
		x->right->par = x;
	}
	else
	{
		x->par->right = x->left;
		if (x->left != NULL)
			x->left->par = x->par;
		x->left = x->par;

		if (x->par->par != NULL)
		{
			if (x->par->par->left == x->par)
				x->par->par->left = x;
			else
				x->par->par->right = x;
		}

		x->par = x->par->par;
		x->left->par = x;
	}
}

//Splay x in its aux. tree.
void Splay (Node *x)
{
	while (x->par != NULL && x->par->par != NULL)
	{
		//Straight.
		if ((x->par->left == x && x->par->par->left == x->par) || (x->par->right == x && x->par->par->right == x->par))
		{
			Rotate (x->par);
			Rotate (x);
		}
		else //Bent.
		{
			Rotate (x);
			Rotate (x);
		}
	}

	//x still isn't root.
	if (x->par != NULL)
		Rotate (x);
}

//Essentially make x the root of its tree of aux. trees/pick up x as the root.
void MakeRoot (Node *x)
{
	Splay (x);

	if (x->left != NULL)
	{
		x->left->par = NULL;
		x->left->pp = x;
		x->left = NULL;
	}
	if (x->right != NULL)
	{
		x->right->par = NULL;
		x->right->pp = x;
		x->right = NULL;
	}
}

//Make root->x path dominant without changing tree root.
void Access (Node *x)
{
	Splay (x);

	if (x->right != NULL)
	{
		x->right->pp = x;
		x->right->par = NULL;
		x->right = NULL;
	}

	while (x->pp != NULL)
	{
		Splay (x->pp);

		if (x->pp->right != NULL)
		{
			x->pp->right->pp = x->pp;
			x->pp->right->par = NULL;
		}

		x->pp->right = x;
		x->par = x->pp;
		x->pp = NULL;
		Rotate (x);
	}
}

//Find root of tree of aux. trees.
Node *FindRoot (Node *x)
{
	Access (x);

	while (x->left != NULL)
		x = x->left;

	return x;
}

//Assume x and y are roots, trees are unrooted.
void Link (Node *x, Node *y)
{
	//Make x and y roots of their trees.
	Access (x);
	MakeRoot (x);
	Access (y);
	MakeRoot (y);

	x->pp = y;
}

//Assume x is a root, and thus y is its child.
void Cut (Node *x, Node *y)
{
	//Make x the root, and y the child.
	MakeRoot (x);

	y->pp = NULL;
}

int main ()
{
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	cin >> n >> m;

	for (int a = 0;a < n;a++)
		node[a].index = a;

	for (int a = 0, b, c;a < m;a++)
	{
		cin >> temp >> b >> c;
		b--;
		c--;

		if (temp[0] == 'c')
		{
			if (FindRoot (&node[b]) == FindRoot (&node[c]))
				cout << "YES\n";
			else
				cout << "NO\n";
		}
		else if (temp[0] == 'a')
			Link (&node[b], &node[c]);
		else
			Cut (&node[b], &node[c]);
	}

	return 0;
}