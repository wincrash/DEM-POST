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
    std::vector<double> FORCE_X;
    std::vector<double> FORCE_Y;
    std::vector<double> FORCE_Z;

    std::vector<double> POSITION_X;
    std::vector<double> POSITION_Y;
    std::vector<double> POSITION_Z;

    std::vector<double> KIEKIS;
};

#endif // PARTICLEFIXES_H
