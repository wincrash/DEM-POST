#include "BondsInformation.h"


BondsInformation::BondsInformation()
{

}
void BondsInformation::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{

    auto result= params->getResults();
    if(result.count("bonds-information"))
    {
        calculate=true;
        h5cpp::File file(current.filename, "r");
        auto gr = file.root();

        {
            auto dt = gr.open_dataset("BOND_STATE");
            hsize_t dim[2];
            dt.get_dataspace().get_dims(dim);
            this->BONDS_TOTAL = dim[0];
        }
        std::vector<int> BOND_STATE=ReadIntArray(gr,"BOND_STATE",BONDS_TOTAL,1);
        std::vector<double> BOND_FORCE_NORMAL_SIGMA=ReadDoubleArray(gr,"BOND_FORCE_NORMAL_SIGMA",BONDS_TOTAL,1);
        std::vector<double> BOND_FORCE_TANGENTIAL_SIGMA=ReadDoubleArray(gr,"BOND_FORCE_TANGENTIAL_SIGMA",BONDS_TOTAL,1);
        file.close();
        for (auto &x:BOND_STATE)
        {
            if(x!=0)//broken
            {
                this->BONDS_BROKEN_ALL++;
            }
            if(x==3)//BROKEN_TANGENTIAL
            {
                this->BONDS_BROKEN_SHEAR++;
            }
            if(x==1)//BROKEN_NORMAL_TENSION
            {
                this->BONDS_BROKEN_NORMAL++;
            }
        }
        this->BONDS_MAX_NORMAL_SIGMA=*std::max_element(std::begin(BOND_FORCE_NORMAL_SIGMA), std::end(BOND_FORCE_NORMAL_SIGMA));
        this->BONDS_MAX_TANGENTIAL_SIGMA=*std::max_element(std::begin(BOND_FORCE_TANGENTIAL_SIGMA), std::end(BOND_FORCE_TANGENTIAL_SIGMA));
    }

}

void BondsInformation::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        names.push_back("BONDS_BROKEN_NORMAL");
        values.push_back(BONDS_BROKEN_NORMAL);
        names.push_back("BONDS_BROKEN_SHEAR");
        values.push_back(BONDS_BROKEN_SHEAR);
        names.push_back("BONDS_BROKEN_ALL");
        values.push_back(BONDS_BROKEN_ALL);
        names.push_back("BONDS_TOTAL");
        values.push_back(BONDS_TOTAL);
        names.push_back("BONDS_MAX_NORMAL_SIGMA");
        values.push_back(BONDS_MAX_NORMAL_SIGMA);
        names.push_back("BONDS_MAX_TANGENTIAL_SIGMA");
        values.push_back(BONDS_MAX_TANGENTIAL_SIGMA);
    }
}

