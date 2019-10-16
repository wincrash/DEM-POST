#ifndef SPECFORCETIRE_H
#define SPECFORCETIRE_H

#include "ACalculations.h"


class SpecForceTIRE:public ACalculations
{
public:
    SpecForceTIRE();
    virtual void Compute(TASKAI &points,ParsingParameters*params);
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::vector<double> SPEC_FORCE;


    double TotalForceMat0=0;
    double TotalForceMat1=0;
};

#endif // SPECFORCETIRE_H
