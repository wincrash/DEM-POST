#include "DEMOutput.h"
#include <iostream>
#include "H5Parser/hdf_wrapper.hpp"
#include <cmath>
#include <algorithm>


#define PADALINIMU_SKAICIUS 20


DEMOutput::DEMOutput(std::string filename, std::vector<int> ParticleNR)
{ 
    this->filename=filename;
    this->ParticleNR=ParticleNR;
}
void DEMOutput::ReadData()
{

    auto ReadIntArray=[](auto &gr,auto name,int N,int D)->std::vector<int>
    {
        std::vector<int> data(N*D,0);
        if(!gr.exists(name)) return data;
        auto dt = gr.open_dataset(name);
        hsize_t dim[2];
        dt.get_dataspace().get_dims(dim);
        dt.read(&data[0]);
        return data;
    };
    auto ReadDoubleArray=[](auto &gr,auto name,int N,int D)->std::vector<double>
    {
        std::vector<double> data(N*D,0);
        if(!gr.exists(name)) return data;
        auto dt = gr.open_dataset(name);
        hsize_t dim[2];
        dt.get_dataspace().get_dims(dim);
        dt.read(&data[0]);
        return data;
    };

    h5cpp::File file(filename, "r");
    auto gr = file.root();

    std::cout << "Reading "<< filename<< std::endl;
    STEP = gr.attrs().get<int>("STEP");
    TIME = gr.attrs().get<double>("TIME");
    if(gr.attrs().exists("TIME_TEMPERATURE"))
        THERMAL_TIME=gr.attrs().get<double>("TIME_TEMPERATURE");
    else
        THERMAL_TIME=0;

    auto dt = gr.open_dataset("POSITIONS");
    hsize_t dim[2];
    dt.get_dataspace().get_dims(dim);
    NumberOfPoints = dim[0];

    auto dt1 = gr.open_dataset("BOUNDARY_FORCE");
    hsize_t dim1[2];
    dt1.get_dataspace().get_dims(dim1);
    NumberOfBoundaries = dim1[0];


    std::vector<double> POSITIONS=ReadDoubleArray(gr,"POSITIONS",NumberOfPoints,4);
    std::vector<double> VELOCITY=ReadDoubleArray(gr,"VELOCITY",NumberOfPoints,4);
    std::vector<double> FORCE=ReadDoubleArray(gr,"FORCE",NumberOfPoints,4);
    std::vector<int> FIX=ReadIntArray(gr,"PARTICLE_FIX",NumberOfPoints,1);
    MAX_FIX=*std::max_element(FIX.begin(),FIX.end())+1;
    FORCE_FIX.resize(MAX_FIX,0);

    BOUNDARY_FORCE=ReadDoubleArray(gr,"BOUNDARY_FORCE",NumberOfBoundaries,1);

    std::vector<double> BOUNDARY_POINTS=ReadDoubleArray(gr,"BOUNDARY_POINTS",NumberOfBoundaries*3,4);


 std::vector<double>  TEMPERATURE=ReadDoubleArray(gr,"TEMPERATURE",NumberOfPoints,1);


    double bminx=1E+10;
    double bminy=1E+10;
    double bminz=1E+10;

    double bmaxx=-1E+10;
    double bmaxy=-1E+10;
    double bmaxz=-1E+10;
    for(int i=0;i<4*3;i++)
    {
        double bx=BOUNDARY_POINTS[i*4+0];
        double by=BOUNDARY_POINTS[i*4+1];
        double bz=BOUNDARY_POINTS[i*4+2];
        if(bx<bminx) bminx=bx;
        if(by<bminy) bminy=by;
        if(bz<bminz) bminz=bz;

        if(bx>bmaxx) bmaxx=bx;
        if(by>bmaxy) bmaxy=by;
        if(bz>bmaxz) bmaxz=bz;
    }

    BoundaryLengthx=bmaxx-bminx;
    BoundaryLengthy=bmaxy-bminy;
    BoundaryLengthz=bmaxz-bminz;

    particles.reserve(NumberOfPoints);
    minx=1E+10;
    miny=1E+10;
    minz=1E+10;

    maxx=-1E+10;
    maxy=-1E+10;
    maxz=-1E+10;

    for(int i=0;i<NumberOfPoints;i++)
    {
        Point p;
        p.x=POSITIONS[i*4+0];
        p.y=POSITIONS[i*4+1];
        p.z=POSITIONS[i*4+2];
        p.r=POSITIONS[i*4+3];
        p.fix=FIX[i];

        p.fx=FORCE[i*4+0];
        p.fy=FORCE[i*4+1];
        p.fz=FORCE[i*4+2];
        p.force=std::sqrt(p.fx*p.fx+p.fy*p.fy+p.fz*p.fz);
        FORCE_FIX[p.fix]=FORCE_FIX[p.fix]+p.force;
        p.temperature=TEMPERATURE[i];
        particles.push_back(p);

        if(p.x<minx) minx=p.x;
        if(p.y<miny) miny=p.y;
        if(p.z<minz) minz=p.z;

        if(p.x>maxx) maxx=p.x;
        if(p.y>maxy) maxy=p.y;
        if(p.z>maxz) maxz=p.z;



    }

    lengthx=maxx-minx;
    lengthy=maxy-miny;
    lengthz=maxz-minz;

    CenterLineX_POS.resize(PADALINIMU_SKAICIUS,0);
    CenterLineX_TEMP.resize(PADALINIMU_SKAICIUS,0);
    double DeltaX=lengthx/(PADALINIMU_SKAICIUS-1);
    double RADIUS_MAT=DeltaX/2;
    for(int i=0;i<PADALINIMU_SKAICIUS;i++)
    {
        CenterLineX_POS[i]=minx+i*DeltaX;

        int patekoDaleliu=0;

        for(Point p:particles)
        {
            double ilgis=std::sqrt((p.x-CenterLineX_POS[i])*(p.x-CenterLineX_POS[i])+p.y*p.y+p.z*p.z);
            if(ilgis<=RADIUS_MAT)
            {
                patekoDaleliu++;
                CenterLineX_TEMP[i]=CenterLineX_TEMP[i]+p.temperature;
            }


        }
        CenterLineX_TEMP[i]=CenterLineX_TEMP[i]/patekoDaleliu;
     //   std::cout<<"Padalinimas "<<CenterLineX_POS[i]<<" pakliuvo "<<patekoDaleliu<<"\n";
    }


    for(int i=0;i<ParticleNR.size();i++)
    {
        int id=ParticleNR[i];
        ParticlePOSX.push_back(POSITIONS[id*4+0]);
        ParticlePOSY.push_back(POSITIONS[id*4+1]);
        ParticlePOSZ.push_back(POSITIONS[id*4+2]);
        ParticleVELX.push_back(VELOCITY[id*4+0]);
        ParticleVELY.push_back(VELOCITY[id*4+1]);
        ParticleVELZ.push_back(VELOCITY[id*4+2]);
        ParticleFORCEX.push_back(FORCE[id*4+0]);
        ParticleFORCEY.push_back(FORCE[id*4+1]);
        ParticleFORCEZ.push_back(FORCE[id*4+2]);
        ParticleTEMPERATURE.push_back(TEMPERATURE[id]);

    }

}
