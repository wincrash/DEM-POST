#ifndef PARSINGPARAMETERS_H
#define PARSINGPARAMETERS_H
#include <string>
#include <vector>
#include "utils/cxxopts.hpp"
class ParsingParameters
{
public:
    ParsingParameters(int argc, char *argv[]);
    cxxopts::ParseResult getResults();
    int argc;
    char** argv;

};

#endif // PARSINGPARAMETERS_H
