#ifndef BONDSINFORMATION_H
#define BONDSINFORMATION_H
#include "../core/AModule.h"

class BondsInformation:public AModule
{
public:
    BondsInformation();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
private:
    long BONDS_BROKEN_NORMAL=0;
    long BONDS_BROKEN_SHEAR=0;
    long BONDS_BROKEN_ALL=0;
    long BONDS_TOTAL=0;
    double BONDS_MAX_NORMAL_SIGMA=0;
    double BONDS_MAX_TANGENTIAL_SIGMA=0;
};

#endif // BONDSINFORMATION_H
