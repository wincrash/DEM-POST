#ifndef DEMOUTPUT_H
#define DEMOUTPUT_H
#include <string>
#include <vector>
#include "H5Parser/Point.h"


typedef  std::vector<Point> TASKAI;

class DEMOutput
{
public:
    DEMOutput(std::string filename);
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


};

#endif // DEMOUTPUT_H
