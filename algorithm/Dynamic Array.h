//A class that stores a dynamic array. 
//Insertion:	O(n)
//Access:		O(1)
//Search:		O(n)
//Deletion:		O(n)
template<typename DynamicArrayType>
class DynamicArray
{
	public:
		DynamicArray ();

		DynamicArrayType	ElementAt		(int index);
		int					GetSize			();
		int					GetCapacity		();
		int					Clear			();
		int					ResetCapacity	();
		int					Search			(DynamicArrayType element);
		int					Insert			(int index, DynamicArrayType element);
		int					PushBack		(DynamicArrayType element);
		int					PopBack			();
		int					Delete			(int index);
		int					ResizeCapacity	(int new_capacity);

	private:
		int					size, capacity;
		DynamicArrayType	*d_array;
};

template<class DynamicArrayType> DynamicArray<DynamicArrayType>::DynamicArray ()
{
	size = capacity = 0;
	d_array = NULL;
}

template<class DynamicArrayType> DynamicArrayType DynamicArray<DynamicArrayType>::ElementAt (int index)
{
	if (index < size && index >= 0)
		return d_array[index];
	else
		return DynamicArrayType ();
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::GetSize ()
{
	return size;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::GetCapacity ()
{
	return capacity;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::Clear ()
{
	size = 0;

	return 0;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::ResetCapacity ()
{
	ResizeCapacity (0);

	return 0;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::Search (DynamicArrayType element)
{
	int a;

	for (a = 0;a < size;a++)
		if (d_array[a] == element)
			return a;

	return -1;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::Insert (int index, DynamicArrayType element)
{
	int a;

	if (index > size || index < 0)
		return 1;

	//If we need to resize the array. Use the resize factor 2.
	if (size == capacity)
	{
		if (capacity > 0)
			ResizeCapacity (capacity * 2);
		else //Implies capacity = 0.
			ResizeCapacity (2);
	}

	size++;

	for (a = size;a > index;a--)
		if (a < capacity)
			d_array[a] = d_array[a - 1];

	d_array[index] = element;

	return 0;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::PushBack (DynamicArrayType element)
{
	Insert (size, element);

	return 0;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::Delete (int index)
{
	int a;
	
	if (index < 0 || index >= size)
		return 1;

	size--;

	for (a = index;a < size;a++)
		d_array[a] = d_array[a + 1];

	return 0;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::PopBack ()
{
	Delete (size - 1);

	return 0;
}

template<class DynamicArrayType> int DynamicArray<DynamicArrayType>::ResizeCapacity (int new_capacity)
{
	DynamicArrayType *temp_array;
	int a;

	if (new_capacity < size)
		return 1;

	if (new_capacity == 0) //Implies size is zero.
	{
		capacity = 0;
		delete[] d_array;
		d_array = NULL;

		return 0;
	}

	temp_array = new DynamicArrayType[capacity];

	//Copy the elements.
	for (a = 0;a < size;a++)
		temp_array[a] = d_array[a];

	//Delete the original, and reset it.
	delete[] d_array;
	d_array = NULL;

	capacity = new_capacity;
	d_array = new DynamicArrayType[capacity];

	//Copy back the elements.
	for (a = 0;a < size;a++)
		d_array[a] = temp_array[a];

	delete[] temp_array;
	temp_array = NULL;

	return 0;
}