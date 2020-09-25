#include "MeshForce.h"

MeshForce::MeshForce()
{

}
void MeshForce::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{
    auto result= params->getResults();
    if (result.count("MeshForce"))
    {
        calculate=true;
        MeshIDPairs.resize(0);
        auto rr=result["MeshForce"].as<std::vector<int>>();
        for(int i=0;i<rr.size();i=i+2)
        {
            std::pair<int,int> p;
            p.first=rr[i];
            p.second=rr[i+1];
            MeshID.push_back(MeshIDPairs.size());
            MeshIDPairs.push_back(p);

        }
        for(size_t i=0;i<MeshIDPairs.size();i++)
        {

            auto pora=MeshIDPairs[i];
            int kiekis=0;
            double xglobal=0;
            double yglobal=0;
            double zglobal=0;
            double forceGlobal=0;
            for(size_t id=pora.first;id<pora.second;id++)
            {
                kiekis++;
                double x1=current.boundaries.POINTS[id*4*3+0*4+0];
                double x2=current.boundaries.POINTS[id*4*3+1*4+0];
                double x3=current.boundaries.POINTS[id*4*3+2*4+0];

                double y1=current.boundaries.POINTS[id*4*3+0*4+1];
                double y2=current.boundaries.POINTS[id*4*3+1*4+1];
                double y3=current.boundaries.POINTS[id*4*3+2*4+1];


                double z1=current.boundaries.POINTS[id*4*3+0*4+2];
                double z2=current.boundaries.POINTS[id*4*3+1*4+2];
                double z3=current.boundaries.POINTS[id*4*3+2*4+2];
                xglobal+=(x1+x2+x3)/3.0;
                yglobal+=(y1+y2+y3)/3.0;
                zglobal+=(z1+z2+z3)/3.0;
                forceGlobal+=current.boundaries.FORCE[id];
            }
            xglobal/=kiekis;
            yglobal/=kiekis;
            zglobal/=kiekis;
            PX.push_back(xglobal);
            PY.push_back(yglobal);
            PZ.push_back(zglobal);

            F.push_back(forceGlobal);
        }
    }

}

void MeshForce::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        for(size_t i=0;i<MeshID.size();i++)
        {
            int id=MeshID[i];
            names.push_back(getName("MeshForce_X",id));
            values.push_back(PX[i]);
            names.push_back(getName("MeshForce_Y",id));
            values.push_back(PY[i]);
            names.push_back(getName("MeshForce_Z",id));
            values.push_back(PZ[i]);
            names.push_back(getName("MeshForce_FORCE",id));
            values.push_back(F[i]);
        }
    }
}
