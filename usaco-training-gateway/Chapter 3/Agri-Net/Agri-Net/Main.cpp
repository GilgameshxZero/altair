/*
ID: yangchess1
PROG: agrinet
LANG: C++
*/

//Use Prim's algorithm to find the Minimal Spanning Tree, and then DFS to traverse the tree and find the total amount of fiber

#include <fstream>
#include <vector>

#define INFINITY 100000000

using namespace std;

struct Farm
{
	int distance;
	int id;
	bool intree;
	int source;
	vector<Farm> neighbor;
};

Farm farm[100];
int matrix[100][100];

int dfs (Farm node, int distance)
{
	int a;
	int total_dist = 0;

	for (a = 0;a < farm[node.id].neighbor.size ();a++)
		total_dist += dfs (farm[node.id].neighbor[a], distance + matrix[node.id][farm[node.id].neighbor[a].id]) + matrix[node.id][farm[node.id].neighbor[a].id];

	return total_dist;
}

int main ()
{
	ifstream in;
	ofstream out;
	int num, small_dist, small_id;
	int a, b;

	in.open ("agrinet.in");
	in >> num;

	//Input adjacency matrix
	for (a = 0;a < num;a++)
	{
		for (b = 0;b < num;b++)
		{
			in >> matrix[a][b];

			if (matrix[a][b] == 0)
				matrix[a][b] = INFINITY;
		}
	}

	in.close ();

	//Init farms
	for (a = 0;a < 100;a++)
	{
		farm[a].distance = INFINITY;
		farm[a].id = a;
		farm[a].intree = false;
		farm[a].source = INFINITY;
	}

	for (a = 1;a < num;a++)
	{
		farm[a].distance = matrix[0][a];
		farm[a].source = 0;
	}

	farm[0].intree = true;

	//Start Prim's algorithm
	for (a = 0;a < num - 1;a++)
	{
		//Search for farm with smallest distance not in tree
		small_dist = INFINITY;
		small_id = INFINITY;

		for (b = 1;b < num;b++)
		{
			if (farm[b].intree == false && farm[b].distance < small_dist)
			{
				small_id = b;
				small_dist = farm[b].distance;
			}
		}

		//Add that farm to the tree and mark it as a neighbor
		farm[small_id].intree = true;
		farm[farm[small_id].source].neighbor.push_back (farm[small_id]);

		//Update the distances and sources if needed
		for (b = 1;b < num;b++)
		{
			if (matrix[small_id][b] < farm[b].distance)
			{
				farm[b].distance = matrix[small_id][b];
				farm[b].source = small_id;
			}
		}
	}

	out.open ("agrinet.out");
	out << dfs (farm[0], 0) << "\n";
	out.close ();

	return 0;
}