#ifndef BOUNDARIES_H
#define BOUNDARIES_H
#include "../core/AModule.h"

class Boundaries:public AModule
{
public:
    Boundaries();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    double PARTICLES_BOUNDARY_MIN_X=0;
    double PARTICLES_BOUNDARY_MIN_Y=0;
    double PARTICLES_BOUNDARY_MIN_Z=0;

    double PARTICLES_BOUNDARY_MAX_X=0;
    double PARTICLES_BOUNDARY_MAX_Y=0;
    double PARTICLES_BOUNDARY_MAX_Z=0;

    double PARTICLES_BOUNDARY_LENGTH_X=0;
    double PARTICLES_BOUNDARY_LENGTH_Y=0;
    double PARTICLES_BOUNDARY_LENGTH_Z=0;

    double PARTICLES_BOUNDARY_STRAIN_X=0;
    double PARTICLES_BOUNDARY_STRAIN_Y=0;
    double PARTICLES_BOUNDARY_STRAIN_Z=0;
};

#endif // BOUNDARIES_H
