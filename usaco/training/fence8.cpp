/*
PROB: fence8
LANG: C++
ID: yangchess1
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
 
int N,R,board[51],rail[1024],boardsum,railsum[1024];
 
bool dfsid(int r,int b,int sum,int limit)
{
	if(r>=0 && sum<=limit) {
		int i,j;
		bool can=false;
		for(i=b;i<N && !can;i++) {
			if(board[i]>=rail[r]) {
				board[i]-=rail[r];
				if(r>0 && rail[r-1]==rail[r]) {
					j=i;
				} else {
					j=0;
				}
				can=dfsid(r-1,j,sum+(board[i]<rail[0])?board[i]:0,limit);
				board[i]+=rail[r];
			}
		}
		return can;
	} else if(r<0) {
		return true;
	}
	return false;
}
 
bool cmp_dec(int a,int b)
{
	return a>b;
}
 
int main()
{
	ifstream fin;
	ofstream fout;
	int i,l,m,r;
	bool exist=false;
 
	fin.open("fence8.in");
	fin>>N;
	for(i=0;i<N;i++) {
		fin>>board[i];
		boardsum+=board[i];
	}
	fin>>R;
	for(i=0;i<R;i++)
		fin>>rail[i];
	fin.close();
 
	sort(rail,rail+R);
	sort(board,board+N,cmp_dec);
	for(i=1,railsum[0]=rail[0];i<R;i++)
		railsum[i]=railsum[i-1]+rail[i];
	for(l=0,r=R-1;l<=r;) {
		m=(l+r)/2;
		if(dfsid(m,0,0,boardsum-railsum[m])) {
			l=m+1;
			exist=true;
		} else {
			r=m-1;
		}
	}
 
	fout.open("fence8.out");
	fout<<(exist?((l+r)/2+1):0)<<endl;
	fout.close();
}

/*
#include <cstdlib>
#include <fstream>
*/

/*
The basic idea in this program is to use ID-DFS to find out whether we can cut out a certain number of rails. We will implement a function to check whether we can cut out a certain number of rails, and use it until we stumbe upon the greatest working number. There are also a number of optimization techniques involved to make this work.

1. The first optimization technique is to rule out all those rails and board which have the same length, because it is the most optimal solution to use the board as a rail of the same length.
2. Then, we rule out all those rails which are larger than the longest board, because there is no way we can cut out a rail longer than the longest board.
3. The most useful optimization would be to incorporate binary search into the ID-DFS. We test if a certain number of rails is possible. If it is, we test if double that number of rails is possible. If not, we decrease it by a pre-calculate amount, such that the number of rails we test is in a binary-search like pattern.
4. Notice that if we test the rails in increasing order, it will yield a faster solution.
5. Notice that if we test the boards in a decreasing order, it will yield a faster solution.
6. If two rails are of the same length (A and B), then don't try to put A on board 1 and B on board 2, and then try B on board 1 and A on board 2, because that is the same thing. Instead, check the index of the rails.
7. If two boards are of the same length, only check cutting the current rail from the first board, because checking the cut on the second board would be a waste of time.
8. If a board is smaller than a rail, then it is unsuable. Discard it at the beginning of the program.
9. One last important optimization technique would be used within one iteration of ID-DFS with a certain depth. If we have a number of cut boards which are unusable (the boards' length is less than the length of the smallest rail), and the sum of the lengths of these unusable boards is greater than the difference between the total length of the boards and the total length of the rails (up to the depth we are searching), then we know that this iteration of ID-DFS is not going to work. This is because we have too many unusable boards such that we do not have enough usable to satisfy the total length of the rails we are testing.

2, 4, 5, and 8 are all easy to code. 1 and 9 are moderately hard, and 3, 6, and 7 are just a bit harder, but not hard at all. This program uses optimizations 1, 2, 3, 4, 5, 8, and 9.
*/

/*
//The function used in qsort to sort the rails in order from small to big.
int CompareIntSmLg (const void *elem1, const void *elem2)
{
	return (*((int *)(elem1)) - *((int *)(elem2)));
}

//The function used in qsort to sort the boards in order from big to small.
int CompareIntLgSm (const void *elem1, const void *elem2)
{
	return (*((int *)(elem2)) - *((int *)(elem1)));
}

//This function checks whether we can use a certain number of rails. It will be used in the binary search/ID-DFS solution as a DFS step to scan one row of the tree for success. The base algorithm in this function is DFS. We are going to add optimizations 1, 6, 7, and 9 in here. This DFS function only searches to row rail_amount, to see if there is a solution. We are going to precalculate the difference between the total length of the boards and the total length of the rails (up to the depth we are searching) by using sum_board for optimization 9. We also do the DFS in-place instead of recusively, because it is not much more difficult to code, and it is also faster and uses less memory.
bool CanCutRail (int rail_amount, int sum_board, int cboard, int crail, int *board_len, int *rail_len)
{
	int br_diff, unusable_board, depth, board_copy[50], rail_copy[1023], rail_use[1024];
	int a, b, c;

	{
		//Precalculate the difference.
		br_diff = sum_board;

		for (a = 0;a < rail_amount;a++)
			br_diff -= rail_len[a];

		//If board length is smaller than rail, then it's obviously impossible.
		if (br_diff < 0)
			return false;

		//Create a local copy of the board and rails lengths.
		for (a = 0;a < cboard;a++)
			board_copy[a] = board_len[a];

		for (a = 0;a < crail;a++)
			rail_copy[a] = rail_len[a];
	}

	//Rule out those boards and rails with the same length. (optimization 1)
	{
		a = 0;
		b = rail_amount - 1;

		//While we are not out of bounds.
		while (a < cboard && b >= 0)
		{
			//Test the cases.
			if (board_copy[a] < rail_copy[b])
				b--;
			else if (board_copy[a] > rail_copy[b])
				a++;
			else
			{
				//Copy all boards smaller than this one index ahead.
				for (c = a + 1;c < cboard;c++)
					board_copy[c - 1] = board_copy[c];

				//Do the same for rails.
				for (c = b + 1;c < crail;c++)
					rail_copy[c - 1] = rail_copy[c];

				cboard--;
				crail--;
				rail_amount--;
			}
		}

		if (cboard == 0 || crail == 0 || rail_amount <= 0)
			return true;
	}

	//Start the in-place DFS of rails. Use the rail_use array as a local stack.
	depth = 0;
	unusable_board = 0;

	for (a = 0;a < rail_amount;a++)
		rail_use[a] = -1;

	//Loop while we are at least at the first level. When we quit, then we have failed.
	while (depth != -1)
	{
		if (depth == rail_amount) //We are at the wanted depth level, ie we have assigned the first rail_amount rails to boards, then we can cut out all the rails from the boards.
			return true;
		else
		{
			//If we are still assigning rails to boards, do that by seeing the next board (starting at rail_use[depth]) we can cut out the rail. We must first restore the board if we are backtracing.
			if (rail_use[depth] != -1)
			{
				//Restore the unusable_board variable too.
				if (depth + 1 < rail_amount && board_copy[rail_use[depth]] < rail_copy[depth + 1])
					unusable_board -= board_copy[rail_use[depth]];

				board_copy[rail_use[depth]] += rail_copy[depth];
			}

			//(optimization 6) Check if the rail before this one is the same length as the rail at the current depth. If so, make sure that the board this rail on is greater than or equal to the board the last rail is on.
			if (depth != 0 && rail_copy[depth] == rail_copy[depth - 1] && rail_use[depth] + 1 < rail_use[depth - 1])
				b = rail_use[depth - 1];
			else
				b = rail_use[depth] + 1;

			for (a = b;a < cboard;a++)
			{
				//If we can cut out the rail from board a.
				if (board_copy[a] >= rail_copy[depth])
				{
					//(optimization 7) If two boards are of the same length (ie this board is equal to the last), then skip this check because we already checked the last one.
					if (a >= 0 && board_copy[a] == board_copy[a - 1])
						continue;

					board_copy[a] -= rail_copy[depth];
					rail_use[depth++] = a;

					//Update the unusable_board variable.
					if (depth < rail_amount && board_copy[a] < rail_copy[depth])
						unusable_board += board_copy[a];

					break;
				}
			}

			//If no board can cut out the rail, clear the board assigned to the next rail, and backtrace.
			if (a == cboard)
				rail_use[depth--] = -1;

			//If optimization 9 is satisfied, rechoose by continue (first decrement depth).
			else if (unusable_board > br_diff)
				depth--;
			
			continue;
		}
	}

	return false;
}

int main ()
{
	std::ifstream in ("fence8.in");
	std::ofstream out ("fence8.out");
	int cboard, crail, sum_board, upper_bound, lower_bound, mid_bound, board_len[50], rail_len[1023];
	int a;

	//Input the data.
	{
		sum_board = 0;
		in >> cboard;

		for (a = 0;a < cboard;a++)
		{
			in >> board_len[a];
			sum_board += board_len[a];
		}

		in >> crail;

		for (a = 0;a < crail;a++)
			in >> rail_len[a];

		in.close ();
	}

	//Arrange the rails from smallest length to largest length so it it enables us to do the problem better. (optimization 4)
	qsort (rail_len, crail, sizeof (int), CompareIntSmLg);

	//Arrange the boards from large to small. (optimization 5)
	qsort (board_len, cboard, sizeof (int), CompareIntLgSm);

	//If we have rails that are obviously uncuttable, don't count them. (optimization 2)
	{
		a = crail;

		while (a >= 0)
		{
			a--;

			//If this rail is less than the largest board, then it is cuttable. We stop here, and discount all the larger rails.
			if (rail_len[a] <= board_len[0])
				break;
		}

		//Set the number of rails as a + 1, to discount all the larger rails that we can not cut.
		crail = a + 1;

		//If there are no rails left to cut, output 0 and exit.
		if (crail == 0)
		{
			out << "0\n";
			out.close ();

			return 0;
		}
	}

	//If there are obviously unusable boards, discard them. (optimization 8)
	{
		a = cboard;

		while (a >= 0)
		{
			a--;

			if (board_len[a] >= rail_len[0])
				break;

			//If we can't use this board, then subtract it from total board length.
			sum_board -= board_len[a];
		}

		cboard = a + 1;

		if (cboard == 0)
		{
			out << "0\n";
			out.close ();

			return 0;
		}
	}
	
	//Implement the binary-search part of the algorithm. (optimization 3)
	{
		upper_bound = 1;

		while (upper_bound <= crail && CanCutRail (upper_bound, sum_board, cboard, crail, board_len, rail_len))
			upper_bound *= 2;

		lower_bound = upper_bound / 2;

		//Make sure the upper_bound is not above the number of rails, but don't make it equal to that, because then we will never get to checking the maximum number of rails.
		if (upper_bound > crail)
			upper_bound = crail + 1;

		//While we are still closing in on a number.
		while (upper_bound - lower_bound > 1)
		{
			mid_bound = (upper_bound + lower_bound) / 2;

			//Test if we can get the mid_bound number of rails. If yes, then move the lower_bound up. If not, then move the upper_bound down.
			if (CanCutRail (mid_bound, sum_board, cboard, crail, board_len, rail_len))
				lower_bound = mid_bound;
			else
				upper_bound = mid_bound;
		}
	}

	//The answer is in the lower_bound, because it is equal to the mid_bound, and the upper_bound is impossible.
	out << lower_bound << "\n";
	out.close ();

	return 0;
}
*/