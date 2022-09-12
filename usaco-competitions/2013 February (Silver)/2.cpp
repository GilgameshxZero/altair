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

struct TVStruct
{
	int pos[2];
	int hdif;
};

const int	MAXFSIZE	= 500;

bool visited[MAXFSIZE][MAXFSIZE], in_array[MAXFSIZE][MAXFSIZE];
int field[MAXFSIZE][MAXFSIZE];

int main ()
{
	std::ifstream in ("tractor.in");
	std::ofstream out ("tractor.out");
	DynamicArray<TVStruct> to_visit;
	TVStruct temp_elem;
	int field_size, need_sq, sm_cost, sq_access, cur_cost, location, hdif, cur_sq[2], lg_nvisited[2];

	in >> field_size;
	need_sq = static_cast<int>(0.5 + static_cast<float>(field_size) * static_cast<float>(field_size) / 2.0);

	for (int a = 0;a < field_size;a++)
	{
		for (int b = 0;b < field_size;b++)
		{
			in >> field[a][b];
			visited[a][b] = false;
		}
	}

	in.close ();

	lg_nvisited[0] = lg_nvisited[1] = 0;
	sm_cost = numeric_limits<int>::max ();

	//While we haven't checked starting on all the squares... keep checking.
	for (;lg_nvisited[0] < field_size;lg_nvisited[0]++)
	{
		for (;lg_nvisited[1] < field_size;lg_nvisited[1]++)
		{
			if (visited[lg_nvisited[0]][lg_nvisited[1]] == false)
			{
				//Check for a tractor starting on this square, and see if we can lower the minimum cost.
				to_visit.Clear ();
				visited[lg_nvisited[0]][lg_nvisited[1]] = true;
				cur_cost = 0;
				cur_sq[0] = lg_nvisited[0];
				cur_sq[1] = lg_nvisited[1];
				sq_access = 1; //The variable containing the number of squares our tractor can go on with this cost.

				for (int a = 0;a < field_size;a++)
					for (int b = 0;b < field_size;b++)
						in_array[a][b] = false;

				in_array[0][0] = true;

				//While we need access to more squares.
				while (sq_access < need_sq)
				{
					//If we have already a larger cost.
					if (cur_cost > sm_cost)
						break;

					//Index all the locations around the current square into the array.
					if (cur_sq[0] != 0 && in_array[cur_sq[0] - 1][cur_sq[1]] == false)
					{
						hdif = abs(field[cur_sq[0] - 1][cur_sq[1]] - field[cur_sq[0]][cur_sq[1]]);

						//Insert it in increasing order of height difference.
						for (location = 0;location < to_visit.GetSize ();location++)
							if (to_visit.ElementAt (location).hdif >= hdif)
								break;

						temp_elem.pos[0] = cur_sq[0] - 1;
						temp_elem.pos[1] = cur_sq[1];
						temp_elem.hdif = hdif;
						in_array[temp_elem.pos[0]][temp_elem.pos[1]] = true;

						to_visit.Insert (location, temp_elem);
					}
					if (cur_sq[0] != field_size - 1 && in_array[cur_sq[0] + 1][cur_sq[1]] == false)
					{
						hdif = abs(field[cur_sq[0] + 1][cur_sq[1]] - field[cur_sq[0]][cur_sq[1]]);

						//Insert it in increasing order of height difference.
						for (location = 0;location < to_visit.GetSize ();location++)
							if (to_visit.ElementAt (location).hdif >= hdif)
								break;

						temp_elem.pos[0] = cur_sq[0] + 1;
						temp_elem.pos[1] = cur_sq[1];
						temp_elem.hdif = hdif;
						in_array[temp_elem.pos[0]][temp_elem.pos[1]] = true;

						to_visit.Insert (location, temp_elem);
					}
					if (cur_sq[1] != 0 && in_array[cur_sq[0]][cur_sq[1] - 1] == false)
					{
						hdif = abs(field[cur_sq[0]][cur_sq[1] - 1] - field[cur_sq[0]][cur_sq[1]]);

						//Insert it in increasing order of height difference.
						for (location = 0;location < to_visit.GetSize ();location++)
							if (to_visit.ElementAt (location).hdif >= hdif)
								break;

						temp_elem.pos[0] = cur_sq[0];
						temp_elem.pos[1] = cur_sq[1] - 1;
						temp_elem.hdif = hdif;
						in_array[temp_elem.pos[0]][temp_elem.pos[1]] = true;

						to_visit.Insert (location, temp_elem);
					}
					if (cur_sq[1] != field_size - 1 && in_array[cur_sq[0]][cur_sq[1] + 1] == false)
					{
						hdif = abs(field[cur_sq[0]][cur_sq[1] + 1] - field[cur_sq[0]][cur_sq[1]]);

						//Insert it in increasing order of height difference.
						for (location = 0;location < to_visit.GetSize ();location++)
							if (to_visit.ElementAt (location).hdif >= hdif)
								break;

						temp_elem.pos[0] = cur_sq[0];
						temp_elem.pos[1] = cur_sq[1] + 1;
						temp_elem.hdif = hdif;
						in_array[temp_elem.pos[0]][temp_elem.pos[1]] = true;

						to_visit.Insert (location, temp_elem);
					}

					//No more options to go.
					if (to_visit.GetSize () == 0)
					{
						cur_cost = numeric_limits<int>::max ();
						break;
					}

					//Choose the first element -- the element with the least distance -- for the next accessed square. Also, update our cur_cost.
					cur_sq[0] = to_visit.ElementAt (0).pos[0];
					cur_sq[1] = to_visit.ElementAt (0).pos[1];

					if (to_visit.ElementAt (0).hdif > cur_cost)
						cur_cost = to_visit.ElementAt (0).hdif;

					to_visit.Delete (0);
					sq_access++;
					visited[cur_sq[0]][cur_sq[1]] = true;
				}

				//See if the current cost is smaller. If it is, update.
				if (cur_cost < sm_cost)
					sm_cost = cur_cost;
			}
		}
	}

	out << sm_cost << "\n";
	out.close ();

	return 0;
}