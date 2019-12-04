#include "Boundaries.h"

Boundaries::Boundaries()
{

}
void Boundaries::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{
    calculate=true;
    double boundsZero[6];
    double boundsCurrent[6];
    GetBoundsWithR(zero.particles,boundsZero);
    GetBoundsWithR(current.particles,boundsCurrent);
    PARTICLES_BOUNDARY_MIN_X=boundsCurrent[0];
    PARTICLES_BOUNDARY_MAX_X=boundsCurrent[1];
    PARTICLES_BOUNDARY_MIN_Y=boundsCurrent[2];
    PARTICLES_BOUNDARY_MAX_Y=boundsCurrent[3];
    PARTICLES_BOUNDARY_MIN_Z=boundsCurrent[4];
    PARTICLES_BOUNDARY_MAX_Z=boundsCurrent[5];

    PARTICLES_BOUNDARY_LENGTH_X=boundsCurrent[1]-boundsCurrent[0];
    PARTICLES_BOUNDARY_LENGTH_Y=boundsCurrent[3]-boundsCurrent[2];
    PARTICLES_BOUNDARY_LENGTH_Z=boundsCurrent[5]-boundsCurrent[4];

    double ZERO_PARTICLES_BOUNDARY_LENGTH_X=boundsZero[1]-boundsZero[0];
    double ZERO_PARTICLES_BOUNDARY_LENGTH_Y=boundsZero[3]-boundsZero[2];
    double ZERO_PARTICLES_BOUNDARY_LENGTH_Z=boundsZero[5]-boundsZero[4];

    PARTICLES_BOUNDARY_STRAIN_X=fabs(ZERO_PARTICLES_BOUNDARY_LENGTH_X-PARTICLES_BOUNDARY_LENGTH_X)/ZERO_PARTICLES_BOUNDARY_LENGTH_X;
    PARTICLES_BOUNDARY_STRAIN_Y=fabs(ZERO_PARTICLES_BOUNDARY_LENGTH_Y-PARTICLES_BOUNDARY_LENGTH_Y)/ZERO_PARTICLES_BOUNDARY_LENGTH_Y;
    PARTICLES_BOUNDARY_STRAIN_Z=fabs(ZERO_PARTICLES_BOUNDARY_LENGTH_Z-PARTICLES_BOUNDARY_LENGTH_Z)/ZERO_PARTICLES_BOUNDARY_LENGTH_Z;


}

void Boundaries::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        names.push_back("PARTICLES_BOUNDARY_MIN_X");
        values.push_back(PARTICLES_BOUNDARY_MIN_X);
        names.push_back("PARTICLES_BOUNDARY_MIN_Y");
        values.push_back(PARTICLES_BOUNDARY_MIN_Y);
        names.push_back("PARTICLES_BOUNDARY_MIN_Z");
        values.push_back(PARTICLES_BOUNDARY_MIN_Z);

        names.push_back("PARTICLES_BOUNDARY_MAX_X");
        values.push_back(PARTICLES_BOUNDARY_MAX_X);
        names.push_back("PARTICLES_BOUNDARY_MAX_Y");
        values.push_back(PARTICLES_BOUNDARY_MAX_Y);
        names.push_back("PARTICLES_BOUNDARY_MAX_Z");
        values.push_back(PARTICLES_BOUNDARY_MAX_Z);



        names.push_back("PARTICLES_BOUNDARY_LENGTH_X");
        values.push_back(PARTICLES_BOUNDARY_LENGTH_X);
        names.push_back("PARTICLES_BOUNDARY_LENGTH_Y");
        values.push_back(PARTICLES_BOUNDARY_LENGTH_Y);
        names.push_back("PARTICLES_BOUNDARY_LENGTH_Z");
        values.push_back(PARTICLES_BOUNDARY_LENGTH_Z);


        names.push_back("PARTICLES_BOUNDARY_STRAIN_X");
        values.push_back(PARTICLES_BOUNDARY_STRAIN_X);
        names.push_back("PARTICLES_BOUNDARY_STRAIN_Y");
        values.push_back(PARTICLES_BOUNDARY_STRAIN_Y);
        names.push_back("PARTICLES_BOUNDARY_STRAIN_Z");
        values.push_back(PARTICLES_BOUNDARY_STRAIN_Z);

    }
}

