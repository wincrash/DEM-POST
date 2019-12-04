#include "GlobalParameters.h"

GlobalParameters::GlobalParameters()
{

}
void GlobalParameters::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{
    calculate=true;
    this->STEP=current.STEP;
    this->TIME=current.TIME;
    this->THERMAL_TIME=current.THERMAL_TIME;
    TotalMass=0;
    TotalVolume=0;
    NUMBER_OF_PARTICLES=current.NUMBER_OF_PARTICLES;
    for(auto &p:current.particles)
    {
        TotalMass=TotalMass+p.mass;
        TotalVolume=TotalVolume+4.0/3.0*p.radius*p.radius*p.radius*PI;
    }
}

void GlobalParameters::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        names.push_back("NUMBER_OF_PARTICLES");
        values.push_back(NUMBER_OF_PARTICLES);
        names.push_back("TOTAL_VOLUME");
        values.push_back(TotalVolume);
        names.push_back("TOTAL_MASS");
        values.push_back(TotalMass);

        names.push_back("STEP");
        values.push_back(STEP);
        names.push_back("TIME");
        values.push_back(TIME);
        names.push_back("THERMAL_TIME");
        values.push_back(THERMAL_TIME);
    }
}
