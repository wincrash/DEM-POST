#ifndef BOND_H
#define BOND_H
#include <vector>

class Bond
{
public:
    Bond(int id1=0,int id2=0,int TYPE=0,int STATE=0);
    int ID1;
    int ID2;
    int TYPE;
    int STATE;
};
typedef std::vector<Bond> BondsType;

#endif // BOND_H
