#ifndef DEMOUTPUT_H
#define DEMOUTPUT_H
#include <string>
#include <vector>
#include "H5Parser/Point.h"


typedef  std::vector<Point> TASKAI;

class DEMOutput
{
public:
    DEMOutput(std::string filename,std::vector<int> ParticleNR);
    void ReadData();
public:
    std::string filename;
    TASKAI particles;
    int NumberOfPoints;
    int NumberOfBoundaries;
    double TIME;
    double THERMAL_TIME;
    int STEP;
    int MAX_FIX;

    double minx;
    double miny;
    double minz;

    double maxx;
    double maxy;
    double maxz;

    double lengthx;
    double lengthy;
    double lengthz;
    std::vector<double> FORCE_FIX;
    std::vector<double> BOUNDARY_FORCE;

    double BoundaryLengthx;
    double BoundaryLengthy;
    double BoundaryLengthz;


    std::vector<double> CenterLineX_POS;
    std::vector<double> CenterLineX_TEMP;


    std::vector<int> ParticleNR;
    std::vector<double> ParticlePOSX;
    std::vector<double> ParticlePOSY;
    std::vector<double> ParticlePOSZ;
    std::vector<double> ParticleVELX;
    std::vector<double> ParticleVELY;
    std::vector<double> ParticleVELZ;
    std::vector<double> ParticleFORCEX;
    std::vector<double> ParticleFORCEY;
    std::vector<double> ParticleFORCEZ;
    std::vector<double> ParticleTEMPERATURE;


};

#endif // DEMOUTPUT_H
