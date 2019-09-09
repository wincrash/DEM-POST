#include "DEMOutput.h"
#include <iostream>
#include "H5Parser/hdf_wrapper.hpp"
#include <cmath>
#include <algorithm>
DEMOutput::DEMOutput(std::string filename)
{ 
    this->filename=filename;
}
void DEMOutput::ReadData()
{

    auto ReadIntArray=[](auto &gr,auto name,int N,int D)->std::vector<int>
    {
        std::vector<int> data(N*D,0);
        auto dt = gr.open_dataset(name);
        hsize_t dim[2];
        dt.get_dataspace().get_dims(dim);
        dt.read(&data[0]);
        return data;
    };
    auto ReadDoubleArray=[](auto &gr,auto name,int N,int D)->std::vector<double>
    {
        std::vector<double> data(N*D,0);
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

    auto dt = gr.open_dataset("POSITIONS");
    hsize_t dim[2];
    dt.get_dataspace().get_dims(dim);
    NumberOfPoints = dim[0];
    std::vector<double> POSITIONS=ReadDoubleArray(gr,"POSITIONS",NumberOfPoints,4);
    std::vector<double> FORCE=ReadDoubleArray(gr,"FORCE",NumberOfPoints,4);
    std::vector<int> FIX=ReadIntArray(gr,"PARTICLE_FIX",NumberOfPoints,1);
    MAX_FIX=*std::max_element(FIX.begin(),FIX.end())+1;
    FORCE_FIX.resize(MAX_FIX,0);

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

        p.fx=POSITIONS[i*4+0];
        p.fy=POSITIONS[i*4+1];
        p.fz=POSITIONS[i*4+2];
        p.force=std::sqrt(p.fx*p.fx+p.fy*p.fy+p.fz*p.fz);
        FORCE_FIX[p.fix]=FORCE_FIX[p.fix]+p.force;
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

}
