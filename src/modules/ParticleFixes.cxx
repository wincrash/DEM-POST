#include "ParticleFixes.h"

ParticleFixes::ParticleFixes()
{

}
void ParticleFixes::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{
    calculate=true;
    int maxFix=0;
    for(auto &p:current.particles)
    {
        int fix=p.fix;
        if(fix>maxFix) maxFix=fix;
    }
    FORCE.resize(maxFix+1,0);
    for(auto &p:current.particles)
    {
        double fx=p.force[0];
        double fy=p.force[1];
        double fz=p.force[2];
        double f=std::sqrt(fx*fx+fy*fy+fz*fz);
        FORCE[p.fix]=FORCE[p.fix]+f;
    }

}

void ParticleFixes::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        for(int i=0;i<FORCE.size();i++)
        {
            names.push_back(getName("PARTICLE_FIX_FORCE",i));
            values.push_back(FORCE[i]);
        }
    }
}

