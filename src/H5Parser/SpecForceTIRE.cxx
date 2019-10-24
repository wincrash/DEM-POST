#include "SpecForceTIRE.h"
#include <cmath>

SpecForceTIRE::SpecForceTIRE()
{

}

void SpecForceTIRE::Compute(TASKAI &points,ParsingParameters*params)
{
    auto result= params->getResults();
    if (result.count("spec-force"))
    {
        calculate=true;
        for(size_t i=0;i<points.size();i++)
        {
            Point p=points[i];
            if(p.mat==0)
            {
                double fx=SPEC_FORCE[i*4+0];
                double fy=SPEC_FORCE[i*4+1];
                double fz=SPEC_FORCE[i*4+2];
                TotalForceMat0=TotalForceMat0+std::sqrt(fx*fx+fy*fy+fz*fz);
                TotalForce0[0]=TotalForce0[0]+fx;
                TotalForce0[1]=TotalForce0[1]+fy;
                TotalForce0[2]=TotalForce0[2]+fz;

            }
            if(p.mat==1)
            {
                double fx=SPEC_FORCE[i*4+0];
                double fy=SPEC_FORCE[i*4+1];
                double fz=SPEC_FORCE[i*4+2];
                TotalForceMat1=TotalForceMat1+std::sqrt(fx*fx+fy*fy+fz*fz);
                TotalForce1[0]=TotalForce1[0]+fx;
                TotalForce1[1]=TotalForce1[1]+fy;
                TotalForce1[2]=TotalForce1[2]+fz;
            }
        }

    }

}
void SpecForceTIRE::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        names.push_back("TIRE_TOTAL_FORCE_MAT_0");
        values.push_back(TotalForceMat0);
        names.push_back("TIRE_TOTAL_FORCE_MAT_1");
        values.push_back(TotalForceMat1);

        names.push_back("TIRE_TOTAL_FORCE_MAT_0_X");
        values.push_back(TotalForce0[0]);
        names.push_back("TIRE_TOTAL_FORCE_MAT_0_Y");
        values.push_back(TotalForce0[1]);
        names.push_back("TIRE_TOTAL_FORCE_MAT_0_Z");
        values.push_back(TotalForce0[2]);

        names.push_back("TIRE_TOTAL_FORCE_MAT_1_X");
        values.push_back(TotalForce1[0]);
        names.push_back("TIRE_TOTAL_FORCE_MAT_1_Y");
        values.push_back(TotalForce1[1]);
        names.push_back("TIRE_TOTAL_FORCE_MAT_1_Z");
        values.push_back(TotalForce1[2]);


    }
}
