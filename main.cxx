#include <iostream>
#include <vector>
#include <experimental/filesystem>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;
namespace fs = std::experimental::filesystem;


#include "H5Parser/DEMOutput.h"
#include "H5Parser/CSVRow.h"


int main(int argc,char *argv[])
{
    std::vector<int> NR;
    if(argc>1)
    {
        for(int i=1;i<argc;i++)
        NR.push_back(atoi(argv[i]));
    }
    std::vector<std::string> filenames;
    for(auto& p: fs::directory_iterator(fs::path("./data")))
    {
        if (p.path().string().find(".h5") != std::string::npos) {

            filenames.push_back(p.path().string());
        }
    }
    std::sort(filenames.begin(),filenames.end());
    filenames.pop_back();//removing last file
    std::vector<DEMOutput> datasets;
    for( std::string x:filenames)
        datasets.push_back(DEMOutput(x,NR));
    for (DEMOutput &x:datasets)
        x.ReadData();


    std::vector<CSVRow> csvrows;

    for (DEMOutput &x:datasets)
    {
        CSVRow row;
        row.Calculate(x,datasets[0]);
        csvrows.push_back(row);
    }

    ofstream csvFile;
    csvFile.open ("CSV.csv");
    csvFile<<csvrows[0].getHeader()<<"\n";
    for(CSVRow &row:csvrows)
        csvFile<<row.getValues()<<"\n";
    csvFile.close();

    return 0;
}
