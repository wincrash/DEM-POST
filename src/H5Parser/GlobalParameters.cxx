#include "GlobalParameters.h"

GlobalParameters::GlobalParameters()
{

}

void GlobalParameters::Compute(TASKAI &points,ParsingParameters*params)
{
        calculate=true;
        TotalMass=0;
        TotalVolume=0;
        NumberOfParticles=points.size();
        for(Point &p:points)
        {
            TotalMass=TotalMass+p.mass;
            TotalVolume=TotalVolume+4.0/3.0*p.r*p.r*p.r*PI;
        }


}
void GlobalParameters::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
            names.push_back("NumberOfParticles");
            values.push_back(NumberOfParticles);
            names.push_back("TotalVolume");
            values.push_back(TotalVolume);
            names.push_back("TotalMass");
            values.push_back(TotalMass);
}
