/*
ID: yangchess1
PROG: rockers
LANG: C++
*/

#include <fstream>

int main ()
{
	std::ifstream in ("rockers.in");
	std::ofstream out ("rockers.out");
	int songlim[21][21][21]; //[a][b][c] The maximum number of songs we can fit on a disks, with b minutes used on the last disk, and with song c as the last song in the group.
	int songlen[21], csong, minpdisk, cdisk, best = 0;
	int a, b, c, d;

	in >> csong >> minpdisk >> cdisk;
	
	for (a = 1;a <= csong;a++)
		in >> songlen[a];

	in.close ();

	//Initialize all of songlim. Really, we only need to use songlim[0...cdisk][0...minpdisk-1][0...csong].
	for (a = 0;a < 21;a++)
		for (b = 0;b < 21;b++)
			for (c = 0;c < 21;c++)
				songlim[a][b][c] = -1;

	//Let's start the DP with zero disks, the 0th disk filled, and with song 0.
	songlen[0] = -1;
	songlim[0][minpdisk][0] = 0;

	//We loop through the song limits with increasing disks, minutes used on the last disk, and the last song used. For each of these song limits, we try every song after the last song and update the appropriate song limit if we add another song to it.
	for (a = 0;a <= cdisk;a++)
	{
		for (b = 0;b <= minpdisk;b++)
		{
			for (c = 0;c <= csong;c++)
			{
				if (songlim[a][b][c] > best)
					best = songlim[a][b][c];

				//If we can legally without problem use this value to initialize future values.
				if (songlim[a][b][c] != -1)
				{
					//Loop through the songs that we can still put on the disk due to the song restriction
					for (d = c + 1;d <= csong;d++)
					{
						//Test if we can still fit song d on the last disk using the length of the song.
						if (songlen[d] + b <= minpdisk)
						{
							//If we add this song on to the last disk we see if it is the best we can do for the current parameters of [a][b][c].
							if (songlim[a][b][c] + 1 > songlim[a][b + songlen[d]][d])
								songlim[a][b + songlen[d]][d] = songlim[a][b][c] + 1;
						}
						else
						{
							//If we can't fit the current song onto the disk, we use another disk and test if it is the best we can do for the current parameters of [a][b][c] if we add the song on.
							if (a + 1 <= cdisk) //Check that this is not the last disk first.
								if (songlim[a][b][c] + 1 > songlim[a + 1][songlen[d]][d])
									songlim[a + 1][songlen[d]][d] = songlim[a][b][c] + 1;
						}
					}
				}
			}
		}
	}

	out << best << "\n";
	out.close ();

	return 0;
}