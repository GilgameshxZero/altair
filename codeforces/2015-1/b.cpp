#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

struct TNode
{
	int cnt;
	TNode *down[26];

	TNode ()
	{
		cnt = 0;
		for (int a = 0;a < 26;a++)
			down[a] = NULL;
	}
};

//returns length until we reach cnt = 1 or total len otherwise
int Insert (TNode *root, string &s)
{
	int r = 0;
	root->cnt++;
	for (int a = 0;a < s.length ();a++)
	{
		if (root->down[s[a] - 'a'] == NULL)
		{
			root->down[s[a] - 'a'] = new TNode;
			root = root->down[s[a] - 'a'];
			root->cnt = 1;
		}
		else
		{
			root = root->down[s[a] - 'a'];
			root->cnt++;
		}

		if (root->cnt == 1 && r == 0)
			r = a + 1;
	}

	if (r == 0)
		return s.length ();
	return r;
}

//`delete` everything under cur
void CleanUp (TNode *cur)
{
	for (int a = 0;a < 26;a++)
	{
		if (cur->down[a] != NULL)
			CleanUp (cur->down[a]),
			delete cur->down[a],
			cur->down[a] = NULL;
	}
}

int main ()
{
	freopen ("in.txt", "r", stdin);
	freopen ("out.txt", "w", stdout);

	int T;
	cin >> T;

	TNode root;
	string s;
	for (int a = 1;a <= T;a++)
	{
		int N;
		cin >> N;

		int ans = 0;
		for (int b = 0;b < N;b++)
		{
			cin >> s;
			ans += Insert (&root, s);
		}

		cout << "Case #" << a << ": " << ans << "\n";
		CleanUp (&root);
		//root = TNode ();
		root.cnt = 0;
	}

	return 0;
}