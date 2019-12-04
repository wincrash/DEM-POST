#ifndef LINESTRAIN_H
#define LINESTRAIN_H

#include "../core/AModule.h"

class LineStrain:public AModule
{
public:
    LineStrain();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::vector<double> POS_X;
    std::vector<double> POS_Y;
    std::vector<double> POS_Z;
    std::vector<double> STRAIN_X;
    std::vector<double> STRAIN_Y;
    std::vector<double> STRAIN_Z;
    std::vector<double> STRAIN;
};


#endif // LINESTRAIN_H
