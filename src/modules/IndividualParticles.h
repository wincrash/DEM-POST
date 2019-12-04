#ifndef INDIVIDUALPARTICLES_H
#define INDIVIDUALPARTICLES_H
#include "../core/AModule.h"

class IndividualParticles:public AModule
{
public:
    IndividualParticles();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::vector<int> ParticleNR;
    std::vector<Particle> Particles;
};

#endif // INDIVIDUALPARTICLES_H
