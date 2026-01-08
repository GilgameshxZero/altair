//Solution by Yang Yan
#include <iostream>
#include <cstdio>
using namespace std;

struct LLNode
{
	int val, minv, maxv;
	LLNode *last;
};

struct LLNodeMod
{
	int minv, maxv;
	LLNodeMod *last;
};

LLNode *top;
LLNodeMod *bot;
int N, T, ans, tsize, bsize;

inline bool IsEmpty ()
{
	return (tsize == 0 && bsize == 0);
}

inline int GetLen ()
{
	return tsize + bsize;
}

void Push (int val)
{
	LLNode *q = new LLNode;
	q->val = val;

	if (tsize == 0)
		q->minv = val,
		q->maxv = val;
	else
		q->minv = min (val, top->minv),
		q->maxv = max (val, top->maxv);

	q->last = top;
	top = q;
	tsize++;
}

void Pop ()
{
	if (bsize != 0)
	{
		bsize--;

		LLNodeMod *t = bot->last;
		delete bot;
		bot = t;
	}
	else
	{
		LLNodeMod *t;
		LLNode *p;
		while (tsize != 0)
		{
			t = new LLNodeMod;
			if (bsize == 0)
				t->minv = top->val,
				t->maxv = top->val;
			else
				t->minv = min (top->val, bot->minv),
				t->maxv = max (top->val, bot->maxv);

			bsize++;
			t->last = bot;
			bot = t;

			tsize--;
			p = top->last;
			delete top;
			top = p;
		}

		bsize--;
		t = bot->last;
		delete bot;
		bot = t;
	}
}

int GetMax ()
{
	if (IsEmpty ())
		exit (0);
	if (tsize == 0)
		return bot->maxv;
	else if (bsize == 0)
		return top->maxv;
	else
		return max (top->maxv, bot->maxv);
}

int GetMin ()
{
	if (IsEmpty ())
		exit (0);
	if (tsize == 0)
		return bot->minv;
	else if (bsize == 0)
		return top->minv;
	else
		return min (top->minv, bot->minv);
}

int main ()
{
	//freopen ("pilots.in", "r", stdin); freopen ("pilots.out", "w", stdout);

	scanf ("%d%d", &T, &N);

	int x;
	scanf ("%d", &x);
	Push (x);
	for (int a = 1;a < N;a++)
	{
		if (GetMax () - GetMin () <= T)
			ans = max (ans, GetLen ());
		else
			Pop ();
		scanf ("%d", &x);
		Push (x);
	}

	if (GetMax () - GetMin () <= T)
		ans = max (ans, GetLen ());
	
	printf ("%d\n", ans);

	return 0;
}