/*
ID: yangchess1
LANG: C++
PROG: fence4
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;


const double INF = 1E200;
const double EP = 1E-10;
const int MAXV = 300;
const double PI = 3.14159265;

struct POINT
{
     double x;
     double y;
     POINT(double a=0, double b=0) { x=a; y=b;}
};
struct LINESEG
{
     POINT s;
     POINT e;
     LINESEG(POINT a, POINT b) { s=a; e=b;}
     LINESEG() { }
};

struct LINE
{
     double a;
     double b;
     double c;
     LINE(double d1=1, double d2=-1, double d3=0) {a=d1; b=d2; c=d3;}
};
double dist(POINT p1,POINT p2)
{
     return( sqrt( (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) ) );
}
double multiply(POINT sp,POINT ep,POINT op)
{
     return((sp.x-op.x)*(ep.y-op.y) - (ep.x-op.x)*(sp.y-op.y));
}
double amultiply(POINT sp,POINT ep,POINT op)
{
     return fabs((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y));
}
double dotmultiply(POINT p1,POINT p2,POINT p0)
{
     return ((p1.x-p0.x)*(p2.x-p0.x) + (p1.y-p0.y)*(p2.y-p0.y));
}
bool online(LINESEG l,POINT p)
{
     return (abs(multiply(l.e, p, l.s) <= EP )          //!!!!!
          && ( ( (p.x-l.s.x) * (p.x-l.e.x) <= EP ) && ( (p.y-l.s.y)*(p.y-l.e.y) <= EP ) ) );
}


POINT rotate(POINT o, double alpha, POINT p)
{
     POINT tp;
     p.x -=o.x;
     p.y -=o.y;
     tp.x=p.x*cos(alpha) - p.y*sin(alpha)+o.x;
     tp.y=p.y*cos(alpha) + p.x*sin(alpha)+o.y;
     return tp;
}


bool intersect(LINESEG u,LINESEG v)
{
     return ( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&
          (max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&&
          (max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&&
          (max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&&
          (multiply(v.s,u.e,u.s)*multiply(u.e,v.e,u.s)>=0)&&
          (multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0));
}

bool intersect_A(LINESEG u,LINESEG v)
{
     return ((intersect(u,v)) &&
          (!online(u,v.s)) &&
          (!online(u,v.e)) &&
          (!online(v,u.e)) &&
          (!online(v,u.s)));
}

LINE makeline(POINT p1,POINT p2)
{
     LINE tl;
     int sign = 1;
     tl.a=p2.y-p1.y;
     if(tl.a<0)
     {
          sign = -1;
          tl.a=sign*tl.a;
     }
     tl.b=sign*(p1.x-p2.x);
     tl.c=sign*(p1.y*p2.x-p1.x*p2.y);
     return tl;
}

bool lineintersect(LINE l1,LINE l2,POINT &p)
{
     double d=l1.a*l2.b-l2.a*l1.b;
     if(abs(d)<EP)
          return false;
     p.x = (l2.c*l1.b-l1.c*l2.b)/d;
     p.y = (l2.a*l1.c-l1.a*l2.c)/d;
     return true;
}

bool intersection(LINESEG l1,LINESEG l2,POINT &inter)
{
     LINE ll1,ll2;
     ll1=makeline(l1.s,l1.e);
     ll2=makeline(l2.s,l2.e);
     if(lineintersect(ll1,ll2,inter)) return online(l1,inter) && online(l2, inter);          //!!!!!
     else return false;
}
//////////////////////////////////////////////////////////////////////////

const int N = 200;
int n;
POINT ob, point[N];
LINESEG fence[N];
int visible[N];

void Input ()
{
     int i;
     scanf("%d%lf%lf", &n, &ob.x, &ob.y);
     for (i = 0; i < n; i ++)
          scanf("%lf%lf", &point[i].x, &point[i].y);
     for (i = 0; i < n-1; i ++)
     {
          fence[i].s = point[i];
          fence[i].e = point[i+1];
     }
     fence[n-1].s = point[n-1];
     fence[n-1].e = point[0];
}

bool CheckPolygon (LINESEG* lines, int num)
{
     int i, j;
     for (i = 0; i < num; i ++)
     {
          for (j = 0; j < num; j ++)
          {
               if ( i == j )
                    continue;
               if ( intersect_A(lines[i], lines[j]) )
                    return false;
          }
     }
     return true;
}

void OutputLine (LINESEG line)
{
     printf("line: (%.0lf, %.0lf), (%.0lf, %.0lf)\n", line.s.x, line.s.y, line.e.x, line.e.y);
}

int nearestLine (LINESEG ray, LINESEG* lines, int num)
{
     double curMinDis, tmp;
     int minIdx, i;
     POINT interPoint;

     curMinDis = INF;
     minIdx = -1;
     //every fence
     for (i = 0; i < num; i ++)
     {
          if ( intersection(lines[i], ray, interPoint) && (tmp=dist(ray.s, interPoint)) <= curMinDis)
          {
               curMinDis = tmp;
               minIdx =  i;
          }
     }
     return minIdx;
}

void FindFence ()
{
     int k = 200;
     double delta = 1e-10;
     LINESEG ray, line1;
     POINT interPoint;
     int i, j;
     double curMinDis, tmp;
     int minIdx;

     memset(visible, 0, sizeof(visible));
     ray.s = ob;
     //every point
     for (i = 0; i < n; i ++)
     {
          ray.e = point[i];

          ray.e.x = k * (ray.e.x - ray.s.x) + ray.s.x;
          ray.e.y = k * (ray.e.y - ray.s.y) + ray.s.y;
         
          line1.s = ray.s;
          line1.e = rotate(ray.s, delta, ray.e);
          minIdx = nearestLine(line1, fence, n);
          if ( minIdx != -1 )
          {
               visible[minIdx] = 1;
          }

          line1.e = rotate(ray.s, -1 * delta, ray.e);
          minIdx = nearestLine(line1, fence, n);
          if ( minIdx != -1 )
          {
               visible[minIdx] = 1;
          }
     }
}

void Output ()
{
     int i, cnt = 0;
    
     for (i = 0; i < n; i ++)
          if ( visible[i] )
               ++ cnt;

     printf("%d\n", cnt);
     if ( visible[n-1] )
     {
          swap(fence[n-1].s, fence[n-1].e);
          if ( visible[n-2] )
               swap(fence[n-2], fence[n-1]);
     }
     for (i = 0; i < n; i ++)
     {
          if ( visible[i] )
          {
               printf("%.0lf %.0lf %.0lf %.0lf\n", fence[i].s.x, fence[i].s.y, fence[i].e.x, fence[i].e.y);
          }
     }
}
void Solve ()
{
     if ( ! CheckPolygon(fence, n) )
     {
          printf("NOFENCE\n");
     }
     else
     {
          FindFence();
          Output();
     }
}

int main ()
{

     freopen("fence4.in", "r", stdin);
     freopen("fence4.out", "w", stdout);

     Input();
     Solve();

     return 0;
}

/*
#include <fstream>
#include <cmath>
#include <iostream>

const int MAX_VERT = 199;
const int INTINFINITY = 100000000;

float PointPointDistance (float p1[2], float p2[2])
{
	return sqrt ((p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[2]) * (p1[1] - p2[2]));
}

bool PointOnSegmentInclusive (float point[2], float p1[2], float p2[2])
{
	//If vertical line (p1, p2)
	if (p1[0] == p2[0])
	{
		//If x coordinate is the same and the y coordinate is between inclusive, then it is on the segment.
		if (point[0] == p1[0] && ((point[1] >= p1[1] && point[1] <= p2[1]) || (point[1] <= p1[1] && point[1] >= p2[1])))
			return true;
		else
			return false;
	}
	//If a horozontal line.
	else if (p1[1] == p2[1])
	{
		//If y coordinate is the same and the x coordinate is between inclusive, then it is on the segment.
		if (point[1] == p1[1] && ((point[0] >= p1[0] && point[0] <= p2[0]) || (point[0] <= p1[0] && point[0] >= p2[0])))
			return true;
		else
			return false;
	}
	//If an endpoint and point are the same point
	else if (((point[0] == p1[0]) && (point[1] == p1[1])) || ((point[0] == p2[0]) && (point[1] == p2[1])))
		return true;
	//If a subsegment is vertical (messes up slope calculations later), then return false.
	else if ((point[0] == p1[0]) || (point[0] == p2[0]))
		return false;
	//If not horozontal nor vertical line (p1, p2)
	else
	{
		float x = static_cast<float>((point[1] - p1[1]) / (point[0] - p1[0]));
		float y = static_cast<float>((point[1] - p2[1]) / (point[0] - p2[0]));

		//Test if the slopes are equal for the subsegments (p1, point) and (point, p2) to the third decimal.
		if (static_cast<int>(x * 1000) == static_cast<int>(y * 1000))
		{
			//If the x and y coordinates of the point are between p1 and p2
			if (((point[1] >= p1[1] && point[1] <= p2[1]) || (point[1] <= p1[1] && point[1] >= p2[1])) && ((point[0] >= p1[0] && point[0] <= p2[0]) || (point[0] <= p1[0] && point[0] >= p2[0])))
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

bool PointOnSegmentExclusive (float point[2], float p1[2], float p2[2])
{
	//If vertical line (p1, p2)
	if (p1[0] == p2[0])
	{
		//If x coordinate is the same and the y coordinate is between inclusive, then it is on the segment.
		if (point[0] == p1[0] && ((point[1] > p1[1] && point[1] < p2[1]) || (point[1] < p1[1] && point[1] > p2[1])))
			return true;
		else
			return false;
	}
	//If a horozontal line.
	else if (p1[1] == p2[1])
	{
		//If y coordinate is the same and the x coordinate is between inclusive, then it is on the segment.
		if (point[1] == p1[1] && ((point[0] > p1[0] && point[0] < p2[0]) || (point[0] < p1[0] && point[0] > p2[0])))
			return true;
		else
			return false;
	}
	//If a subsegment is vertical (messes up slope calculations later), then return false.
	else if ((point[0] == p1[0]) || (point[0] == p2[0]))
		return false;
	//If not horozontal nor vertical line (p1, p2)
	else
	{
		float x = static_cast<float>((point[1] - p1[1]) / (point[0] - p1[0]));
		float y = static_cast<float>((point[1] - p2[1]) / (point[0] - p2[0]));

		//Test if the slopes are equal for the subsegments (p1, point) and (point, p2) to the third decimal.
		if (static_cast<int>(x * 1000) == static_cast<int>(y * 1000))
		{
			//If the x and y coordinates of the point are between p1 and p2
			if (((point[1] > p1[1] && point[1] < p2[1]) || (point[1] < p1[1] && point[1] > p2[1])) && ((point[0] > p1[0] && point[0] < p2[0]) || (point[0] < p1[0] && point[0] > p2[0])))
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

bool LineIntersection (float intersection[2], float p1[2], float p2[2], float p3[2], float p4[2])
{
	float a = (p4[0] - p3[0]) * (p1[1] - p3[1]) - (p4[1] - p3[1]) * (p1[0] - p3[0]), 
		b = (p4[1] - p3[1]) * (p2[0] - p1[0]) - (p4[0] - p3[0]) * (p2[1] - p1[1]);

	if (b == 0)
		return false;

	intersection[0] = p1[0] + (p2[0] - p1[0]) * a / b;
	intersection[1] = p1[1] + (p2[1] - p1[1]) * a / b;

	return true;
}

bool SegmentIntersectionInclusive (float intersection[2], float p1[2], float p2[2], float p3[2], float p4[2])
{
	if (LineIntersection (intersection, p1, p2, p3, p4) == false) //If segments are parallel.
		return false;

	if (PointOnSegmentInclusive (intersection, p1, p2) && PointOnSegmentInclusive (intersection, p3, p4)) //Because lines are linear, we test if the intersection x-coordinate of intersection is between both of the lines' x-coordinates.
		return true;

	return false;
}

bool SegmentIntersectionExclusive (float intersection[2], float p1[2], float p2[2], float p3[2], float p4[2])
{
	if (LineIntersection (intersection, p1, p2, p3, p4) == false) //If segments are parallel.
		return false;

	if (PointOnSegmentExclusive (intersection, p1, p2) && PointOnSegmentExclusive (intersection, p3, p4)) //Because lines are linear, we test if the intersection x-coordinate of intersection is between both of the lines' x-coordinates.
		return true;

	return false;
}

bool PointsOnSameSideOfLine (float p1[2], float p2[2], float l1[2], float l2[2])
{
	float intersection[2], a, b;

	if (LineIntersection (intersection, p1, p2, l1, l2) == false) //If these lines are parallel:
		return true; //Then they are on the same side of line l.

	a = PointPointDistance (p1, intersection);
	b = PointPointDistance (p2, intersection);

	if (a > b)
	{
		if (PointPointDistance (p1, p2) < a)
			return true;

		return false;
	}
	else
	{
		if (PointPointDistance (p1, p2) < b)
			return true;

		return false;
	}
}

int main ()
{
	std::ifstream in ("fence4.in");
	std::ofstream out ("fence4.out");
	int cvert, close_fence, output[MAX_VERT][2], a, b;
	float viewpoint[2], midpoint[MAX_VERT][2], vertices[MAX_VERT + 1][2], small_dist, l, p[2];
	bool visible_fence[MAX_VERT];

	for (a = 0;a < MAX_VERT;a++)
		visible_fence[a] = false;

	in >> cvert >> viewpoint[0] >> viewpoint[1];

	for (a = 0;a < cvert;a++)
		in >> vertices[a][0] >> vertices[a][1];

	in.close ();

	//For easier calculations:
	vertices[cvert][0] = vertices[0][0];
	vertices[cvert][1] = vertices[0][1];

	for (a = 0;a < cvert;a++)
	{
		midpoint[a][0] = (vertices[a][0] + vertices[a + 1][0]) / 2;
		midpoint[a][1] = (vertices[a][1] + vertices[a + 1][1]) / 2;
	}

	//We first need to test if the the fence is valid, i.e. none of the sub-fences (sides) intersect.
	for (a = 0;a < cvert;a++) //Loop through all the fences.
	{
		for (b = a + 2;b < cvert + a - 1;b++) //Loop through all fences NOT sharing a vertice with fence[a].
		{
			if (SegmentIntersectionExclusive (p, vertices[a], vertices[a + 1], vertices[b % cvert], vertices[(b + 1) % cvert]) == true) //If some fences not sharing a vertice intersect, then this is not a valid fence. Return immediately.
			{
				out << "NOFENCE\n";
				out.close ();
				return 0;
			}
		}
	}

	//We can see a fence either if we can see the fence's midpoint or some ray from the viewpoint to some vertice not on the fence intersects the fence. To calculate all this, we need the formula's to determine whether a line intersects a line, point intersection of two lines, whether a point is on a line segment, whether a line segment intersects a line segment, and the distance between two points. We first determine all the closest fences (the fences we can see) from the viewpoint to any endpoint on any fence.
	for (a = 0;a < cvert;a++)
	{
		small_dist = INTINFINITY;

		if (a == 198)
			int jkj = 90;

		for (b = 0;b < cvert;b++) //Loop the fences.
		{
			//Calculate the point intersection between the (viewpoint, vert[a]) and fence[b]: (vert[b], vert[b + 1]). This is calculated by LineIntersection (float[2], float[2], float[2], float[2], float[2]).
			LineIntersection (p, viewpoint, vertices[a], vertices[b], vertices[b + 1]);

			//Ensure that the intersection point is indeed on the fence; we know that it is on the viewpoint.
			if (!PointOnSegmentExclusive (p, vertices[b], vertices[b + 1]))
				continue;

			l = PointPointDistance (viewpoint, p);

			if (l < small_dist) //If this segment is closer to the view than the last one, it obstructs the view to the last one, so replace the small_dist and close_fence IDs.
			{
				small_dist = l;
				close_fence = b;
			}
		}

		if (small_dist != INTINFINITY) //If a fence was found on the ray (viewpoint, vertice[a]), add that fence as a can-see fence.
		{
			//Check some special cases. If the fences neighboring the vertex are on different sides of the ray, then this is not a valid sight.
			if (!PointsOnSameSideOfLine (vertices[(a + cvert - 1) % cvert], vertices[(a + 1) % cvert], viewpoint, vertices[a]))
				continue;

			visible_fence[close_fence] = true;
			std::cout << "fence: (" << vertices[close_fence][0] << ", " << vertices[close_fence][1] << ") - (" << vertices[close_fence + 1][0] << ", " << vertices[close_fence + 1][1] << "); a = " << a << "\n";
		}
	}

	//Now we look for the fences which we can directly see the midpoint to. Use the midpoint array.
	for (a = 0;a < cvert;a++)
	{
		if (a == 197)
			a=a;

		for (b = 0;b < cvert;b++) //Loop the fences
		{
			//If the segment (viewpoint, mid[a]) is crossed by another fence segment, then use a new mid.
			if (!LineIntersection (p, viewpoint, midpoint[a], vertices[b], vertices[(b + 1) % cvert])) //If parallel.
				continue;

			if (PointOnSegmentExclusive (p, viewpoint, midpoint[a]) && PointOnSegmentInclusive (p, vertices[b], vertices[(b + 1) % cvert])) //If intersected.
				break;
		}

		if (b == cvert) //If the viewpoint and midpoint were not crossed, then this midpoint is visible.
			visible_fence[a] = true;
	}

	//Output.
	b = 0; //The number of visible fences.

	for (a = 0;a < cvert - 1;a++)
	{
		if (visible_fence[a] == true)
		{
			output[b][0] = a;
			output[b++][1] = a + 1;
		}
	}

	if (visible_fence[cvert - 1] == true)
	{
		output[b][0] = 0;
		output[b++][1] = cvert - 1;

		out << b << "\n";

		for (a = 0;a < b - 2;a++)
			out << vertices[output[a][0]][0] << " " << vertices[output[a][0]][1] << " " << vertices[output[a][1]][0] << " " << vertices[output[a][1]][1] << "\n"; //Output the current fence segment.

		out << vertices[output[b - 1][0]][0] << " " << vertices[output[b - 1][0]][1] << " " << vertices[output[b - 1][1]][0] << " " << vertices[output[b - 1][1]][1] << "\n" << vertices[output[b - 2][0]][0] << " " << vertices[output[b - 2][0]][1] << " " << vertices[output[b - 2][1]][0] << " " << vertices[output[b - 2][1]][1] << "\n";
	}
	else
	{
		out << b << "\n";

		for (a = 0;a < b;a++)
			out << vertices[output[a][0]][0] << " " << vertices[output[a][0]][1] << " " << vertices[output[a][1]][0] << " " << vertices[output[a][1]][1] << "\n"; //Output the current fence segment.
	}

	out.close ();
	std::cin.get ();

	return 0;
}*/