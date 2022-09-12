#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>

using namespace std;

int main () {
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	string s;
	in >> s;

	bitset<52> deck;
	deck.reset ();

	vector< pair<int, int> > t;
	int cnt[4] = {0, 0, 0, 0};

	for (int a = 0;a < s.length ();a += 3)
	{
		t.push_back (make_pair (0, 0));
		if (s[a] == 'P')
			t.back ().first = 0;
		else if (s[a] == 'K')
			t.back ().first = 1;
		else if (s[a] == 'H')
			t.back ().first = 2;
		else if (s[a] == 'T')
			t.back ().first = 3;

		t.back ().second = (s[a + 1] - '0') * 10 + (s[a + 2] - '0');
	}

	for (int a = 0;a < t.size ();a++)
	{
		if (deck[t[a].first * 13 + t[a].second - 1])
		{
			out << "GRESKA";
			return 0;
		}
		else
		{
			deck[t[a].first * 13 + t[a].second - 1] = true;
			cnt[t[a].first]++;
		}
	}

	for (int a = 0;a < 4;a++)
		out << 13 - cnt[a] << ' ';

	in.close ();
	out.close ();

	return 0;
}