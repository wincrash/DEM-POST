#ifndef INFORMATIONONLINE_H
#define INFORMATIONONLINE_H
#include "ACalculations.h"

class InformationOnLine:public ACalculations
{
public:
    InformationOnLine();
    virtual void Compute(TASKAI &points,ParsingParameters*params);
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);

};

#endif // INFORMATIONONLINE_H
