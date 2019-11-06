#ifndef BONDGENERATOR_H
#define BONDGENERATOR_H
#include "Bond.h"
#include "Point.h"


class BondGenerator
{
public:
    BondGenerator();
    void CreateBonds(TASKAI &points,BondsType &bonds,double DELTA=1E-6);
 };

#endif // BONDGENERATOR_H
