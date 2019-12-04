#ifndef CSVROW_H
#define CSVROW_H

#include <vector>
#include <string>

#define DELIMETER ";"
#include "Dataset.h"
#include "AModule.h"
#include "ParsingParameters.h"
class CSVRow
{
public:
    CSVRow();
    void Calculate(ParsingParameters*params,Dataset&zero,Dataset&current);
    std::vector<std::string> names;
    std::vector<double> values;
    std::string getHeader();
    std::string getValues();
    std::vector<AModule*> modules;
};

#endif // CSVROW_H
