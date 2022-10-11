/*
ID: yangchess1
LANG: C
PROB: starry
*/
#include<stdio.h>
#include<string.h>

char skymap[128][128],visit[128][128],output[128][128],atoz[27][9][128][128],tmap[128][128],tmp[128][128],mm[128][128];

int cmp[27],total,ni,nj,cmn,w,h,l,r,u,d,total;

struct SM{char w,h;}wh[27][9];

void Updata(int i,int j,char a)
{
	if(i<1||j<1||i>h||j>w||skymap[i][j]=='0'||output[i][j]==a)
		return;
	output[i][j]=a;
	Updata(i-1,j-1,a);
	Updata(i-1,j,a);
	Updata(i-1,j+1,a);
	Updata(i,j-1,a);
	Updata(i,j+1,a);
	Updata(i+1,j-1,a);
	Updata(i+1,j,a);
	Updata(i+1,j+1,a);
}

void search(int i,int j)
{
	if(i<1||j<1||i>h||j>w||skymap[i][j]=='0'||visit[i][j]==1)
		return;
	if(i<u)
		u=i;
	if(i>d)
		d=i;
	if(j<l)
		l=j;
	if(j>r)
		r=j;
	visit[i][j]=1;
	search(i-1,j-1);
	search(i-1,j);
	search(i-1,j+1);
	search(i,j-1);
	search(i,j+1);
	search(i+1,j-1);
	search(i+1,j);
	search(i+1,j+1);
}

void make(int i,int j)
{
	if(i<1||j<1||i>ni||j>nj||tmp[i][j]=='0'||tmap[i][j]==1)
		return;
	tmap[i][j]=1;
	make(i-1,j-1);
	make(i-1,j);
	make(i-1,j+1);
	make(i,j-1);
	make(i,j+1);
	make(i+1,j-1);
	make(i+1,j);
	make(i+1,j+1);
}	

int Judge()
{
	int i,j,flag,k1,k2;
	for(i=1;i<=total;i++)
	{
		if(cmp[i]!=cmn)
			continue;
		for(j=1;j<=8;j++)
		{
			if(wh[i][j].w!=nj||wh[i][j].h!=ni)
				continue;
			for(k1=1,flag=0;k1<=ni;k1++)
			{
				if(flag==1)
					break;
				for(k2=1;k2<=nj;k2++)
				{
					if(atoz[i][j][k1][k2]!=tmap[k1][k2])
					{
						flag=1;
						break;
					}
				}
			}
			if(flag==0)
				return i;
		}
	}
	total++;
	cmp[total]=cmn;
	for(i=1;i<=ni;i++)
	{
		for(j=1;j<=nj;j++)
		{
			atoz[total][1][i][j]=tmap[i][j];
			atoz[total][2][nj-j+1][i]=tmap[i][j];
			atoz[total][3][ni-i+1][nj-j+1]=tmap[i][j];
			atoz[total][4][j][ni-i+1]=tmap[i][j];
		}
	}
	for(i=1;i<=ni;i++)
	{
		for(j=1;j<=nj;j++)
		{
			atoz[total][5][i][nj-j+1]=atoz[total][1][i][j];
			atoz[total][7][i][nj-j+1]=atoz[total][3][i][j];
		}
	}
	for(i=1;i<=nj;i++)
	{
		for(j=1;j<=ni;j++)
		{
			atoz[total][6][i][ni-j+1]=atoz[total][2][i][j];
			atoz[total][8][i][ni-j+1]=atoz[total][4][i][j];
		}
	}
	wh[total][1].w=nj;
	wh[total][1].h=ni;
	wh[total][2].w=ni;
	wh[total][2].h=nj;
	wh[total][3].w=nj;
	wh[total][3].h=ni;
	wh[total][4].w=ni;
	wh[total][4].h=nj;
	wh[total][5].w=nj;
	wh[total][5].h=ni;
	wh[total][6].w=ni;
	wh[total][6].h=nj;
	wh[total][7].w=nj;
	wh[total][7].h=ni;
	wh[total][8].w=ni;
	wh[total][8].h=nj;
	return 0;
}

int main()
{
	int i,j,k1,k2,al;
	FILE *fin  = fopen ("starry.in", "r");
    FILE *fout = fopen ("starry.out", "w");
	fscanf(fin,"%d %d",&w,&h);
	for(i=1;i<=h;i++)
	{
		fscanf(fin,"%s",&skymap[i][1]);
	}
	for(i=1;i<=h;i++)
	{
		for(j=1;j<=w;j++)
		{
			output[i][j]='0';
		}
	}
	for(i=1;i<=h;i++)
	{
		for(j=1;j<=w;j++)
		{
			if(visit[i][j])
				continue;
			if(skymap[i][j]=='0')
				visit[i][j]=1;
			else
			{
				r=d=0;
				l=u=1000;
				search(i,j);
				memset(tmp,0,sizeof(tmp));
				memset(tmap,0,sizeof(tmap));
				for(k1=u;k1<=d;k1++)
				{
					for(k2=l;k2<=r;k2++)
					{
						tmp[k1-u+1][k2-l+1]=skymap[k1][k2];
					}
				}	
				ni=d-u+1;
				nj=r-l+1;
				make(i-u+1,j-l+1);	
				cmn=(ni<<8|nj)<(nj<<8|ni)?(ni<<8|nj):(nj<<8|ni);
				al=Judge();
				if(al==0)
				{
					Updata(i,j,'a'+total-1);
				}
				else
				{
					Updata(i,j,'a'+al-1);
				}
			}
		}
	}
	for(i=1;i<=h;i++)
	{
		fprintf(fout,"%s\n",&output[i][1]);
	}
	return 0;
}/*
//I used [y][x] just because it seemed more intuitional to me.

#include <iostream>
#include <fstream>

const int MAXCLUSTERPT	= 160;
const int MAXDIM		= 100;
const int MAXCCLUSTER	= 500;

//Not sure why I used this structure in some places, and not in others.
struct Point
{
	int x, y;
};

struct Cluster
{
	int x[MAXCLUSTERPT], y[MAXCLUSTERPT], cpoint;
	char letter;
};

struct CRect //Cluster rectangle.
{
	int bound_x, bound_y;	//Inclusive bounds.
	bool point[MAXDIM][MAXDIM];
};

//Recursive function used by FindCluster.
void FloodCluster (int y, int x, int c, int cx, int cy, Cluster *rtrn, bool sky_map[MAXDIM][MAXDIM], int cluster_map[MAXDIM][MAXDIM])
{
	//Test all 8 sides. We can test if y - 1 is in range in the same if statement b/c compiler utilizes if order.
	if (y > 0 && sky_map[y - 1][x] == true && cluster_map[y - 1][x] == -1)
	{
		cluster_map[y - 1][x] = c; //Mark which cluster this is part of for future back-references.
		rtrn->x[rtrn->cpoint] = x;
		rtrn->y[rtrn->cpoint++] = y - 1;

		FloodCluster (y - 1, x, c, cx, cy, rtrn, sky_map, cluster_map);
	}
	if (y > 0 && x < cx - 1 && sky_map[y - 1][x + 1] == true && cluster_map[y - 1][x + 1] == -1)
	{
		cluster_map[y - 1][x + 1] = c;
		rtrn->x[rtrn->cpoint] = x + 1;
		rtrn->y[rtrn->cpoint++] = y - 1;

		FloodCluster (y - 1, x + 1, c, cx, cy, rtrn, sky_map, cluster_map);
	}
	if (x < cx - 1 && sky_map[y][x + 1] == true && cluster_map[y][x + 1] == -1)
	{
		cluster_map[y][x + 1] = c;
		rtrn->x[rtrn->cpoint] = x + 1;
		rtrn->y[rtrn->cpoint++] = y;

		FloodCluster (y, x + 1, c, cx, cy, rtrn, sky_map, cluster_map);
	}
	if (x < cx - 1 && y < cy - 1 && sky_map[y + 1][x + 1] == true && cluster_map[y + 1][x + 1] == -1)
	{
		cluster_map[y + 1][x + 1] = c;
		rtrn->x[rtrn->cpoint] = x + 1;
		rtrn->y[rtrn->cpoint++] = y + 1;

		FloodCluster (y + 1, x + 1, c, cx, cy, rtrn, sky_map, cluster_map);
	}
	if (y < cy - 1 && sky_map[y + 1][x] == true && cluster_map[y + 1][x] == -1)
	{
		cluster_map[y + 1][x] = c;
		rtrn->x[rtrn->cpoint] = x;
		rtrn->y[rtrn->cpoint++] = y + 1;

		FloodCluster (y + 1, x, c, cx, cy, rtrn, sky_map, cluster_map);
	}
	if (x > 0 && y < cy - 1 && sky_map[y + 1][x - 1] == true && cluster_map[y + 1][x - 1] == -1)
	{
		cluster_map[y + 1][x - 1] = c;
		rtrn->x[rtrn->cpoint] = x - 1;
		rtrn->y[rtrn->cpoint++] = y + 1;

		FloodCluster (y + 1, x - 1, c, cx, cy, rtrn, sky_map, cluster_map);
	}
	if (x > 0 && sky_map[y][x - 1] == true && cluster_map[y][x - 1] == -1)
	{
		cluster_map[y][x - 1] = c;
		rtrn->x[rtrn->cpoint] = x - 1;
		rtrn->y[rtrn->cpoint++] = y;

		FloodCluster (y, x - 1, c, cx, cy, rtrn, sky_map, cluster_map);
	}
	if (x > 0 && y > 0 && sky_map[y - 1][x - 1] == true && cluster_map[y - 1][x - 1] == -1)
	{
		cluster_map[y - 1][x - 1] = c;
		rtrn->x[rtrn->cpoint] = x - 1;
		rtrn->y[rtrn->cpoint++] = y - 1;

		FloodCluster (y - 1, x - 1, c, cx, cy, rtrn, sky_map, cluster_map);
	}

	return;
}

//Floodfill a cluster based on a point. We need a map of the visited clusters, and a map of the availible stars to do this task. Take a cluster_map array to know if we have already marked this cluster.
Cluster FindCluster (int y, int x, int c, int cx, int cy, bool sky_map[MAXDIM][MAXDIM], int cluster_map[MAXDIM][MAXDIM])
{
	Cluster rtrn;

	rtrn.letter = NULL;

	//We need to store the cluster in rtrn, and mark all its points on the visited array.
	if (cluster_map[y][x] != -1) //This cluster has already been marked.
	{
		rtrn.cpoint = 0;
		return rtrn;
	}

	rtrn.x[0] = x;
	rtrn.y[0] = y;
	rtrn.cpoint = 1;
	cluster_map[y][x] = c;

	FloodCluster (y, x, c, cx, cy, &rtrn, sky_map, cluster_map);

	return rtrn;
}

CRect Rotate (CRect cluster)
{
	CRect rtrn;

	//y = x, x = bound_y - y;
	for (int a = 0;a <= cluster.bound_y;a++)
		for (int b = 0;b <= cluster.bound_x;b++)
			rtrn.point[b][cluster.bound_y - a] = cluster.point[a][b];

	rtrn.bound_x = cluster.bound_y;
	rtrn.bound_y = cluster.bound_x;

	return rtrn;
}
CRect Reflect (CRect cluster)
{
	CRect rtrn;

	//y = y, x = bound_x - x;
	for (int a = 0;a <= cluster.bound_y;a++)
		for (int b = 0;b <= cluster.bound_x;b++)
			rtrn.point[a][cluster.bound_x - b] = cluster.point[a][b];
	
	rtrn.bound_x = cluster.bound_x;
	rtrn.bound_y = cluster.bound_y;

	return rtrn;
}

//Return true if all points are equal at the same coordinates.
bool VerifyCongruency (CRect c1, CRect c2)
{
	if (c1.bound_x != c2.bound_x || c1.bound_y != c2.bound_y)
		return false;

	for (int a = 0;a < c1.bound_y;a++)
		for (int b = 0;b < c1.bound_x;b++)
			if (c1.point[a][b] != c2.point[a][b])
				return false;

	return true;
}

//Return true if two clusters are similar.
bool VerifySimilarity (Cluster c1, Cluster c2)
{
	Point low[2], high[2];
	CRect cluster[2];

	if (c1.cpoint != c2.cpoint)
		return false;

	low[0].x = low[0].y = low[1].x = low[1].y = 100;
	high[0].x = high[0].y = high[1].x = high[1].y = 0;

	//Reduce coordinates.
	for (int a = 0;a < c1.cpoint;a++)
	{
		if (c1.x[a] > high[0].x)
			high[0].x = c1.x[a];
		if (c1.y[a] > high[0].y)
			high[0].y = c1.y[a];
		if (c1.x[a] < low[0].x)
			low[0].x = c1.x[a];
		if (c1.y[a] < low[0].y)
			low[0].y = c1.y[a];

		if (c2.x[a] > high[1].x)
			high[1].x = c2.x[a];
		if (c2.y[a] > high[1].y)
			high[1].y = c2.y[a];
		if (c2.x[a] < low[1].x)
			low[1].x = c2.x[a];
		if (c2.y[a] < low[1].y)
			low[1].y = c2.y[a];
	}

	for (int a = 0;a < c1.cpoint;a++)
	{
		c1.x[a] -= low[0].x;
		c1.y[a] -= low[0].y;

		c2.x[a] -= low[1].x;
		c2.y[a] -= low[1].y;
	}

	//High's are now the bounding rectangles.
	high[0].x -= low[0].x;
	high[0].y -= low[0].y;
	high[1].x -= low[1].x;
	high[1].y -= low[1].y;

	//Draw both clusters onto a CRect.
	for (int a = 0;a < MAXDIM;a++)
		for (int b = 0;b < MAXDIM;b++)
			cluster[0].point[a][b] = cluster[1].point[a][b] = false;

	for (int a = 0;a < c1.cpoint;a++)
	{
		cluster[0].point[c1.y[a]][c1.x[a]] = true;
		cluster[1].point[c2.y[a]][c2.x[a]] = true;
	}

	cluster[0].bound_x = high[0].x;
	cluster[0].bound_y = high[0].y;
	cluster[1].bound_x = high[1].x;
	cluster[1].bound_y = high[1].y;

	//Check all rotations and reflections.
	for (int a = 0;a < 4;a++)
	{
		if (VerifyCongruency (cluster[0], cluster[1]))
			return true;

		if (VerifyCongruency (Reflect (cluster[0]), cluster[1]))
			return true;

		cluster[0] = Rotate (cluster[0]);
	}

	return false;
}

int main ()
{
	std::ofstream out ("starry.out");
	std::ifstream in ("starry.in");
	Cluster cluster[MAXCCLUSTER];		//Clusters.
	int ccluster,						//Count of clusters.
		cx, cy,							//Height and width of the sky.
		cluster_map[MAXDIM][MAXDIM];	//The cluster each star belongs to.
	char letter = 'a';
	bool sky_map[MAXDIM][MAXDIM];		//Star positions.

	ccluster = 0;

	//Input basic data.
	in >> cx >> cy;
	in.get ();

	for (int a = 0;a < cy;a++)
	{
		for (int b = 0;b < cx;b++)
			sky_map[a][b] = (in.get () == '1');

		in.get ();
	}

	in.close ();

	//Initialize variables.
	for (int a = 0;a < cy;a++)
		for (int b = 0;b < cx;b++)
			cluster_map[a][b] = -1;

	//Loop through all the points in the sky. If we stumble upon a 1, floodfill for that 1, and determine the cluster related to that 1.
	for (int a = 0;a < cy;a++)
	{
		for (int b = 0;b < cx;b++)
		{
			if (sky_map[a][b] == true)
			{
				cluster[ccluster++] = FindCluster (a, b, ccluster, cx, cy, sky_map, cluster_map);

				//FindCluster will only return 0 if we have already visited the cluster specified.
				if (cluster[ccluster - 1].cpoint == 0)
					ccluster--;
			}
		}
	}

	//Loop through the cluster, and determine similar clusters.
	for (int a = 0;a < ccluster;a++)
	{
		//No letter yet.
		if (cluster[a].letter == NULL)
		{
			cluster[a].letter = letter;

			for (int b = a + 1; b < ccluster;b++)
			{
				if (a == 1 && b == 5)
					a=a;

				if (VerifySimilarity (cluster[a], cluster[b]))
					cluster[b].letter = letter;
			}

			letter++;
		}
	}

	//Use cluster_map to output letters for each cluster.
	for (int a = 0;a < cy;a++)
	{
		for (int b = 0;b < cx;b++)
		{
			if (cluster_map[a][b] != -1)
				out << cluster[cluster_map[a][b]].letter;
			else
				out << "0";
		}

		out << "\n";
	}

	out.close ();

	return 0;
}*/