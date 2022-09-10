#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <iostream>
using namespace std;

int main ()
{
	//freopen ("Text.txt", "r", stdin);

	int cword, i, r[40];
	vector<string> dic[17];
	string line[40], s;
	char match[26], back[26], omatch[41][26], oback[41][26];

	cin >> cword;

	for (int a = 0;a < cword;a++)
	{
		cin >> s;
		dic[s.length ()].push_back (s);
	}

	while (true)
	{
		memset (omatch, NULL, 40 * 26 * sizeof (char));
		memset (oback, NULL, 40 * 26 * sizeof (char));
		memset (r, 0, 40 * sizeof (int));
		line[0] = "";
		cin >> line[0];

		if (line[0] == "")
			return 0;

		for (i = 1;cin.get () != '\n';i++)
		{
			line[i] = "";
			cin >> line[i];

			if (line[i] == "")
				break;
		}

		for (int a = 0, l, b, c;a <= i;a++)
		{
			if (a == i)
			{
				for (int d = 0;d < i - 1;d++)
				{
					for (int e = 0;e < line[d].length ();e++)
						printf ("%c", (char)match[line[d][e] - 'a']);

					printf (" ");
				}
				
				for (int e = 0;e < line[i - 1].length ();e++)
					printf ("%c", (char)match[line[i - 1][e] - 'a']);
				printf ("\n");
				break;
			}
			if (a == -1)
			{
				for (int d = 0;d < i - 1;d++)
				{
					for (int e = 0;e < line[d].length ();e++)
						printf ("*");

					printf (" ");
				}
				
				for (int e = 0;e < line[i - 1].length ();e++)
					printf ("*");
				printf ("\n");
				break;
			}

			l = line[a].length ();

			for (b = r[a];b < dic[l].size ();b++)
			{
				memcpy (match, omatch[a], 26 * sizeof (char));
				memcpy (back, oback[a], 26 * sizeof (char));
				for (c = 0;c < l;c++)
				{
					if ((match[line[a][c] - 'a'] != NULL && match[line[a][c] - 'a'] != dic[l][b][c]) || 
						(back[dic[l][b][c] - 'a'] != NULL && back[dic[l][b][c] - 'a'] != line[a][c]) || 
						(match[line[a][c] - 'a'] == NULL && back[dic[l][b][c] - 'a'] == line[a][c]) || 
						(match[line[a][c] - 'a'] == dic[l][b][c] && back[dic[l][b][c] - 'a'] == NULL))
						break;
					else
					{
						match[line[a][c] - 'a'] = dic[l][b][c];
						back[dic[l][b][c] - 'a'] = line[a][c];
					}
				}

				if (c == l)
				{
					r[a] = b + 1;
					memcpy (omatch[a + 1], match, 26 * sizeof (char));
					memcpy (oback[a + 1], back, 26 * sizeof (char));
					break;
				}
			}

			if (b == dic[l].size ())
			{
				r[a] = 0;
				a -= 2;
			}
		}
	}

	return 0;
}