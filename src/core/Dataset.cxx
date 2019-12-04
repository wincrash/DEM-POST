#include "Dataset.h"
#include <iostream>
#include "H5Parser/hdf_wrapper.hpp"
#include <cmath>
#include <algorithm>
Dataset::Dataset(std::string filename)
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
    {
        auto dt = gr.open_dataset("POSITIONS");
        hsize_t dim[2];
        dt.get_dataspace().get_dims(dim);
        NUMBER_OF_PARTICLES = dim[0];
    }

    std::vector<double> POSITIONS=ReadDoubleArray(gr,"POSITIONS",NUMBER_OF_PARTICLES,4);
    std::vector<double> VELOCITY=ReadDoubleArray(gr,"VELOCITY",NUMBER_OF_PARTICLES,4);
    std::vector<double> FORCE=ReadDoubleArray(gr,"FORCE",NUMBER_OF_PARTICLES,4);
    std::vector<int> FIX=ReadIntArray(gr,"PARTICLE_FIX",NUMBER_OF_PARTICLES,1);
    std::vector<int> MATERIAL=ReadIntArray(gr,"PARTICLE_MATERIAL",NUMBER_OF_PARTICLES,1);
    std::vector<double>  TEMPERATURE=ReadDoubleArray(gr,"TEMPERATURE",NUMBER_OF_PARTICLES,1);

    {
    auto dt1 = gr.open_dataset("BOUNDARY_FORCE");
    hsize_t dim1[2];
    dt1.get_dataspace().get_dims(dim1);
    NUMBER_OF_BOUNDARIES = dim1[0];
    }

    boundaries.FORCE=ReadDoubleArray(gr,"BOUNDARY_FORCE",NUMBER_OF_BOUNDARIES,1);
    boundaries.POINTS=ReadDoubleArray(gr,"BOUNDARY_POINTS",NUMBER_OF_BOUNDARIES*3,4);
    boundaries.NUMBER_OF_BOUNDARIES=NUMBER_OF_BOUNDARIES;



    particles.resize(NUMBER_OF_PARTICLES);
    for(int i=0;i<NUMBER_OF_PARTICLES;i++)
    {
        Particle p;
        p.position[0]=POSITIONS[i*4+0];
        p.position[1]=POSITIONS[i*4+1];
        p.position[2]=POSITIONS[i*4+2];
        p.radius=POSITIONS[i*4+3];

        p.velocity[0]=VELOCITY[i*4+0];
        p.velocity[1]=VELOCITY[i*4+1];
        p.velocity[2]=VELOCITY[i*4+2];
        p.mass=VELOCITY[i*4+3];


        p.force[0]=FORCE[i*4+0];
        p.force[1]=FORCE[i*4+1];
        p.force[2]=FORCE[i*4+2];
        p.forceMagnitude=CalcMagnitude(p.force);
        p.temperature=TEMPERATURE[i];
        p.fix=FIX[i];
        p.mat_id=MATERIAL[i];
        particles[i]=p;
    }


}
