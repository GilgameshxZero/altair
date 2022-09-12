/*
ID: yangchess1
LANG: C++
PROB: fence6
*/

#include <algorithm>
#include <fstream>

const int EPPERFENCE	= 2;
const int MAXFENCEPEREP	= 9;
const int MAXCENDPOINT	= 200;
const int MAXCFENCE		= 100;

//Fence endpoint. This structure stores the various fences that connect to this endpoint.
struct EndPoint
{
	int cfence;
	int connected[MAXFENCEPEREP];
};

//Uses Dijkstra's algorithm to find distances between all vertices in a graph.
int DijkstraPath (bool **neighbor, int **dist, const int source, const int nvert)
{
	const int INFINITY = 200000000;
	bool visited[800];
	int current, small_dist, small_past, a, b;

	//Initialization
	current = source;

	for (a = 0;a < nvert;a++)
		visited[a] = false;

	visited[source] = true;
	dist[source][source] = 0;

	//Start the algorithm
	for (a = 1;a < nvert;a++)
	{
		//Update all the distances to the neighbors of the current pasture
		for (b = 0;b < nvert;b++)
		{
			//If the pasture is a neighbor of the curent pasture and has not been visited yet
			if (neighbor[current][b] == true && visited[b] == false)
			{
				//Check if the pasture has a shorter sum (distance to the current + the distance of the current to the source) than already listed
				if (dist[current][b] + dist[source][current] < dist[source][b])
					dist[source][b] = dist[b][source] = dist[current][b] + dist[source][current];
			}
		}

		//Pick the closest neighbor not visited, and set it as the next current pasture
        small_dist = INFINITY;

		for (b = 0;b < nvert;b++)
		{
			if (visited[b] == false && dist[source][b] < small_dist)
			{
				small_dist = dist[source][b];
				small_past = b;
			}
		}

		visited[small_past] = true;
		current = small_past;
	}

	return 0;
}

int main ()
{
	std::ifstream in ("fence6.in");
	std::ofstream out ("fence6.out");
	EndPoint endpoint[MAXCENDPOINT];
	bool same_flag, **adj_EP;
	const int INFINITY = 200000000;
	int cfence, cendpoint, small_perim, fence_len[MAXCFENCE], fence_EP[MAXCFENCE][EPPERFENCE], **EP_dist;
	int a, b, c, d, e, f;

	//Input the data. This time, we store each fence endpoint as a node, and each of the fences as a line connecting the nodes.
	in >> cfence;
	cendpoint = 0;

	//The fences connected to the endpoints are represented in computer units (starting at 0). Make sure also to store the endpoints each fence corresponds to, as it will be useful later on.
	for (a = 0;a < cfence;a++)
	{
		in >> b;
		in >> fence_len[b - 1];
		in >> c >> d;

		for (e = 0;e < c;e++)
		{
			in >> f;
			endpoint[cendpoint].connected[e] = f - 1;
		}

		endpoint[cendpoint].connected[c] = b - 1;
		endpoint[cendpoint].cfence = c + 1;
		std::sort (endpoint[cendpoint].connected, endpoint[cendpoint].connected + c + 1);
		cendpoint++;

		for (e = 0;e < d;e++)
		{
			in >> f;
			endpoint[cendpoint].connected[e] = f - 1;
		}
		
		endpoint[cendpoint].connected[d] = b - 1;
		endpoint[cendpoint].cfence = d + 1;
		std::sort (endpoint[cendpoint].connected, endpoint[cendpoint].connected + d + 1);
		cendpoint++;

		fence_EP[b - 1][0] = cendpoint - 2;
		fence_EP[b - 1][1] = cendpoint - 1;
	}

	//Go through the endpoints and combine any that are the same. This will be easy because we have the connected array sorted.
	for (a = 0;a < cendpoint;a++)
	{
		//Look for an endpoint similar to endpoint a. This must be after a, because we have searched before a. Limit this search to endpoint[a].cfence number of duplicates to find, because if the number of duplicates exceeds that, it may mean we have two distinct endpoints that look the same. Store the number of duplicates found in e.
		e = 0;

		for (b = a + 1;b < cendpoint && e < endpoint[a].cfence;b++)
		{
			if (endpoint[a].cfence == endpoint[b].cfence)
			{
				same_flag = true;

				for (c = 0;c < endpoint[a].cfence;c++)
				{
					if (endpoint[a].connected[c] != endpoint[b].connected[c])
					{
						same_flag = false;
						break;
					}
				}

				//If these two are exactly the same, remove the second one, and add one duplicate. Also update the endpoint for the fences connected to the removed endpoint.
				if (same_flag == true)
				{
					//The endpoint for the fences connected to endpoint b will now be endpoint a. Make sure that if both endpoints of fences connected to b connect to a, only update one.
					for (c = 0;c < endpoint[b].cfence;c++)
					{
						if (fence_EP[endpoint[b].connected[c]][0] == b)
							fence_EP[endpoint[b].connected[c]][0] = a;
						else if (fence_EP[endpoint[b].connected[c]][1] == b)
							fence_EP[endpoint[b].connected[c]][1] = a;
					}

					//All those endpoints greater than b in fence_EP are to be decremented.
					for (c = 0;c < cfence;c++)
					{
						if (fence_EP[c][0] > b)
							fence_EP[c][0]--;

						if (fence_EP[c][1] > b)
							fence_EP[c][1]--;
					}

					for (c = b + 1;c < cendpoint;c++)
					{
						endpoint[c - 1].cfence = endpoint[c].cfence;

						for (d = 0;d < endpoint[c].cfence;d++)
							endpoint[c - 1].connected[d] = endpoint[c].connected[d];
					}

					cendpoint--;
					e++;
					b--;
				}
			}
		}
	}

	//Now that we have all distinct endpoints, put then in an adjacency matrix for the main algorithm. We use the fence_EP array here, in addition to the times we use it later. We have to make the matrix of type **, not type *[], for Dijkstra's function.
	adj_EP = new bool *[cendpoint];

	for (a = 0;a < cendpoint;a++)
		adj_EP[a] = new bool[cendpoint];

	for (a = 0;a < cendpoint;a++)
		for (b = 0;b < cendpoint;b++)
			adj_EP[a][b] = false;

	for (a = 0;a < cfence;a++)
		adj_EP[fence_EP[a][0]][fence_EP[a][1]] = adj_EP[fence_EP[a][1]][fence_EP[a][0]] = true;

	//Create a distance array that will be used by the Dijkstra's function.
	EP_dist = new int *[cendpoint];
	
	for (a = 0;a < cendpoint;a++)
		EP_dist[a] = new int[cendpoint];
	
	//After a bit of pain with the input and converting it to a graph, we now proceed to the algorithm. We take every fence, and try removing it. We then use Dijkstra's to find the shortest path between the fence's endpoints. This length plus the length of the fence is the perimeter of the smallest region by the fence. We do this for every fence, and take the smallest perimeter. We have also kept track of which endpoints correspond to a fence, so when removing the fence, we know which endpoints to update.
	small_perim = INFINITY;

	for (a = 0;a < cfence;a++)
	{
		//Remove this fence.
		for (b = 0;b < cendpoint;b++)
			for (c = 0;c < cendpoint;c++)
				EP_dist[b][c] = INFINITY;

		for (b = 0;b < cfence;b++)
			EP_dist[fence_EP[b][0]][fence_EP[b][1]] = EP_dist[fence_EP[b][1]][fence_EP[b][0]] = fence_len[b];

		adj_EP[fence_EP[a][0]][fence_EP[a][1]] = adj_EP[fence_EP[a][1]][fence_EP[a][0]] = false;
		EP_dist[fence_EP[a][0]][fence_EP[a][1]] = EP_dist[fence_EP[a][1]][fence_EP[a][0]] = INFINITY;

		//Run Dijkstra's.
		DijkstraPath (adj_EP, EP_dist, fence_EP[a][0], cendpoint);

		//Test if the distance between the endpoints of fence a is the smallest. If so, record it.
		if (EP_dist[fence_EP[a][0]][fence_EP[a][1]] + fence_len[a] < small_perim)
			small_perim = EP_dist[fence_EP[a][0]][fence_EP[a][1]] + fence_len[a];

		//Add back the fence.
		adj_EP[fence_EP[a][0]][fence_EP[a][1]] = adj_EP[fence_EP[a][1]][fence_EP[a][0]] = true;
	}

	//Output the answer
	out << small_perim << "\n";
	out.close ();

	//Free up the memory.
	for (a = 0;a < cendpoint;a++)
	{
		delete[] adj_EP[a];
		delete[] EP_dist[a];
	}

	delete[] adj_EP;
	delete[] EP_dist;

	return 0;
}