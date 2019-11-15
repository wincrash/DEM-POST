#include "ContactInformation.h"
#include "BondGenerator.h"
#include <algorithm>
#include <numeric>
ContactInformation::ContactInformation()
{

}
void ContactInformation::Compute(TASKAI &points, ParsingParameters *params)
{
    auto result=params->getResults();
    if(result.count("contact-information"))
    {
        calculate=true;
        BondsType bonds;

        BondGenerator bondsGen;
        bondsGen.CreateBonds(points,bonds);
        avgOverlap=0;
        maxOverlap=0;
        int N=0;
        std::vector<int> contactCount;
        contactCount.resize(points.size(),0);
        for(auto b:bonds)
        {
            int id1=b.ID1;
            int id2=b.ID2;
            auto p1=points[id1];
            auto p2=points[id2];
            double overlap=p1.r+p2.r-GetDistance(p1,p2);
            if(overlap>0)
            {
                N++;
                avgOverlap=avgOverlap+overlap;
                if(maxOverlap<overlap) maxOverlap=overlap;
                contactCount[id1]++;
                contactCount[id2]++;
            }
        }
        ContactCount=N;
        avgOverlap=avgOverlap/N;
        coordinationNumber=std::accumulate(contactCount.begin(),contactCount.end(),0)/contactCount.size();
    }
}
void ContactInformation::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        names.push_back("COORDIANTION_NUMBER");
        values.push_back(coordinationNumber);
        names.push_back("AVERAGE_OVERLAP");
        values.push_back(avgOverlap);
        names.push_back("MAX_OVERLAP");
        values.push_back(maxOverlap);
        names.push_back("CONTACT_COUNT");
        values.push_back(ContactCount);

    }
}


