#include "IndividualParticles.h"

IndividualParticles::IndividualParticles()
{

}
void IndividualParticles::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{
    auto result= params->getResults();
    if (result.count("particles"))
    {
        calculate=true;
        ParticleNR=result["particles"].as<std::vector<int>>();
        for(int i=0;i<ParticleNR.size();i++)
        {
            int id=ParticleNR[i];
            Particles.push_back(current.particles[id]);
        }
    }
}

void IndividualParticles::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        for(int i=0;i<ParticleNR.size();i++)
        {
            Particle p=Particles[i];
            int ID=ParticleNR[i];
            names.push_back(getName("ParticlePOSX",ID));
            values.push_back(p.position[0]);
            names.push_back(getName("ParticlePOSY",ID));
            values.push_back(p.position[1]);
            names.push_back(getName("ParticlePOSZ",ID));
            values.push_back(p.position[2]);

            names.push_back(getName("ParticleVELX",ID));
            values.push_back(p.velocity[0]);

            names.push_back(getName("ParticleVELY",ID));
            values.push_back(p.velocity[1]);

            names.push_back(getName("ParticleVELZ",ID));
            values.push_back(p.velocity[2]);


            names.push_back(getName("ParticleFORCEX",ID));
            values.push_back(p.force[0]);
            names.push_back(getName("ParticleFORCEY",ID));
            values.push_back(p.force[1]);
            names.push_back(getName("ParticleFORCEZ",ID));
            values.push_back(p.force[2]);
            names.push_back(getName("ParticleFORCE",ID));
            values.push_back(p.forceMagnitude);

            names.push_back(getName("ParticleTEMPERATURE",ID));
            values.push_back(p.temperature);
        }
    }
}

