#ifndef ACALCULATIONS_H
#define ACALCULATIONS_H
#include "Point.h"
#include <string>
#include "ParsingParameters.h"

class ACalculations
{
public:
    ACalculations();
//    virtual void Compute(TASKAI &points,ParsingParameters*params)=0;
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)=0;
    bool calculate=false;
};

#endif // ACALCULATIONS_H
