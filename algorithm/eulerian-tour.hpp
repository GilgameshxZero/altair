//Used by the FindEulerianTour function. Do not use elsewhere.
void FindEulerianTourSub (int **mvert, int *tour, const int cvert, const int start_node, int *tour_pos)
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
}

//Finds a Eulerian tour/circuit.
void FindEulerianTour (int **mvert, int *tour, const int cvert, const int start_node)
{
	int *tour_pos = new int;
	
	*tour_pos = 0;
	FindEulerianTourSub (mvert, tour, cvert, start_node, tour_pos);
	
	delete tour_pos;
}