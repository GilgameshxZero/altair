#include <vector>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include <string>
#include <set>
using namespace std;

int main ()
{
	freopen ("nocow.in", "r", stdin);
	freopen ("nocow.out", "w", stdout);
	int n, k;
	cin >> n >> k;

	string ts1;
	vector< set<string> > adj_set;
	vector< vector<string> > mia, adj;
	mia.resize (n);
	for (int a = 0, b;a < n;a++)
	{
		cin >> ts1 >> ts1 >> ts1 >> ts1 >> ts1;
		b = 0;
		while (ts1 != "cow.")
		{
			if (adj_set.size () == b)
				adj_set.push_back (set<string>());
			adj_set[b].insert (ts1);
			mia[a].push_back (ts1);
			cin >> ts1;
			b++;
		}
	}
	adj.resize (adj_set.size ());
	for (int a = 0;a < adj_set.size ();a++)
		for (set<string>::iterator b = adj_set[a].begin ();b != adj_set[a].end ();b++)
			adj[a].push_back ((*b));

	vector<int> bsize;
	bsize.resize (adj.size ());
	bsize[adj.size () - 1] = 1;
	for (int a = adj.size () - 2;a >= 0;a--)
		bsize[a] = bsize[a + 1] * adj[a + 1].size();

	vector<int> conv_mia;
	conv_mia.resize (mia.size ());
	for (int a = 0;a < mia.size ();a++)
	{
		conv_mia[a] = 0;
		for (int b = 0, c;b < mia[a].size ();b++)
		{
			for (c = 0;c < adj[b].size ();c++)
				if (adj[b][c] == mia[a][b])
					break;
			conv_mia[a] += bsize[b] * c;
		}
	}

	sort (conv_mia.begin (), conv_mia.end ());
	k--;
	for (int a = 0;a < conv_mia.size ();a++)
	{
		if (conv_mia[a] > k)
			break;
		k++;
	}

	vector<int> ans;
	ans.resize (adj.size ());
	for (int a = 0;a < adj.size ();a++)
	{
		ans[a] = k / bsize[a];
		k %= bsize[a];
	}

	for (int a = 0;a < adj.size () - 1;a++)
		cout << adj[a][ans[a]] << " ";
	cout << adj[adj.size () - 1][ans[adj.size () - 1]] << "\n";

	return 0;
}