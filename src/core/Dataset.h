#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include "Particle.h"
#include "Boundary.h"
#include <string>
#include <sstream>
#include <algorithm>

class Dataset
{
public:
    Dataset(std::string filename);
    ParticlesType particles;
    Boundary boundaries;
    std::string filename;

    long STEP;
    double TIME;
    double THERMAL_TIME;
    int NUMBER_OF_PARTICLES;
    int NUMBER_OF_BOUNDARIES;
};

auto getName=[](auto a,auto b)->std::string
{
    std::stringstream str;
    str<<a<<"_"<<b;
    return str.str();
};

inline void GetBoundsWithR(ParticlesType&points,double bounds[6])
{
    bounds[0]=1000000000;
    bounds[1]=-1000000000;
    bounds[2]=1000000000;
    bounds[3]=-1000000000;
    bounds[4]=1000000000;
    bounds[5]=-1000000000;
    std::for_each(points.begin(), points.end(), [&bounds](Particle &p)
    {
        double x=p.position[0];
        double y=p.position[1];
        double z=p.position[2];
        double r=p.radius;
        if((x-r)<bounds[0]) bounds[0]=x-r;
        if((y-r)<bounds[2]) bounds[2]=y-r;
        if((z-r)<bounds[4]) bounds[4]=z-r;

        if((x+r)>bounds[1]) bounds[1]=x+r;
        if((y+r)>bounds[3]) bounds[3]=y+r;
        if((z+r)>bounds[5]) bounds[5]=z+r;
    });
}
#endif // DATASET_H
