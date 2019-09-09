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
    double TIME;
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
};

#endif // DEMOUTPUT_H
