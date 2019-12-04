#include "LineStrain.h"

LineStrain::LineStrain()
{

}
void LineStrain::Calculate(ParsingParameters*params,Dataset &zero,Dataset&current)
{
    auto result= params->getResults();
    if(result.count("linestrain"))
    {
        calculate=true;
        std::vector<double> p1=result["linestrain-point1"].as<std::vector<double>>();
        std::vector<double> p2=result["linestrain-point2"].as<std::vector<double>>();
        size_t count=result["linestrain-count"].as<int>();
        double radius=result["linestrain-radius"].as<double>();
        double deltaX=p2[0]-p1[0];
        double deltaY=p2[1]-p1[1];
        double deltaZ=p2[2]-p1[2];
        deltaX=deltaX/(count-1);
        deltaY=deltaY/(count-1);
        deltaZ=deltaZ/(count-1);
        std::vector<double> X;
        std::vector<double> Y;
        std::vector<double> Z;
        for(int i=0;i<count;i++)
        {
            X.push_back(p1[0]+deltaX*i);
            Y.push_back(p1[1]+deltaY*i);
            Z.push_back(p1[2]+deltaZ*i);
        }
        std::vector<double> ZERO_AVG_X(X.size(),0);
        std::vector<double> ZERO_AVG_Y(X.size(),0);
        std::vector<double> ZERO_AVG_Z(X.size(),0);
        std::vector<std::vector<int>> IDX;
        for(size_t i=0;i<X.size();i++)
        {
            IDX.push_back(std::vector<int>());
        }


        for(size_t k=0;k<zero.particles.size();k++)
        {
            Particle p=zero.particles[k];
            for(size_t i=0;i<X.size();i++)
            {
                double x=p.position[0]-X[i];
                double y=p.position[1]-Y[i];
                double z=p.position[2]-Z[i];
                double ilgis=std::sqrt(x*x+y*y+z*z);
                if(ilgis<=radius)
                {
                    IDX[i].push_back(k);
                    ZERO_AVG_X[i]=ZERO_AVG_X[i]+p.position[0];
                    ZERO_AVG_Y[i]=ZERO_AVG_Y[i]+p.position[1];
                    ZERO_AVG_Z[i]=ZERO_AVG_Z[i]+p.position[2];
                }
            }
        }

        for(size_t i=0;i<X.size();i++)
        {
            std::cout<<"LineStrain segment "<<i<<" count of particles "<<IDX[i].size()<<"\n";
            ZERO_AVG_X[i]=ZERO_AVG_X[i]/IDX[i].size();
            ZERO_AVG_Y[i]=ZERO_AVG_Y[i]/IDX[i].size();
            ZERO_AVG_Z[i]=ZERO_AVG_Z[i]/IDX[i].size();
        }

        std::vector<double> AVG_X(X.size(),0);
        std::vector<double> AVG_Y(X.size(),0);
        std::vector<double> AVG_Z(X.size(),0);
        for(size_t i=0;i<IDX.size();i++)
        {
            std::vector<int> ids=IDX[i];
            for(size_t k=0;k<ids.size();k++)
            {
                Particle p=current.particles[ids[k]];
                AVG_X[i]=AVG_X[i]+p.position[0];
                AVG_Y[i]=AVG_Y[i]+p.position[1];
                AVG_Z[i]=AVG_Z[i]+p.position[2];
            }
            AVG_X[i]=AVG_X[i]/ids.size();
            AVG_Y[i]=AVG_Y[i]/ids.size();
            AVG_Z[i]=AVG_Z[i]/ids.size();
        }
        POS_X.resize(count-1,0);
        POS_Y.resize(count-1,0);
        POS_Z.resize(count-1,0);
        STRAIN_X.resize(count-1,0);
        STRAIN_Y.resize(count-1,0);
        STRAIN_Z.resize(count-1,0);
        STRAIN.resize(count-1,0);
        for(size_t i=1;i<AVG_X.size();i++)
        {
            double zero_lengthx=fabs(ZERO_AVG_X[i-1]-ZERO_AVG_X[i]);
            double zero_lengthy=fabs(ZERO_AVG_Y[i-1]-ZERO_AVG_Y[i]);
            double zero_lengthz=fabs(ZERO_AVG_Z[i-1]-ZERO_AVG_Z[i]);
            double zero_length=std::sqrt(zero_lengthx*zero_lengthx+zero_lengthy*zero_lengthy+zero_lengthz*zero_lengthz);

            double lengthx=fabs(AVG_X[i-1]-AVG_X[i]);
            double lengthy=fabs(AVG_Y[i-1]-AVG_Y[i]);
            double lengthz=fabs(AVG_Z[i-1]-AVG_Z[i]);
            double length=std::sqrt(lengthx*lengthx+lengthy*lengthy+lengthz*lengthz);
            double x=(ZERO_AVG_X[i-1]+ZERO_AVG_X[i])/2;
            double y=(ZERO_AVG_Y[i-1]+ZERO_AVG_Y[i])/2;
            double z=(ZERO_AVG_Z[i-1]+ZERO_AVG_Z[i])/2;
            POS_X[i-1]=x;
            POS_Y[i-1]=y;
            POS_Z[i-1]=z;
            STRAIN_X[i-1]=lengthx/zero_lengthx;
            STRAIN_Y[i-1]=lengthy/zero_lengthy;
            STRAIN_Z[i-1]=lengthz/zero_lengthz;
            STRAIN[i-1]=length/zero_length;

        /*    std::cout<<i-1<<" x= "<<POS_X[i-1]<<" y= "<<POS_Y[i-1]<<" z= "<<POS_Z[i-1]
                    <<" strain x= "<<STRAIN_X[i-1]<<" strain y= "<<STRAIN_Y[i-1]<<" strain z= "<<STRAIN_Z[i-1]<<
                      " strain total= "<<STRAIN[i-1]<<"\n";
*/

        }


    }
}

void LineStrain::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        names.push_back("LINE_STRAIN_COUNT");
        values.push_back(STRAIN.size());
        for(size_t i=0;i<STRAIN.size();i++)
        {
            names.push_back(getName("LINE_STRAIN_POS_X",i));
            values.push_back(POS_X[i]);
            names.push_back(getName("LINE_STRAIN_POS_Y",i));
            values.push_back(POS_Y[i]);
            names.push_back(getName("LINE_STRAIN_POS_Z",i));
            values.push_back(POS_Z[i]);


            names.push_back(getName("LINE_STRAIN_X",i));
            values.push_back(STRAIN_X[i]);
            names.push_back(getName("LINE_STRAIN_Y",i));
            values.push_back(STRAIN_Y[i]);
            names.push_back(getName("LINE_STRAIN_Z",i));
            values.push_back(STRAIN_Z[i]);

            names.push_back("LINE_STRAIN");
            values.push_back(STRAIN[i]);

        }

    }
}

