#include<iostream>
using namespace std;
#include<stdlib.h>
#include<stack>
#include<time.h>

struct Point
{
	int x;
	int y;
};

Point p0;

void swap(Point &p1, Point &p2)
{
	Point temp=p1;
	p1=p2;
	p2=temp;
}

//Returns the square of the distance between the two points
int dist(Point p1, Point p2)
{
    	return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y);
}


// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p,Point q,Point r)
{	
	int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if(val==0)
		return 0;
	return (val>0) ? 1 : 2;
}

//Sort an array of points with respect to the first point
int compare(const void *vp1,const void *vp2)	
{
   	Point *p1 = (Point *)vp1;
   	Point *p2 = (Point *)vp2;
 
   	int o = orientation(p0, *p1, *p2);
   	if (o == 0)
     		return (dist(p0, *p2) >= dist(p0, *p1))? -1 :1;
 
   	return (o == 2)? -1: 1;
}

Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

void convexHull(Point points[],int n)
{
	int ymin=points[0].y, min=0;
	for(int i=0;i<n;i++)
	{
		int y=points[i].y;
		if(y<ymin || (y==ymin && points[i].x<points[min].x))
			ymin=points[i].y, min=i;
	}
	
	swap(points[0], points[min]);
	
	p0=points[0];
	/*
	 void qsort (void* base, size_t num, size_t size, int (*compar)(const void*,const void*));
	 -->Sorts the num elements of the array pointed by base, each element size bytes long, using the compar function to determine the order.
	*/
	qsort(&points[1], n-1, sizeof(Point), compare);
	
	stack<Point> S;
	S.push(points[0]);
	S.push(points[1]);
	S.push(points[2]);
	
	for(int i=3;i<n;i++)
	{
		while(orientation(nextToTop(S),S.top(),points[i])!=2)
			S.pop();
		S.push(points[i]);
	}
	
	while(!S.empty())	
	{
		Point p=S.top();
		cout<< "(" << p.x << ", " << p.y << ")" << endl;
		S.pop();
	}
}

int main()
{
	int n;
	cout<<"Enter the number of points you want to generate:";
	cin>>n;
	Point points[n];
	srand( (unsigned)time(NULL) ); 
	for(int i=0;i<n;i++)
	{
		points[i].x = rand() % 100 + 1;
		points[i].y = rand() % 100 + 1;
		cout<<"("<<points[i].x<<","<<points[i].y<<")";
		if(i==(n-1))
			cout<<endl;
	}	
	int m = sizeof(points)/sizeof(points[0]);
	convexHull(points, m);
	return 0;
}

