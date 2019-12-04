#ifndef GLOBALPARAMETERS_H
#define GLOBALPARAMETERS_H
#include "../core/AModule.h"

class GlobalParameters:public AModule
{
public:
    GlobalParameters();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    double TotalMass=0;
    double TotalVolume=0;
    long STEP;
    double TIME;
    double THERMAL_TIME;
    int NUMBER_OF_PARTICLES;
};

#endif // GLOBALPARAMETERS_H
