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
    FORCE_X.resize(maxFix+1,0);
    FORCE_Y.resize(maxFix+1,0);
    FORCE_Z.resize(maxFix+1,0);
    for(auto &p:current.particles)
    {
        double fx=p.force[0];
        double fy=p.force[1];
        double fz=p.force[2];
        double f=std::sqrt(fx*fx+fy*fy+fz*fz);
        FORCE[p.fix]=FORCE[p.fix]+f;
        FORCE_X[p.fix]=FORCE_X[p.fix]+fx;
        FORCE_Y[p.fix]=FORCE_Y[p.fix]+fy;
        FORCE_Z[p.fix]=FORCE_Z[p.fix]+fz;
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

            names.push_back(getName("PARTICLE_FIX_FORCE_X",i));
            values.push_back(FORCE_X[i]);

            names.push_back(getName("PARTICLE_FIX_FORCE_Y",i));
            values.push_back(FORCE_Y[i]);

            names.push_back(getName("PARTICLE_FIX_FORCE_Z",i));
            values.push_back(FORCE_Z[i]);

        }
    }
}

