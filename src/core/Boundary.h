#ifndef BOUNDARY_H
#define BOUNDARY_H
#include <vector>

class Boundary
{
public:
    Boundary();
    std::vector<double> POINTS;
    std::vector<double> FORCE;
    int NUMBER_OF_BOUNDARIES;
};

#endif // BOUNDARY_H
