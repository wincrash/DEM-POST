#include "IndividualParticles.h"

IndividualParticles::IndividualParticles()
{

}

void IndividualParticles::Compute(TASKAI &points,ParsingParameters*params)
{
    auto result= params->getResults();
    if (result.count("particles"))
    {
        calculate=true;
        ParticleNR=result["particles"].as<std::vector<int>>();
        for(int i=0;i<ParticleNR.size();i++)
        {
            int id=ParticleNR[i];
            Particles.push_back(points[id]);
        }
    }

}
void IndividualParticles::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        for(int i=0;i<ParticleNR.size();i++)
        {
            Point p=Particles[i];
            int ID=ParticleNR[i];
            names.push_back(getName("ParticlePOSX",ID));
            values.push_back(p.x);
            names.push_back(getName("ParticlePOSY",ID));
            values.push_back(p.y);
            names.push_back(getName("ParticlePOSZ",ID));
            values.push_back(p.z);

            names.push_back(getName("ParticleVELX",ID));
            values.push_back(p.vx);

            names.push_back(getName("ParticleVELY",ID));
            values.push_back(p.vy);

            names.push_back(getName("ParticleVELZ",ID));
            values.push_back(p.vz);


            names.push_back(getName("ParticleFORCEX",ID));
            values.push_back(p.fx);
            names.push_back(getName("ParticleFORCEY",ID));
            values.push_back(p.fy);
            names.push_back(getName("ParticleFORCEZ",ID));
            values.push_back(p.fz);
            names.push_back(getName("ParticleFORCE",ID));
            values.push_back(p.force);

            names.push_back(getName("ParticleTEMPERATURE",ID));
            values.push_back(p.temperature);

        }
    }
}
