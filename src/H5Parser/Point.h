#ifndef POINT_H
#define POINT_H
#include <vector>
#include <string>
#include <sstream>

class Point
{
public:
    Point();
    int fix;
    double x;
    double y;
    double z;

    double vx;
    double vy;
    double vz;

    double force;
    double fx;
    double fy;
    double fz;
    double r;
    double temperature;
};

typedef  std::vector<Point> TASKAI;
auto getName=[](auto a,auto b)->std::string
{
    std::stringstream str;
    str<<a<<"_"<<b;
    return str.str();
};



void GetMinMaxRadius(TASKAI &points,double &RMin,double &RMax);


#endif // POINT_H
