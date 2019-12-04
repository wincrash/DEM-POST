#ifndef GLOBALPARAMETERS_H
#define GLOBALPARAMETERS_H

#include "ACalculations.h"
#include "../H5Parser/ParsingParameters.h"

class GlobalParameters:public ACalculations
{
public:
    GlobalParameters();
    virtual void Compute(TASKAI &points,ParsingParameters*params);
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);

    double TotalMass=0;
    double TotalVolume=0;
    int NumberOfParticles=0;


};


#endif // GLOBALPARAMETERS_H
