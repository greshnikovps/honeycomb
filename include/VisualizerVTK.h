#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>

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

class VisualizerVTK {
public:
    static void visualize(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges);
};