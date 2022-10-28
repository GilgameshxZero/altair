/*
ID: yangchess1
PROG: maze1
LANG: C++
*/

#include <fstream>
#include <string>
#include <vector>
using namespace std;

//struct Node
//{
//	bool visited;
//	int distance[2];
//	vector<Node *> neighbor;
//};

int main ()
{
	ifstream in;
	ofstream out;

	in.open ("maze1.in");
	in.out ();
	out.open ("maze1.out");
	
	out.close ();
	//Node node[38][100];
	//vector<Node *> start;
	//int length, height;
	//int a, b, c, d;
	//char f;

	//in.open ("maze1.in");
	//in >> length >> height;
	//in.get ();

	////Read in top row of maze and scan for start points.
	//for (a = 0;a < length;a++)
	//{
	//	in.get ();

	//	if (in.get () == ' ')
	//		start.push_back (&node[a][0]);
	//}

	////Dump end of line chars
	//in.get ();
	//in.get ();

	////Read in rest of lines except for last 2
	//for (a = 0;a < height - 1;a++)
	//{
	//	//Read in first 2 characters
	//	if (in.get () == ' ')
	//		start.push_back (&node[a][0]);

	//	//Dump extra
	//	in.get ();

	//	//Read in in-between rows
	//	for (b = 0;b < length - 1;b++)
	//	{
	//		//If two nodes are connected
	//		if (in.get () == ' ')
	//		{
	//			node[a][b].neighbor.push_back (&node[a][b + 1]);
	//			node[a][b + 1].neighbor.push_back (&node[a][b]);
	//		}
	//	
	//		//Dump middle character
	//		in.get ();
	//	}

	//	//Evaluate last character of in-between row
	//	if (in.get () == ' ')
	//		start.push_back (&node[a][length - 1]);
	//	
	//	//Dump end of line char
	//	in.get ();

	//	//Move on to read second row, the border row
	//	for (b = 0;b < length;b++)
	//	{
	//		//Dump first character
	//		in.get ();

	//		//If two nodes are connected
	//		if (in.get () == ' ')
	//		{
	//			node[a][b].neighbor.push_back (&node[a + 1][b]);
	//			node[a + 1][b].neighbor.push_back (&node[a][b]);
	//		}
	//	}

	//	//Dump end of line chars
	//	in.get ();
	//	in.get ();
	//}

	////Read in first 2 characters of 2nd to last row
	//if (in.get () == ' ')
	//	start.push_back (&node[height - 1][0]);

	////Dump extra
	//in.get ();

	////Read in in-between rows
	//for (b = 0;b < length - 1;b++)
	//{
	//	//If two nodes are connected
	//	if (in.get () == ' ')
	//	{
	//		node[height - 1][b].neighbor.push_back (&node[height - 1][b + 1]);
	//		node[height - 1][b + 1].neighbor.push_back (&node[height - 1][b]);
	//	}
	//	
	//	//Dump middle character
	//	in.get ();
	//}

	////Evaluate last character of in-between row
	//if (in.get () == ' ')
	//	start.push_back (&node[height - 1][length - 1]);
	//	
	////Dump end of line char
	//in.get ();

	////Read in last row
	//for (b = 0;b < length;b++)
	//{
	//	//Dump first character
	//	in.get ();

	//	//If node is start
	//	if (in.get () == ' ')
	//		start.push_back (&node[height - 1][b]);
	//}

	////Reading complete
	//in.close ();

	////Now determine all distances from start point 1
	////Initialize all visited/distances
	//for (a = 0;a < height;a++)
	//{
	//	for (b = 0;b < length;b++)
	//	{
	//		node[a][b].distance[0] = 1000000;
	//		node[a][b].distance[1] = 1000000;
	//		node[a][b].visited = false;
	//	}
	//}

	////Initialize start
	//start[0]->visited = true;
	//start[0]->distance[0] = 0;

	return 0;
}