#include "PorocityInBox.h"
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>
#include <vtkCellArray.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkFieldData.h>
#include <vtkDataSetWriter.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3D.h>
#include <vtkPlane.h>
#include <vtkPlaneCollection.h>
#include <vtkClipClosedSurface.h>
#include <vtkMassProperties.h>

PorocityInBox::PorocityInBox()
{

}
void PorocityInBox::Compute(TASKAI &points, ParsingParameters *params)
{
    auto result=params->getResults();
    if(result.count("porocity"))
    {
        calculate=true;
        int RESOLUTION=result["resolution"].as<int>();
        std::vector<double> bounds=result["bounds"].as<std::vector<double> >();

        double Rmin=1000000;
        double Rmax=-1000000;
        GetMinMaxRadius(points,Rmin,Rmax);
        Rmax=Rmax*3;


        double minx=bounds[0];
        double miny=bounds[2];
        double minz=bounds[4];
        double maxx=bounds[1];
        double maxy=bounds[3];
        double maxz=bounds[5];


        vtkSmartPointer<vtkPolyData>poly=vtkSmartPointer<vtkPolyData>::New();
        vtkSmartPointer<vtkPoints>points1=vtkSmartPointer<vtkPoints>::New();
        vtkSmartPointer<vtkDoubleArray>radius=vtkSmartPointer<vtkDoubleArray>::New();
        radius->SetName("RADIUS");
        radius->SetNumberOfComponents(1);
        vtkSmartPointer<vtkCellArray>cells=vtkSmartPointer<vtkCellArray>::New();

        for(size_t i=0;i<points.size();i++)
        {
            Point P=points[i];
            if(P.x>(minx-Rmax) && P.x<(maxx+Rmax))
                if(P.y>(miny-Rmax) && P.y<(maxy+Rmax))
                    if(P.z>(minz-Rmax) && P.z<(maxz+Rmax))
                    {
                        points1->InsertNextPoint(P.x,P.y,P.z);
                        radius->InsertNextTuple1(P.r);
                        cells->InsertNextCell(1);
                        cells->InsertCellPoint(points1->GetNumberOfPoints()-1);
                    }
        }
        poly->SetPoints(points1);
        poly->GetPointData()->SetScalars(radius);
        poly->SetVerts(cells);
        vtkSmartPointer<vtkSphereSource>s=vtkSmartPointer<vtkSphereSource>::New();
        s->SetRadius(1);
        s->SetCenter(0,0,0);
        s->SetPhiResolution(RESOLUTION);
        s->SetThetaResolution(RESOLUTION);
        s->Update();
        vtkSmartPointer<vtkGlyph3D>g=vtkSmartPointer<vtkGlyph3D>::New();
        g->SetSourceData(s->GetOutput());
        g->SetInputData(poly);
        g->SetScaleModeToScaleByScalar();
        g->SetScaleFactor(1);
        g->Update();


        vtkSmartPointer<vtkClipClosedSurface>clip=vtkSmartPointer<vtkClipClosedSurface>::New();
        clip->SetInputConnection(g->GetOutputPort());
        vtkSmartPointer<vtkPlaneCollection>planes=vtkSmartPointer<vtkPlaneCollection>::New();
        vtkSmartPointer<vtkPlane>p1=vtkSmartPointer<vtkPlane>::New();
        p1->SetNormal(1,0,0);
        vtkSmartPointer<vtkPlane>p2=vtkSmartPointer<vtkPlane>::New();
        p2->SetNormal(-1,0,0);
        vtkSmartPointer<vtkPlane>p3=vtkSmartPointer<vtkPlane>::New();
        p3->SetNormal(0,1,0);
        vtkSmartPointer<vtkPlane>p4=vtkSmartPointer<vtkPlane>::New();
        p4->SetNormal(0,-1,0);
        vtkSmartPointer<vtkPlane>p5=vtkSmartPointer<vtkPlane>::New();
        p5->SetNormal(0,0,1);
        vtkSmartPointer<vtkPlane>p6=vtkSmartPointer<vtkPlane>::New();
        p6->SetNormal(0,0,-1);
        planes->AddItem(p1);
        planes->AddItem(p2);
        planes->AddItem(p3);
        planes->AddItem(p4);
        planes->AddItem(p5);
        planes->AddItem(p6);
        clip->SetClippingPlanes(planes);
        //  clip->Update();

        vtkSmartPointer<vtkMassProperties >mesh=vtkSmartPointer<vtkMassProperties >::New();
        mesh->SetInputConnection(clip->GetOutputPort());

        //mesh->Update();
        p6->SetOrigin(0,0,maxz);
        p5->SetOrigin(0,0,minz);
        p4->SetOrigin(0,maxy,0);
        p3->SetOrigin(0,miny,0);
        p1->SetOrigin(minx,0,0);
        p2->SetOrigin(maxx,0,0);

        planes->Modified();
        clip->Update();
        mesh->Update();
        double turis=mesh->GetVolume();

        double lengthx=maxx-minx;
        double lengthy=maxy-miny;
        double lengthz=maxz-minz;
        value=turis/(lengthx*lengthy*lengthz);
        vtkSmartPointer<vtkCubeSource>cube=vtkSmartPointer<vtkCubeSource>::New();
        cube->SetBounds(minx,maxx,miny,maxy,minz,maxz);
        cube->Update();
        vtkSmartPointer<vtkDataSetWriter>writer=vtkSmartPointer<vtkDataSetWriter>::New();
        writer->SetInputData(cube->GetOutput());
        writer->SetFileName("Porocity_BOX.vtk");
        writer->Write();
    }
}
void PorocityInBox::GetNamesAndValues(std::vector<std::string> &names,std::vector<double> &values)
{
    if(calculate)
    {
        names.push_back("POROCITY");
        values.push_back(value);
    }
}
