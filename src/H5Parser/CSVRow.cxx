#include "CSVRow.h"
#include <sstream>
#include <iostream>

CSVRow::CSVRow()
{

}

void CSVRow::Calculate(DEMOutput&current,DEMOutput&zero)
{
    auto getName=[](auto a,auto b)->std::string
    {
        std::stringstream str;
        str<<a<<"_"<<b;
        return str.str();
    };
    names.push_back("STEP");
    values.push_back(current.STEP);
    names.push_back("TIME");
    values.push_back(current.TIME);
    names.push_back("THERMAL_TIME");
    values.push_back(current.THERMAL_TIME);


    names.push_back("MAX_FIX");
    values.push_back(current.MAX_FIX);

    names.push_back("SIZE_X");
    values.push_back(zero.lengthx);
    names.push_back("SIZE_Y");
    values.push_back(zero.lengthy);
    names.push_back("SIZE_Z");
    values.push_back(zero.lengthz);

    names.push_back("DISPLACEMENT_X");
    values.push_back(current.lengthx-zero.lengthx);
    names.push_back("DISPLACEMENT_Y");
    values.push_back(current.lengthy-zero.lengthy);
    names.push_back("DISPLACEMENT_Z");
    values.push_back(current.lengthz-zero.lengthz);

    names.push_back("STRAIN_X");
    values.push_back((current.lengthx-zero.lengthx)/zero.lengthx);
    names.push_back("STRAIN_Y");
    values.push_back((current.lengthy-zero.lengthy)/zero.lengthy);
    names.push_back("STRAIN_Z");
    values.push_back((current.lengthz-zero.lengthz)/zero.lengthz);


    names.push_back("BOUNDARY_DISPLACEMENT_X");
    values.push_back(current.BoundaryLengthx-zero.BoundaryLengthx);
    names.push_back("BOUNDARY_DISPLACEMENT_Y");
    values.push_back(current.BoundaryLengthy-zero.BoundaryLengthy);
    names.push_back("BOUNDARY_DISPLACEMENT_Z");
    values.push_back(current.BoundaryLengthz-zero.BoundaryLengthz);

    names.push_back("BOUNDARY_STRAIN_X");
    values.push_back((current.BoundaryLengthx-zero.BoundaryLengthx)/zero.BoundaryLengthx);
    names.push_back("BOUNDARY_STRAIN_Y");
    values.push_back((current.BoundaryLengthy-zero.BoundaryLengthy)/zero.BoundaryLengthy);
    names.push_back("BOUNDARY_STRAIN_Z");
    values.push_back((current.BoundaryLengthz-zero.BoundaryLengthz)/zero.BoundaryLengthz);



    for(int i=0;i<current.MAX_FIX;i++)
    {
        names.push_back(getName("FORCE_FIX",i));
        values.push_back(current.FORCE_FIX[i]);
    }
    for(int i=0;i<current.NumberOfBoundaries;i++)
    {
        names.push_back(getName("BOUNDARIES_FORCE",i));
        values.push_back(current.BOUNDARY_FORCE[i]);
    }

    names.push_back("CenterLineX_COUNT");
    values.push_back(current.CenterLineX_POS.size());
    for(int i=0;i<current.CenterLineX_POS.size();i++)
    {
        names.push_back(getName("CenterLineX_POS",i));
        values.push_back(current.CenterLineX_POS[i]);
        names.push_back(getName("CenterLineX_TEMP",i));
        values.push_back(current.CenterLineX_TEMP[i]);
      //  std::cout<<i<<" POS "<<current.CenterLineX_POS[i]<<"  temp "<<current.CenterLineX_TEMP[i]<<"\n";
    }

    for(int i=0;i<current.ParticleNR.size();i++)
    {
        int ID=current.ParticleNR[i];
        names.push_back(getName("ParticlePOSX",i));
        values.push_back(current.ParticlePOSX[i]);
        names.push_back(getName("ParticlePOSY",i));
        values.push_back(current.ParticlePOSY[i]);
        names.push_back(getName("ParticlePOSZ",i));
        values.push_back(current.ParticlePOSZ[i]);

        names.push_back(getName("ParticleVELX",i));
        values.push_back(current.ParticleVELX[i]);

        names.push_back(getName("ParticleVELY",i));
        values.push_back(current.ParticleVELY[i]);

        names.push_back(getName("ParticleVELZ",i));
        values.push_back(current.ParticleVELZ[i]);


        names.push_back(getName("ParticleFORCEX",i));
        values.push_back(current.ParticleFORCEX[i]);
        names.push_back(getName("ParticleFORCEY",i));
        values.push_back(current.ParticleFORCEY[i]);
        names.push_back(getName("ParticleFORCEZ",i));
        values.push_back(current.ParticleFORCEZ[i]);
        names.push_back(getName("ParticleTEMPERATURE",i));
        values.push_back(current.ParticleTEMPERATURE[i]);

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
