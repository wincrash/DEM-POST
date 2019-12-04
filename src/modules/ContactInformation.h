#ifndef CONTACTINFORMATION_H
#define CONTACTINFORMATION_H
#include "../core/AModule.h"

class ContactInformation:public AModule
{
public:
    ContactInformation();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    double coordinationNumber=0;
    double maxOverlap=0;
    double avgOverlap=0;
    int ContactCount=0;
};

#endif // CONTACTINFORMATION_H
