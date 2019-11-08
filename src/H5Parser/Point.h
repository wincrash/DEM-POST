#ifndef POINT_H
#define POINT_H
#include <vector>
#include <string>
#include <sstream>
#define PI 3.14159265359
class Point
{
public:
    Point();
    int fix;
    int mat;
    double x;
    double y;
    double z;

    double vx;
    double vy;
    double vz;
    double mass;

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

double GetDistance(Point &P1,Point &P2);
#endif // POINT_H
