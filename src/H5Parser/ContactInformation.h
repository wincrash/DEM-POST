#ifndef CONTACTINFORMATION_H
#define CONTACTINFORMATION_H
#include "ACalculations.h"


class ContactInformation:public ACalculations
{
public:
    ContactInformation();
    virtual void Compute(TASKAI &points,ParsingParameters*params);
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    double coordinationNumber=0;
    double maxOverlap=0;
    double avgOverlap=0;
    int ContactCount=0;

};
#endif // CONTACTINFORMATION_H
