//A class that stores a linked list, and a linked list node structure is also defined here.
//Insertion:	O(n)
//Access:		O(n)
//Search:		O(n)
//Deletion:		O(n)
template<typename LinkedListType>
class LinkedList
{
	private:
		template<typename LinkedListNodeType>
		struct LinkedListNode
		{
			LinkedListNodeType	key;
			LinkedListNode		*next;
		};

		int								size;
		LinkedListNode<LinkedListType>	*head;

	public:
		LinkedList ();

		LinkedListType					ElementAt	(int index);
		LinkedListNode<LinkedListType>	*NodeAt		(int index);
		int								GetSize		();
		int								Clear		();
		int								PopBack		();
		int								Search		(LinkedListType element);
		int								Insert		(int index, LinkedListType element);
		int								PushBack	(LinkedListType element);
		int								Delete		(int index);
};

template<class LinkedListType> LinkedList<LinkedListType>::LinkedList ()
{
	size = 0;
	head = NULL;
}

template<class LinkedListType> LinkedListType LinkedList<LinkedListType>::ElementAt (int index)
{
	LinkedListNode<LinkedListType> *node = head;
	int a;

	if (index < size && index >= 0)
	{
		for (a = 0;a < index;a++)
			node = node->next;

		return node->key;
	}
	else
		return LinkedListType ();
}

template<class LinkedListType> typename LinkedList<LinkedListType>::LinkedListNode<LinkedListType> *LinkedList<LinkedListType>::NodeAt (int index)
{
	LinkedListNode<LinkedListType> *node = head;
	int a;

	if (index < size && index >= 0)
	{
		for (a = 0;a < index;a++)
			node = node->next;

		return node;
	}
	else
		return LinkedListNode ();
}

template<class LinkedListType> int LinkedList<LinkedListType>::GetSize ()
{
	return size;
}

template<class LinkedListType> int LinkedList<LinkedListType>::Clear ()
{
	for (;size > 0;)
		Delete (0);

	return 0;
}

template<class LinkedListType> int LinkedList<LinkedListType>::PopBack ()
{
	Delete (size - 1);

	return 0;
}

template<class LinkedListType> int LinkedList<LinkedListType>::Search (LinkedListType element)
{
	LinkedListNode<LinkedListType> *node = head;
	int a;

	for (a = 0;a < size;a++)
	{
		if (node->key == element)
			return a;
		
		node = node->next;
	}

	return -1;
}

template<class LinkedListType> int LinkedList<LinkedListType>::Insert (int index, LinkedListType element)
{
	LinkedListNode<LinkedListType> *node = head, *tnode;
	int a;

	if (index > size || index < 0)
		return 1;

	if (index == 0)
	{
		head = new LinkedListNode<LinkedListType>;
		head->key = element;
		head->next = node;
		size++;

		return 0;
	}

	for (a = 1;a < index;a++)
		node = node->next;

	tnode = node->next;
	node->next = new LinkedListNode<LinkedListType>;
	node->next->key = element;
	node->next->next = tnode;
	size++;

	return 0;
}

template<class LinkedListType> int LinkedList<LinkedListType>::PushBack (LinkedListType element)
{
	Insert (size, element);

	return 0;
}

template<class LinkedListType> int LinkedList<LinkedListType>::Delete (int index)
{
	LinkedListNode<LinkedListType> *node = head, *tnode;
	int a;
	
	if (index < 0 || index >= size)
		return 1;

	if (index == 0)
	{
		head = head->next;
		delete node;
		node = NULL;
		size--;

		return 0;
	}

	for (a = 1;a < index;a++)
		node = node->next;

	tnode = node->next;
	node->next = tnode->next;
	delete tnode;
	tnode = NULL;
	size--;

	return 0;
}