#include "ParsingParameters.h"
#include "utils/cxxopts.hpp"

ParsingParameters::ParsingParameters(int argc, char *argv[])
{
    this->argc=argc;
    this->argv=argv;
}
char **copy_argv(int argc, char *argv[]) {
  // calculate the contiguous argv buffer size
  int length=0;
  size_t ptr_args = argc + 1;
  for (int i = 0; i < argc; i++)
  {
    length += (strlen(argv[i]) + 1);
  }
  char** new_argv = (char**)malloc((ptr_args) * sizeof(char*) + length);
  // copy argv into the contiguous buffer
  length = 0;
  for (int i = 0; i < argc; i++)
  {
    new_argv[i] = &(((char*)new_argv)[(ptr_args * sizeof(char*)) + length]);
    strcpy(new_argv[i], argv[i]);
    length += (strlen(argv[i]) + 1);
  }
  // insert NULL terminating ptr at the end of the ptr array
  new_argv[ptr_args-1] = NULL;
  return (new_argv);
}
cxxopts::ParseResult ParsingParameters::getResults()
{
    try{
        cxxopts::Options options(this->argv[0], " - DEM to CSV parser");
        options
                .positional_help("[optional args]")
                .show_positional_help();
        options .allow_unrecognised_options()
                .add_options()
                ("o,output", "CSV file name", cxxopts::value<std::string>()->default_value("CSV.csv"))
                ("p,particles", "A list of particles IDS seperated with ,", cxxopts::value<std::vector<int>>())
                ("m,meshcell", "A list of mesh cell to track seperated with ,", cxxopts::value<std::vector<int>>())
                ("spec-force","Calculate forces of problem TIRE")
                ("contact-information","Calculate contact information, coordination number and overalp")

                ("help", "Print help");
        options.add_options("Porocity")
                ("porocity","Calculate porocity in box")
                ("resolution", "Resolution of the sphere", cxxopts::value<int>()->default_value("16"))
                ("bounds", "Box bounds, minx,maxx,miny,maxy,minz,maxz", cxxopts::value<std::vector<double>>());
        options.add_options("LineStrain")
                ("linestrain","Calculate line strain")
                ("linestrain-point1", "Line point 1, x,y,z seperated with ,", cxxopts::value<std::vector<double>>())
                ("linestrain-point2", "Line point 2, x,y,z seperated with ,", cxxopts::value<std::vector<double>>())
                ("linestrain-count", "Number of segments", cxxopts::value<int>()->default_value("5"))
                ("linestrain-radius", "Radius of segments", cxxopts::value<double>()->default_value("0.01"));

        options.add_options("BondsInformation")
                ("bonds-information","Calculate bonds information");


        int bargc=argc;
        auto bargv=copy_argv(argc,argv);
        cxxopts::ParseResult result = options.parse(this->argc, this->argv);
        argc=bargc;
        argv=bargv;
        if (result.count("help"))
        {
            std::cout << options.help({"", "Porocity","LineStrain","BondsInformation"}) << std::endl;
            exit(0);
        }

        return result;
    }

    catch (const cxxopts::OptionException& e)
    {
        std::cout << "error parsing options: " << e.what() << std::endl;
        exit(1);
    }

}
