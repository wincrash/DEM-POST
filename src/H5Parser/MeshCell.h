#ifndef MeshCell_H
#define MeshCell_H


#include "ACalculations.h"


class MeshCell:public ACalculations
{
public:
    MeshCell();
    virtual void Compute(std::vector<double> &BOUNDARY_POINTS, ParsingParameters*params);
    virtual void GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values);
    std::vector<int> MeshID;
    std::vector<double> PX;
    std::vector<double> PY;
    std::vector<double> PZ;
};
#endif // MeshCell_H
