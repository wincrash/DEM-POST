#ifndef PARTICLE_H
#define PARTICLE_H
#include <vector>
#include <cmath>
#define PI 3.14159265359
class Particle
{
public:
    Particle();
    double position[3];
    double velocity[3];
    double force[3];
    double forceMagnitude;
    double radius;
    double mass;
    double temperature;
    int fix;
    int mat_id;

};
inline double CalcMagnitude(double *x)
{
    return std::sqrt(x[0]*x[0]+x[1]*x[1]+x[2]*x[2]);
}
typedef std::vector<Particle> ParticlesType;

inline double GetDistance(Particle &p1,Particle &p2)
{
    double diff[3];
    for(size_t i =0;i<3;i++)
    {
        diff[i]=p1.position[i]-p2.position[i];
    }
    return  CalcMagnitude(diff);
}


inline void GetMinMaxRadius(ParticlesType&points,double &RMin,double &RMax)
{
    RMin=1000000000;
    RMax=-1000000000;
    for(auto &p:points)
    {
        double r=p.radius;
        if(RMin>r) RMin=r;
        if(RMax<r) RMax=r;
    }
}

#endif // PARTICLE_H
