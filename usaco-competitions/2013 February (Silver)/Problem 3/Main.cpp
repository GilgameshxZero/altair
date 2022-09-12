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

const int	MAXCOWS	= 10000;

DynamicArray<int> constraint[MAXCOWS];
int cowtime[MAXCOWS], finish[MAXCOWS];

int GetFinish (int num)
{
	int lg_constraint;

	if (finish[num] != -1)
		return finish[num];
	
	//If no constraints regarding this cow, then it's just its cowtime when it finishes.
	if (constraint[num].GetSize () == 0)
		return cowtime[num];
	else
	{
		lg_constraint = 0;

		//Check all the constraints, and add the cowtime to the largest finish time of a constraint to make this finish time.
		for (int a = 0;a < constraint[num].GetSize ();a++)
		{
			finish[constraint[num].ElementAt (a)] = GetFinish (constraint[num].ElementAt (a));

			if (finish[constraint[num].ElementAt (a)] > lg_constraint)
				lg_constraint = finish[constraint[num].ElementAt (a)];
		}

		return cowtime[num] + lg_constraint;
	}
}

int main ()
{
	std::ifstream in ("msched.in");
	std::ofstream out ("msched.out");
	int ccow, cconstraint, lg_time;

	in >> ccow >> cconstraint;

	for (int a = 0;a < ccow;a++)
	{
		in >> cowtime[a];
		finish[a] = -1;
	}

	for (int a = 0, b, c;a < cconstraint;a++)
	{
		in >> b >> c;
		constraint[c - 1].PushBack (b - 1);
	}

	lg_time = 0;

	//Examine each cow, and keep an array of how much time from beginning it will be until that cow is finished. For each cow, see if that time is greater than our greatest, and then update if true.
	for (int a = 0;a < ccow;a++)
	{
		finish[a] = GetFinish (a);

		if (finish[a] > lg_time)
			lg_time = finish[a];
	}

	out << lg_time << "\n";
	out.close ();

	return 0;
}