/*
ID: yangchess1
PROG: heritage
LANG: C++
*/

#include <fstream>
#include <string>

//A structure that can hold a tree.
struct Node
{
	char symbol;
	Node* left_node;
	Node* right_node;
};

//A recursive procedure that constructs a tree by splitting the in_order traversal by the root, which can be found as the first letter of the pre_order traversal. In this function, we keep a variable pre_order_index, which will keep the pointer to the first letter of the pre-order traversal, because we will not change the pre-order traversal when we recurse. It will store the tree in Node *rtrn_tree.
void ConstructTree (std::string in_order, std::string pre_order, int *pre_order_index, Node *rtrn_tree)
{
	int root_pos;

	//If the in_order traversal is only 1 symbol, we've reached a leaf.
	if (in_order.length () == 1)
	{
		//Increment the pre_order_index so that it points to the symbol succeeding the leaf and set the rtrn_tree's symbol as the symbol in the in_order traversal.
		rtrn_tree->symbol = in_order[0];
		rtrn_tree->left_node = NULL;
		rtrn_tree->right_node = NULL;

		return;
	}

	//The root of the tree is the first letter of the pre-order traversal.
	rtrn_tree->symbol = pre_order[(*pre_order_index)];

	root_pos = in_order.find (rtrn_tree->symbol);

	//Split the in_order traversal with the root and find the left and right sub-trees of the root. We pass an incremented pre_order_index each time to make sure that the pre_order_index indeed points to the root of the sub-tree.
	rtrn_tree->left_node = new Node;
	rtrn_tree->right_node = new Node;

	//Check if the sub-tree is nonexistant.
	if (root_pos == 0)
	{
		delete rtrn_tree->left_node;
		rtrn_tree->left_node = NULL;
	}
	else
	{
		(*pre_order_index)++;
		ConstructTree (in_order.substr (0, root_pos), pre_order, pre_order_index, rtrn_tree->left_node);
	}

	//Check if the sub-tree is nonexistant.
	if (in_order.length () - root_pos - 1 == 0)
	{
		delete rtrn_tree->right_node;
		rtrn_tree->right_node = NULL;
	}
	else
	{
		(*pre_order_index)++;
		ConstructTree (in_order.substr (root_pos + 1, in_order.length () - root_pos - 1), pre_order, pre_order_index, rtrn_tree->right_node);
	}

	return;
}

//Traverse the left sub-tree, then the right sub-tree, and then print the root.
void PostOrderTraversal (Node *tree, std::ofstream *out)
{
	//If we reached past the end of the tree, just return.
	if (tree == NULL)
		return;

	PostOrderTraversal (tree->left_node, out);
	PostOrderTraversal (tree->right_node, out);

	(*out) << tree->symbol;

	return;
}

int main ()
{
	std::ifstream in ("heritage.in");
	std::ofstream out ("heritage.out");
	std::string in_order, pre_order, post_order;
	Node heritage;
	int pre_order_index_param = 0;

	//Input the in-order and pre-order traversals.
	in >> in_order >> pre_order;
	in.close ();

	//We know the root from the pre-order traversal. We can then split the in_order traversal with the root and use a recursive function every time to determine the actual tree (stored in Node *heritage), with which we will derive the post_order traversal from.
	ConstructTree (in_order, pre_order, &pre_order_index_param, &heritage);

	//After we have the tree, we use a post_order traversal to print the symbols to the output file.
	PostOrderTraversal (&heritage, &out);

	out << "\n";
	out.close ();

	return 0;
}