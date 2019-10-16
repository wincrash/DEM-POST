#include "Point.h"

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

