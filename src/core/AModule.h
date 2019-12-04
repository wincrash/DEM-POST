#ifndef AMODULE_H
#define AMODULE_H
#include "Dataset.h"
#include "ParsingParameters.h"
class AModule
{
public:
    AModule();
    virtual void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)=0;
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)=0;
    bool calculate=false;
};

#endif // AMODULE_H
