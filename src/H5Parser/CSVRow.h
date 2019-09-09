#ifndef CSVROW_H
#define CSVROW_H
#include "H5Parser/DEMOutput.h"
#include <vector>
#include <string>

#define DELIMETER ";"

class CSVRow
{
public:
    CSVRow();
    void Calculate(DEMOutput&current,DEMOutput&zero);
    std::vector<std::string> names;
    std::vector<double> values;
    std::string getHeader();
    std::string getValues();

};

#endif // CSVROW_H
