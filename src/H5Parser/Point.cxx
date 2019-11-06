#include "Point.h"
#include <cmath>
Point::Point()
{

}

void GetMinMaxRadius(TASKAI &points,double &RMin,double &RMax)
{
    RMin=100000000000;
    RMax=-10000000000;
    for(size_t i=0;i<points.size();i++ )
    {
        double r=points[i].r;
        if(RMin>r) RMin=r;
        if(RMax<r) RMax=r;
    }
}

double GetDistance(Point &P1,Point &P2)
{
    double diffx=P1.x-P2.x;
    double diffy=P1.y-P2.y;
    double diffz=P1.z-P2.z;
    return std::sqrt(diffx*diffx+diffy*diffy+diffz*diffz);
}
