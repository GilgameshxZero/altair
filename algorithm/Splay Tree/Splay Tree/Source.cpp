#include <iostream>
#include <string>
#include <map>
#include <assert.h>
#include <vector>
#include <sstream>
using namespace std;

struct Node
{
	Node *par, *ch[2];
	int val, size;

	Node ()
	{
		par = ch[0] = ch[1] = NULL;
		size = 0;
		val = -1;
	}

	//have a dummy node after each leaf
	bool IsNull ()
	{
		return (size == 0);
	}

	bool IsRoot ()
	{
		return par->IsNull ();
	}

	void Rotate ()
	{
		if (IsNull ())
			return; //we shouldn't rotate dummy node
		if (IsRoot ())
			return; //don't rotate the root

		int x = par->ch[1] == this, y = par->par->ch[1] == par;
		par->ch[x] = ch[!x];
		ch[!x]->par = par;
		ch[!x] = par;
		par = ch[!x]->par;
		ch[!x]->par = this;
		par->ch[y] = this;

		ch[!x]->size = ch[!x]->ch[0]->size + ch[!x]->ch[1]->size + 1;
		size = ch[0]->size + ch[1]->size + 1;
	}

	void Splay (Node **root)
	{
		if (*root == this)
			return; //don't splay if we are the root

		while (!IsRoot () && par != *root)
		{
			if ((par->ch[0] == this) ^ (par->par->ch[0] == par)) //if straight: 1^1 -> false -> top down, else bent: 1^0 -> bottom up
				Rotate ();
			else
				par->Rotate ();
			Rotate ();
		}

		if (par == *root)
			Rotate ();

		*root = this;
	}
};

//true: error, x already exists
bool Insert (Node **root, Node *node, int x)
{
	if (node->IsNull ())
	{
		node->size++;
		node->ch[0] = new Node;
		node->ch[1] = new Node;
		node->ch[0]->par = node->ch[1]->par = node;
		node->val = x;
		node->Splay (root);
		*root = node;
		return false;
	}
	
	node->size++;

	if (x < node->val)
		return Insert (root, node->ch[0], x);
	else if (x > node->val)
		return Insert (root, node->ch[1], x);
	else //exists
		return true;
}

//return NULL if x doesn't exist.
Node *Get (Node *root, int x)
{
	if (root->IsNull ())
		return NULL;
	else if (x < root->val)
		return Get (root->ch[0], x);
	else if (x > root->val)
		return Get (root->ch[1], x);
	else //exists
		return root;
}

void Delete (Node **root, Node *node)
{
	node->Splay (root);

	if (!node->ch[0]->IsNull () && !node->ch[1]->IsNull ()) //two children
	{
		Node *mmax = node->ch[0];
		while (!mmax->ch[1]->IsNull ())
			mmax = mmax->ch[1];

		mmax->Splay (&((*root)->ch[0]));
		assert (mmax->ch[1]->IsNull ());

		delete mmax->ch[1];
		mmax->ch[1] = node->ch[1];
		node->ch[1]->par = mmax;
		delete node;
		*root = mmax;
		mmax->size = mmax->ch[0]->size + mmax->ch[1]->size + 1;
		mmax->par = NULL;
	}
	else if (node->ch[0]->IsNull () && node->ch[1]->IsNull ()) //no children
	{
		delete node->ch[0];
		*root = node->ch[1]; //NULL node
		(*root)->par = NULL;
		delete node;
	}
	else //1 child
	{
		if (node->ch[0]->IsNull ())
		{
			*root = node->ch[1];
			(*root)->par = NULL;
			delete node->ch[0];
			delete node;
		}
		else
		{
			*root = node->ch[0];
			(*root)->par = NULL;
			delete node->ch[1];
			delete node;
		}
	}
}

void Traverse (vector<int> *order, Node *root)
{
	if (root->IsNull ())
		return;

	Traverse (order, root->ch[0]);
	order->push_back (root->val);
	Traverse (order, root->ch[1]);
}

int Rank (Node *root, int x)
{
	if (root->IsNull ())
		return -(1 << 31);
	else if (root->val == x)
		return root->ch[0]->size + 1;
	else if (x < root->val)
		return Rank (root->ch[0], x);
	else
		return root->ch[0]->size + 1 + Rank (root->ch[1], x);
}

int Find (Node *root, int k) //finds kth largest under root
{
	if (root->IsNull ())
		return -(1 << 31);
	else if (k == root->ch[0]->size + 1)
		return root->val;
	else if (k <= root->ch[0]->size)
		return Find (root->ch[0], k);
	else
		return Find (root->ch[1], k - root->ch[0]->size - 1);
}

string int_string (int x)
{
	if (x < 0)
		return "NULL";

	stringstream ss;
	string r;

	ss << x;
	ss >> r;
	return r;
}

void TraverseRelations (vector<string> *rel, Node *root)
{
	if (root->IsNull ())
		return;

	rel->push_back (int_string (root->val) + "->" + int_string (root->ch[0]->val));
	rel->push_back (int_string (root->val) + "->" + int_string (root->ch[1]->val));
	TraverseRelations (rel, root->ch[0]);
	TraverseRelations (rel, root->ch[1]);
}

int main ()
{
	Node *root;

	root = new Node;

	cout << "Splay Tree (with subtree size)\nYang Yan - Rain Corporation\nProject started: 2014/08/24\n";

	while (true)
	{
		string comm;
		cout << "\nCommands:\n"
			<< "add x: adds x to the splay tree (x must not already exist in tree)\n"
			<< "del x: deletes x from the splay tree (x must be in the tree)\n"
			<< "order: lists the elements in the splay tree in numerical order from least to greatest\n"
			<< "rank x: finds the rank (order) of x in tree (x must exist in tree)\n"
			<< "find x: finds the xth element in the tree (tree must be at least as large as x)\n"
			<< "size: returns size of tree\n"
			<< "exist x: test if x exists in the tree\n"
			<< "view: prints all child relations in the tree\n"
			<< "rot x: rotates x in tree with its parent (x must be in tree, x must not be root of tree)\n"
			<< "splay x: splays x to top of tree (x must exist)\n"
			<< "exit: exits the program\n"
			<< "Please enter a command (minimum error checking is implemented, please do not push the boundaries): ";
		cin >> comm;

		if (comm == "add")
		{
			int x;
			cin >> x;

			if (Insert (&root, root, x))
				cout << x << " already exists in the tree and was not added.\n";
		}
		else if (comm == "del")
		{
			int x;
			Node *tnode;

			cin >> x;
			tnode = Get (root, x);
			
			if (tnode == NULL)
				cout << x << " does not exist in the tree and was not deleted.\n";
			else
				Delete (&root, tnode);
		}
		else if (comm == "order")
		{
			vector<int> order;
			Traverse (&order, root);
			for (int a = 0;a < order.size ();a++)
				cout << order[a] << " ";
			cout << "\n";
		}
		else if (comm == "rank")
		{
			int x, y;
			cin >> x;

			y = Rank (root, x);
			if (y < 0)
				cout << x << " does not exist in the tree.\n";
			else
				cout << "Rank (from 1): " << y << "\n";
		}
		else if (comm == "find")
		{
			int x, y;
			cin >> x;
			y = Find (root, x);

			if (y < 0)
				cout << x << " is not in range of the tree.\n";
			else
				cout << "The " << x << "th element in the tree is " << y << ".\n";
		}
		else if (comm == "size")
		{
			cout << "Size of tree: " << root->size << "\n";
		}
		else if (comm == "exist")
		{
			int x;
			Node *tnode;
			cin >> x;
			tnode = Get (root, x);

			if (tnode == NULL)
				cout << x << " does not exist in the tree.\n";
			else
				cout << x << " exists in the tree.\n";
		}
		else if (comm == "view")
		{
			vector<string> rel;
			TraverseRelations (&rel, root);

			for (int a = 0;a < rel.size ();a++)
				cout << rel[a] << "\n";
		}
		else if (comm == "rot")
		{
			int x;
			Node *tnode;
			cin >> x;
			tnode = Get (root, x);

			if (tnode == NULL)
				cout << x << " does not exist in tree.\n";
			else if (tnode == root)
				cout << x << " is the root.\n";
			else
				tnode->Rotate ();
		}
		else if (comm == "splay")
		{
			int x;
			Node *tnode;
			cin >> x;
			tnode = Get (root, x);

			if (tnode == NULL)
				cout << x << " does not exist in tree.\n";
			else if (tnode == root)
				cout << x << " is the root.\n";
			else
				tnode->Splay (&root);
		}
		else if (comm == "exit")
			break;
		else
			cout << "Your command was not recognized.\n";
	}

	return 0;
}