/*
ID: yangchess1
LANG: C++
PROG: fence
*/

#include <fstream>
#include <iostream>

//Finds a tour/circuit
void Find_Tour (int **mvert, int *tour, const int cvert, const int start_node, int *tour_pos)
{
	bool neighbors;
	int a, rand_neigh;
	
	while (true)
	{
		//Pick random neighbor rand_neigh of start_node (pick the first one). While doing this, test that start_node still has neighbors. If not, exit immediately.
		neighbors = false;
		
		for (a = 0;a < cvert;a++)
		{
			if (mvert[start_node][a] > 0)
			{
				neighbors = true;
				rand_neigh = a;
				break;
			}
		}
		
		//Assure that start_node still has neighbors
		if (neighbors == false)
			break;
			
		//Now we have a random neighbor and start_node has at least one neighbor, delete that edge
		mvert[start_node][rand_neigh]--;
		mvert[rand_neigh][start_node]--;
		
		//Call the recursive function
		Find_Tour (mvert, tour, cvert, rand_neigh, tour_pos);
	}
	
	//After we have visited all neighbors of start_node
	tour[(*tour_pos)++] = start_node;
	std::cout << "\nNode added: tour[ " << *tour_pos << " ] = " << start_node + 1;
	std::cin.get ();
	
	//Done
	return;
}

//Finds a tour/circuit
void Find_Euler_Tour (int **mvert, int *tour, const int cvert, const int start_node)
{
	int *tour_pos = new int;
	
	*tour_pos = 0;
	Find_Tour (mvert, tour, cvert, start_node, tour_pos);
	
	delete tour_pos;
	
	return;
}

int main ()
{
	std::ifstream in;
	std::ofstream out;
	const int MAX_PAST = 500;
	int deg[500], cfence, start_past, *tour, **mvert;
	int a, b, c;
	
	in.open ("fence.in");
	in >> cfence;
	
	//Initialize
	for (a = 0;a < MAX_PAST;a++)
		deg[a] = 0;
	
	mvert = new int *[MAX_PAST];
	tour = new int[cfence + 1];
	
	for (a = 0;a < MAX_PAST;a++)
		mvert[a] = new int[MAX_PAST];
		
	for (a = 0;a < MAX_PAST;a++)
	{	
		for (b = 0;b < MAX_PAST;b++)
			mvert[a][b] = 0;
	}
	
	for (a = 0;a < cfence + 1;a++)
		tour[a] = -1;
	
	//Read in matrix
	for (a = 0;a < cfence;a++)
	{
		in >> b >> c;
		mvert[b - 1][c - 1]++;
		mvert[c - 1][b - 1]++;
		deg[b - 1]++;
		deg[c - 1]++;
	}

	in.close ();
	
	//Find the smallest node with odd degree, if none, then take node 1
	for (a = 0;a < MAX_PAST;a++)
	{
		if (deg[a] % 2 == 1)
			break;
	}
	
	//Execute path finding algorithm
	if (a < 500)
		Find_Euler_Tour (mvert, tour, MAX_PAST, a);
	if (a == 500)
		Find_Euler_Tour (mvert, tour, MAX_PAST, 0);
	
	//Output results
	out.open ("fence.out");

	for (a = cfence;a >= 0;a--)
	{
		if (tour[a] != -1)
			out << tour[a] + 1 << "\n";	
	}
		
	out.close ();
	
	//Free memory
	for (a = 0;a < MAX_PAST;a++)
		delete mvert[a];
		
	delete[] mvert;
	delete[] tour;
	
	std::cin.get ();
	
	return 0;
}
