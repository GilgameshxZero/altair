/*
ID: yangchess1
LANG: C++
PROG: msquare
*/

//Try to do a simple BFS

#include <fstream>
#include <string>
#include <queue>

struct SquareCombo
{
	int square[8];
	std::string sequence;
};

int Encode (int *formation)
{
	int copy[8];
	int rtrn = 0;
	int a, b, c;

	//Create local copy
	for (a = 0;a < 8;a++)
		copy[a] = formation[a];

	for (a = 0;a < 6;a++)
	{
		//Add on digit
		b = (copy[a] - 1);

		for (c = 7 - a;c > 1;c--)
			b *= c;

		rtrn += b;

		//Subtract all the rest if bigger than the digit
		for (b = a + 1;b < 7;b++)
			if (copy[b] > copy[a])
				copy[b]--;
	}

	//Add last digit
	rtrn += (copy[6] - 1);

	return rtrn;
}

void Transform (int *original, int *rtrn_val, char order)
{
	int copy[8], temp[4];
	int a;
	
	//Create local copy
	for (a = 0;a < 8;a++)
		copy[a] = original[a];

	if (order == 'A')
	{
		temp[0] = copy[0];
		copy[0] = copy[7];
		copy[7] = temp[0];
		temp[0] = copy[1];
		copy[1] = copy[6];
		copy[6] = temp[0];
		temp[0] = copy[2];
		copy[2] = copy[5];
		copy[5] = temp[0];
		temp[0] = copy[3];
		copy[3] = copy[4];
		copy[4] = temp[0];
	}

	if (order == 'B')
	{
		temp[0] = copy[3];
		copy[3] = copy[2];
		copy[2] = copy[1];
		copy[1] = copy[0];
		copy[0] = temp[0];
		temp[0] = copy[4];
		copy[4] = copy[5];
		copy[5] = copy[6];
		copy[6] = copy[7];
		copy[7] = temp[0];
	}

	if (order == 'C')
	{
		temp[0] = copy[6];
		copy[6] = copy[5];
		copy[5] = copy[2];
		copy[2] = copy[1];
		copy[1] = temp[0];
	}
	
	//Create copy
	for (a = 0;a < 8;a++)
		rtrn_val[a] = copy[a];

	return;
}

int main ()
{
	std::ifstream in ("msquare.in");
	std::ofstream out ("msquare.out");
	std::queue<SquareCombo> queue;
	SquareCombo temp;
	bool visited[40320], flag;
	int *transform = new int[8];
	int a, b, c, d, end[8];
	
	for (a = 0;a < 40320;a++)
		visited[a] = false;

	//We can get 1 2 3 4 5 6 7 8 = 0
	visited[0] = true;

	for (a = 0;a < 8;a++)
		temp.square[a] = a + 1;

	temp.sequence = "";
	queue.push (temp);

	for (a = 0;a < 8;a++)
		in >> end[a];

	in.close ();

	//Test for base case
	flag = true;

	for (a = 0;a < 8;a++)
	{
		if (end[a] != a + 1)
			flag = false;
	}

	if (flag == true)
	{
		out << "0\n\n";
		out.close ();

		return 0;
	}

	//Start a Breadth-First Search
	while (true)
	{
		//Get length of existing queue
		a = queue.size ();

		//Go through original queue and test if by adding an A, B, or C (without visiting them already) will result in an answer. Then add another element to the queue of A, B, or C and pop the original element.
		for (b = 0;b < a;b++)
		{
			//Test for the letters (A, B, C)
			for (c = 65;c < 68;c++)
			{
				//Get new square by transforming it with the current character
				Transform (queue.front ().square, transform, static_cast<char>(c));
				d = Encode (transform);
                
                //If the character is not visited already
                if (visited[d] == false)
                {
					//Mark it as visited
					visited[d] = true;

					temp.sequence = queue.front ().sequence + static_cast<char>(c);

					for (d = 0;d < 8;d++)
						temp.square[d] = transform[d];

					flag = true;
						
					//Test if it is the answer
					for (d = 0;d < 8;d++)
						if (temp.square[d] != end[d])
							flag = false;

					if (flag == true)
						break;
						
					//Save it as another one in the queue
					queue.push (temp);
				}
			}
			
			//Test for answer
			if (flag == true)
				break;
			
			//Pop the original element
			queue.pop ();
		}

		//Test for answer
		if (flag == true)
			break;
	}

	out << temp.sequence.length () << "\n" << temp.sequence << "\n";
	out.close ();

	return 0;
}