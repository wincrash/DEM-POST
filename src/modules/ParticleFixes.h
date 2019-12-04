#ifndef PARTICLEFIXES_H
#define PARTICLEFIXES_H

#include "../core/AModule.h"

class ParticleFixes:public AModule
{
public:
    ParticleFixes();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::vector<double> FORCE;
};

#endif // PARTICLEFIXES_H
