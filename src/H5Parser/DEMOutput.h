#ifndef DEMOUTPUT_H
#define DEMOUTPUT_H
#include <string>
#include <vector>
#include "H5Parser/Point.h"
#include "ParsingParameters.h"
#include "PorocityInBox.h"
#include "IndividualParticles.h"
#include "InformationOnLine.h"
#include "SpecForceTIRE.h"
#include "MeshCell.h"
#include "ContactInformation.h"

class DEMOutput
{
public:
    DEMOutput(std::string filename,ParsingParameters *params);
    void ReadData();
public:
    ParsingParameters *params;
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






    PorocityInBox porocity;
    IndividualParticles individualParticles;
    InformationOnLine informationOnLine;
    SpecForceTIRE specForceTIRE;
    MeshCell meshCell;
    ContactInformation contactInformation;


};

#endif // DEMOUTPUT_H
