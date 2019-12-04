#ifndef MESHCELL_H
#define MESHCELL_H
#include "../core/AModule.h"

class MeshCell:public AModule
{
public:
    MeshCell();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::vector<int> MeshID;
    std::vector<double> PX;
    std::vector<double> PY;
    std::vector<double> PZ;
    std::vector<double> F;
};


#endif // MESHCELL_H
