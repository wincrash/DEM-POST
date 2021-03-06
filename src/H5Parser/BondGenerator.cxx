#include "BondGenerator.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
BondGenerator::BondGenerator()
{

}


void BondGenerator::CreateBonds(TASKAI &points, BondsType &bonds, double DELTA)
{
    double RMin=0;
    double RMax=0;
    GetMinMaxRadius(points,RMin,RMax);
    double bounds[6];
    bounds[0]=100000000000;
    bounds[1]=-100000000000;
    bounds[2]=100000000000;
    bounds[3]=-100000000000;
    bounds[4]=100000000000;
    bounds[5]=-100000000000;

    std::for_each(points.begin(), points.end(), [&bounds](Point &p)
    {
        double x=p.x;
        double y=p.y;
        double z=p.z;
        double r=p.r;
        if((x-r)<bounds[0]) bounds[0]=x-r;
        if((y-r)<bounds[2]) bounds[2]=y-r;
        if((z-r)<bounds[4]) bounds[4]=z-r;

        if((x+r)>bounds[1]) bounds[1]=x+r;
        if((y+r)>bounds[3]) bounds[3]=y+r;
        if((z+r)>bounds[5]) bounds[5]=z+r;
    });

    double CELL_SIZE=RMax*2.2;
    size_t NX=std::ceil(((bounds[1]-bounds[0])/CELL_SIZE));
    size_t NY=std::ceil(((bounds[3]-bounds[2])/CELL_SIZE));
    size_t NZ=std::ceil(((bounds[5]-bounds[4])/CELL_SIZE));
    std::cout<<NX<<" "<<NY<<" "<<NZ<<"\n";
    std::vector<std::vector<size_t>> indexes(NX*NY*NZ);
    for(size_t i=0;i<NX*NY*NZ;i++)
    {
        std::vector<size_t> temp(0);
        indexes[i]=temp;
    }
    std::for_each(points.begin(),points.end(),[CELL_SIZE,NX,NY,NZ,&indexes,n=0,&bounds](Point &p)mutable{
        size_t x=std::floor((p.x-bounds[0])/CELL_SIZE);
        size_t y=std::floor((p.y-bounds[2])/CELL_SIZE);
        size_t z=std::floor((p.z-bounds[4])/CELL_SIZE);
        size_t id= x + y * NX + z * NX * NY;
        indexes[id].push_back(n);
        //indexes[id][0]++;
        n++;
    });

    std::map<std::pair<int,int>,int> links;
    std::for_each(points.begin(),points.end(),[CELL_SIZE,NX,NY,NZ,&indexes,n=0,&points,DELTA,&bonds,&bounds,&links](Point &p)mutable{
        size_t x=std::floor((p.x-bounds[0])/CELL_SIZE)-1;
        size_t y=std::floor((p.y-bounds[2])/CELL_SIZE)-1;
        size_t z=std::floor((p.z-bounds[4])/CELL_SIZE)-1;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                {
                    int ii=x+i;
                    int jj=y+j;
                    int kk=z+k;
                    if(ii<0 || jj<0 || kk<0 || ii>=NX|| jj>=NY|| kk>=NZ) continue;
                    size_t id= ii + jj * NX + kk * NX * NY;
                    size_t kiek=indexes[id].size();
                    for(size_t b=0;b<kiek;b++)
                    {

                        size_t pid=indexes[id][b];
                        if(pid==n) continue;

                        Point pp=points[pid];
                        double atstumas= GetDistance(p,pp)-p.r-pp.r;
                        if(atstumas<DELTA)
                        {
                            std::pair<int,int> l;
                            l.first=pid;
                            l.second=n;
//if(l.first>l.second) std::swap(l.first,l.second);
                            if (l.first > l.second) {
                                int temp = l.first;
                                l.first = l.second;
                                l.second = temp;
                            }
                            if(links.find(l)==links.end())
                            {
                                links[l]=1;
                                Bond bondas;
                                bondas.ID1=n;
                                bondas.ID2=pid;
                                bondas.TYPE=0;
                                bondas.STATE=0;
                                bonds.push_back(bondas);
                            }
                        }
                    }
                }

        n++;

    });
}


