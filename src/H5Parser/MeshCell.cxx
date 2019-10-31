#include "MeshCell.h"
#include <cmath>

MeshCell::MeshCell()
{

}

void MeshCell::Compute(std::vector<double> &BOUNDARY_POINTS,ParsingParameters*params)
{
    auto result= params->getResults();
    if (result.count("meshcell"))
    {
        calculate=true;
        MeshID=result["meshcell"].as<std::vector<int>>();
        for(int i=0;i<MeshID.size();i++)
        {
            int id=MeshID[i];
            double x1=BOUNDARY_POINTS[id*4*3+0*4+0];
            double x2=BOUNDARY_POINTS[id*4*3+1*4+0];
            double x3=BOUNDARY_POINTS[id*4*3+2*4+0];

            double y1=BOUNDARY_POINTS[id*4*3+0*4+1];
            double y2=BOUNDARY_POINTS[id*4*3+1*4+1];
            double y3=BOUNDARY_POINTS[id*4*3+2*4+1];


            double z1=BOUNDARY_POINTS[id*4*3+0*4+2];
            double z2=BOUNDARY_POINTS[id*4*3+1*4+2];
            double z3=BOUNDARY_POINTS[id*4*3+2*4+2];


            PX.push_back((x1+x2+x3)/3.0);
            PY.push_back((y1+y2+y3)/3.0);
            PZ.push_back((z1+z2+z3)/3.0);
        }

    }

}
void MeshCell::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        for(int i=0;i<MeshID.size();i++)
        {
            int id=MeshID[i];
            names.push_back(getName("MeshCell_X",id));
            values.push_back(PX[i]);
            names.push_back(getName("MeshCell_Y",id));
            values.push_back(PY[i]);
            names.push_back(getName("MeshCell_Z",id));
            values.push_back(PZ[i]);

        }
    }
}
