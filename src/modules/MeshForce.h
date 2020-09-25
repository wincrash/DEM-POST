#ifndef MeshForce_H
#define MeshForce_H
#include "../core/AModule.h"

class MeshForce:public AModule
{
public:
    MeshForce();
    void Calculate(ParsingParameters*params,Dataset &zero,Dataset&current);
    void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::vector<int> MeshID;
    std::vector<double> PX;
    std::vector<double> PY;
    std::vector<double> PZ;
    std::vector<double> F;
    std::vector<std::pair<int,int>> MeshIDPairs;
};


#endif // MeshForce_H
