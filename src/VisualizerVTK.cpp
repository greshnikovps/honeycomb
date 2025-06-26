#include "VisualizerVTK.h"
#include <iostream>
#ifdef USE_VTK
#include <vtkSmartPointer.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkLine.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkWin32OpenGLRenderWindow.h>
#endif
#include <stdexcept>

void VisualizerVTK::visualize(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges) {
#ifdef USE_VTK
    auto points = vtkSmartPointer<vtkPoints>::New();
    auto lines = vtkSmartPointer<vtkCellArray>::New();
    for (const auto& v : vertices) {
        points->InsertNextPoint(v.x, v.y, 0.0);
    }
    for (const auto& e : edges) {
        auto line = vtkSmartPointer<vtkLine>::New();
        line->GetPointIds()->SetId(0, static_cast<vtkIdType>(e.v1));
        line->GetPointIds()->SetId(1, static_cast<vtkIdType>(e.v2));
        lines->InsertNextCell(line);
    }
    auto polyData = vtkSmartPointer<vtkPolyData>::New();
    polyData->SetPoints(points);
    polyData->SetLines(lines);

    std::cout << "Points: " << points->GetNumberOfPoints() << std::endl;
    std::cout << "Lines: " << lines->GetNumberOfCells() << std::endl;

    auto mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
    auto actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
    actor->GetProperty()->SetLineWidth(2.0);

    auto renderer = vtkSmartPointer<vtkRenderer>::New();
    renderer->AddActor(actor);
    renderer->SetBackground(1.0, 1.0, 1.0);
    auto renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);
    auto interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    interactor->SetRenderWindow(renderWindow);
    renderer->ResetCamera();
    renderWindow->Render();
    interactor->Initialize();
    interactor->Start();
#else
    throw std::runtime_error("VTK support not enabled. Define USE_VTK and link VTK.");
#endif
}