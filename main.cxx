#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
namespace fs = std::experimental::filesystem;

#include "core/Dataset.h"
#include "core/CSVRow.h"
#include "core/ParsingParameters.h"


int main(int argc,char *argv[])
{
    ParsingParameters *parameters=new ParsingParameters(argc,argv);
    auto result=parameters->getResults();

    std::vector<int> NR;

    std::vector<std::string> filenames;
    for(auto& p: fs::directory_iterator(fs::path("./data")))
    {
        if (p.path().string().find(".h5") != std::string::npos) {

            filenames.push_back(p.path().string());
        }
    }
    std::sort(filenames.begin(),filenames.end());
    filenames.pop_back();//removing last file

    Dataset zero(filenames[0]);
    std::vector<CSVRow> csvrows;
    for (auto &filename:filenames)
    {
        Dataset current(filename);
        CSVRow row;
        row.Calculate(parameters,zero,current);
        csvrows.push_back(row);
    }

    ofstream csvFile;
    csvFile.open (result["output"].as<std::string>());
    csvFile<<csvrows[0].getHeader()<<"\n";
    for(CSVRow &row:csvrows)
        csvFile<<row.getValues()<<"\n";
    csvFile.close();

    return 0;
}
