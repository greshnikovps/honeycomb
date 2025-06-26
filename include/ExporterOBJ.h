#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <string>
#include <vector>

class ExporterOBJ {
public:
    static void exportGrid(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, const std::string& filepath);
};