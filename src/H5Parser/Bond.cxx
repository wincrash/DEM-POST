#include "Bond.h"
#include <algorithm>
#include <iostream>

Bond::Bond(int id1, int id2, int TYPE, int STATE)
{
    this->ID1=id1;
    this->ID2=id2;
    this->TYPE=TYPE;
    this->STATE=STATE;
    if(id1>id2) std::swap(this->ID1,this->ID2);
}
