#ifndef MODULEFACTORY_H
#define MODULEFACTORY_H
#include "core/AModule.h"

class ModuleFactory
{
public:
    ModuleFactory();
    AModule* createModule(std::string name);
};

#endif // MODULEFACTORY_H
