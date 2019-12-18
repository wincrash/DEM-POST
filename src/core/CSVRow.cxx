#include "CSVRow.h"
#include <sstream>
#include <iostream>
#include "modules/ModuleFactory.h"

CSVRow::CSVRow()
{

}

void CSVRow::Calculate(ParsingParameters *params, Dataset &zero, Dataset &current)
{
    ModuleFactory factory;
    modules.push_back(factory.createModule("GlobalParameters"));
    modules.push_back(factory.createModule("Boundaries"));
    modules.push_back(factory.createModule("IndividualParticles"));
    modules.push_back(factory.createModule("LineStrain"));
    modules.push_back(factory.createModule("ParticleFixes"));
    modules.push_back(factory.createModule("ContactInformation"));
    modules.push_back(factory.createModule("MeshCell"));
    modules.push_back(factory.createModule("BondsInformation"));






    for(auto &m:modules)
    {
        m->Calculate(params,zero,current);
        m->GetNamesAndValues(names,values);
    }
}

std::string CSVRow::getHeader()
{
    std::stringstream str;
    for(std::string val:names)
        str<<val<<DELIMETER;
    str<<"0";
    return str.str();
}

std::string CSVRow::getValues()
{
    std::stringstream str;
    for(double val:values)
        str<<val<<DELIMETER;
    str<<"0";
    return str.str();
}
