#ifndef INDIVIDUALPARTICLES_H
#define INDIVIDUALPARTICLES_H
#include "ACalculations.h"

class IndividualParticles:public ACalculations
{
public:
    IndividualParticles();
    virtual void Compute(TASKAI &points,ParsingParameters*params);
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);

    std::vector<int> ParticleNR;
    std::vector<Point> Particles;

};

#endif // INDIVIDUALPARTICLES_H
