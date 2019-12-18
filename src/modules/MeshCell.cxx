#include "MeshCell.h"

MeshCell::MeshCell()
{

}
void MeshCell::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{
    auto result= params->getResults();
    if (result.count("meshcell"))
    {
        calculate=true;
        MeshID=result["meshcell"].as<std::vector<int>>();
        for(size_t i=0;i<MeshID.size();i++)
        {
            size_t id=MeshID[i];
            double x1=current.boundaries.POINTS[id*4*3+0*4+0];
            double x2=current.boundaries.POINTS[id*4*3+1*4+0];
            double x3=current.boundaries.POINTS[id*4*3+2*4+0];

            double y1=current.boundaries.POINTS[id*4*3+0*4+1];
            double y2=current.boundaries.POINTS[id*4*3+1*4+1];
            double y3=current.boundaries.POINTS[id*4*3+2*4+1];


            double z1=current.boundaries.POINTS[id*4*3+0*4+2];
            double z2=current.boundaries.POINTS[id*4*3+1*4+2];
            double z3=current.boundaries.POINTS[id*4*3+2*4+2];


            PX.push_back((x1+x2+x3)/3.0);
            PY.push_back((y1+y2+y3)/3.0);
            PZ.push_back((z1+z2+z3)/3.0);
            F.push_back(current.boundaries.FORCE[id]);

            double maxas=0;
            double avg=0;
            int overlap_kiekis=0;
            for(auto &p:current.particles)
            {
                double ilgis=p.radius-fabs(PX[i]-p.position[0]);
                if(ilgis<0)
                {
                    overlap_kiekis++;
                    avg=avg+ilgis;
                    if(maxas<ilgis) maxas=ilgis;
                }

            }

        }
    }

}

void MeshCell::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        for(size_t i=0;i<MeshID.size();i++)
        {
            int id=MeshID[i];
            names.push_back(getName("MeshCell_X",id));
            values.push_back(PX[i]);
            names.push_back(getName("MeshCell_Y",id));
            values.push_back(PY[i]);
            names.push_back(getName("MeshCell_Z",id));
            values.push_back(PZ[i]);
            names.push_back(getName("MeshCell_FORCE",id));
            values.push_back(F[i]);
            names.push_back(getName("MeshCell_MAX_OVERLAP",id));
            values.push_back(MAX_OVERLAP[i]);
            names.push_back(getName("MeshCell_AVG_OVERLAP",id));
            values.push_back(AVG_OVERLAP[i]);
        }
    }
}
