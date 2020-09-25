#include "ModuleFactory.h"
#include "GlobalParameters.h"
#include "Boundaries.h"
#include "IndividualParticles.h"
#include "LineStrain.h"
#include "ParticleFixes.h"
#include "ContactInformation.h"
#include "MeshCell.h"
#include "BondsInformation.h"
#include "MeshForce.h"
ModuleFactory::ModuleFactory()
{

}
AModule* ModuleFactory::createModule(std::string name)
{
    if(name.compare("GlobalParameters")==0)
    {
        return  new GlobalParameters();
    }
    if(name.compare("Boundaries")==0)
    {
        return  new Boundaries();
    }
    if(name.compare("IndividualParticles")==0)
    {
        return  new IndividualParticles();
    }
    if(name.compare("LineStrain")==0)
    {
        return  new LineStrain();
    }
    if(name.compare("ParticleFixes")==0)
    {
        return  new ParticleFixes();
    }
    if(name.compare("ContactInformation")==0)
    {
        return  new ContactInformation();
    }
    if(name.compare("MeshCell")==0)
    {
        return  new MeshCell();
    }
    if(name.compare("BondsInformation")==0)
    {
        return  new BondsInformation();
    }
    if(name.compare("MeshForce")==0)
    {
        return  new MeshForce();
    }



}
