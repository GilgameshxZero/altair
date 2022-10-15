/*
ID: yangchess1
PROG: zerosum
LANG: C++
*/

//IDK why, but my solution won't work

//#include <fstream>
//#include <string>
//using namespace std;
//
//int number, sign[9] = {0,0,0,0,0,0,0,0,0}, scount = -1;
//string solution[100];
//
//void solve (unsigned short loops)
//{
//	int a, n = 0, term = 0, multiplier = 1;
//
//	if (loops == 0)
//	{
//		solution[++scount] = "1";
//
//		for (a = 0;a < number - 1;a++)
//		{
//			if (sign[a] == 0)
//				solution[scount] += "-";
//			if (sign[a] == 1)
//				solution[scount] += "+";
//			if (sign[a] == 2)
//				solution[scount] += " ";
//
//			solution[scount] += a + 2 + 48;
//		}
//
//		for (a = 0;a < 2 * number - 1;a++)
//		{
//			switch (solution[scount][a])
//			{
//				case '+':
//					n += multiplier * term;
//					term = 0;
//					multiplier = 1;
//					break;
//				case '-':
//					n += multiplier * term;
//					term = 0;
//					multiplier = -1;
//					break;
//				case ' ':
//					break;
//				default:
//					term = term * 10 + solution[scount][a] - 48;
//			}
//		}
//
//		n += multiplier * term;
//
//		if (n != 0)
//			scount--;
//
//		return;
//	}
//
//	for (a = 0;a < 3;a++)
//	{
//		sign[loops - 1] = a;
//		solve (loops - 1);
//	}
//}
//int main ()
//{
//	ifstream in;
//	ofstream out;
//	unsigned short a, b;
//	string temp;
//
//	in.open ("zerosum.in");
//	in >> number;
//	in.close ();
//
//	solve (number - 1);
//
//	for (a = 0;a < scount;a++)
//	{
//		for (b = 0;b < scount - 1;b++)
//		{
//			if (solution[b] > solution[b + 1])
//			{
//				temp = solution[b];
//				solution[b] = solution[b + 1];
//				solution[b + 1] = temp;
//			}
//		}
//	}
//
//	out.open ("zerosum.out");
//	for (a = 0;a < scount;a++)
//		out << solution[a] << "\n";
//	out.close ();
//
//	return 0;
//}
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int n;

int cal(char exp[])
{
        int i,len = strlen(exp);
        int sum = 0,op;
        char oprt = '+';
        i=0;
        while(i<len)
        {
                op=0;
                while(i<len&&exp[i]!='+'&&exp[i]!='-')
                {
                        if (isdigit(exp[i]))
                                op = op*10+exp[i]-'0';
                        i++;
                }                               
                if (oprt=='+')
                        sum+=op;
                else
                        sum-=op;
                if (exp[i]=='+'||exp[i]=='-')
                        oprt=exp[i];
                i++;
        }
        return sum;
}

void dfs(int depth,char exp[])
{
    char str[20];
        int len;
        if (depth==n-1)
        {
                if (cal(exp)==0)
                        printf("%s\n",exp);
        }
        else
        {
                strcpy(str,exp);
                len = strlen(str);
                str[len]=' ';
                str[len+1]='0'+depth+2;
                str[len+2]='\0';
                dfs(depth+1,str);
                str[len]='+';
                dfs(depth+1,str);
                str[len]='-';
                dfs(depth+1,str);               
        }
}

int main()
{
        freopen("zerosum.in","r",stdin);        
        freopen("zerosum.out","w",stdout);
        scanf("%d",&n);
        dfs(0,"1");     
        return 0;
}