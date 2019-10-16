#ifndef POROCITYINBOX_H
#define POROCITYINBOX_H
#include "ACalculations.h"

class PorocityInBox:public ACalculations
{
public:
    PorocityInBox();
    virtual void Compute(TASKAI &points,ParsingParameters*params);
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::string name="POROCITY";
    double value=0;
};

#endif // POROCITYINBOX_H
