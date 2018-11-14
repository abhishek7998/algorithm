#include<iostream>
using namespace std;

struct point
{
	int x,y;
};

int Direction(point pi,point pj,point pk)
{
	int x1 = pk.x-pi.x , y1 = pk.y-pi.y;
	int x2 = pj.x-pi.x , y2 = pj.y-pi.y;
	return x1*y2-x2*y1;
}

bool On_Segment(point pi,point pj,point pk)
{
	if( pk.x >= min(pi.x,pj.x) && pk.x <= max(pi.x,pj.x) )
	if( pk.y >= min(pi.y,pj.y) && pk.y <= max(pi.y,pj.y) )
		return true;
	return false;
}
bool Segment_Intersect(point p1,point p2,point p3,point p4)
{
	int d1,d2,d3,d4;
	d1=Direction(p1,p2,p3);
	d2=Direction(p1,p2,p4);
	d3=Direction(p3,p4,p1);
	d4=Direction(p3,p4,p2);

	if(d1*d2<0 && d3*d4<0)
		return true;
	else if(d1==0 && On_Segment(p1,p2,p3))
		return true;
	else if(d2==0 && On_Segment(p1,p2,p4))
		return true;
	else if(d3==0 && On_Segment(p3,p4,p1))
		return true;
	else if(d4==0 && On_Segment(p3,p4,p2))
		return true;
	return false;
}

int main()
{
	point p1,p2,p3,p4;
	cout<<"Enter first point (x,y) :";
	cin>>p1.x>>p1.y;
	cout<<"Enter Second point (x,y) :";
	cin>>p2.x>>p2.y;
	cout<<"Enter third point (x,y) :";
	cin>>p3.x>>p3.y;
	cout<<"Enter fourth point (x,y) :";
	cin>>p4.x>>p4.y;

	bool ans = Segment_Intersect(p1,p2,p3,p4);
	if(ans)
		cout<<"Two Segments Intersects.\n";
	else
		cout<<"No Intersection betwoon two segments.\n";
}
