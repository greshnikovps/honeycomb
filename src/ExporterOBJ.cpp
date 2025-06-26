#include "ExporterOBJ.h"
#include <fstream>
#include <iomanip>
#include <stdexcept>

void ExporterOBJ::exportGrid(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, const std::string& filepath) {
    std::ofstream ofs(filepath);
    if (!ofs) {
        throw std::runtime_error("Cannot open output file: " + filepath);
    }
    ofs << std::fixed << std::setprecision(6);
    // Write vertices
    for (const auto& v : vertices) {
        ofs << "v " << v.x << " " << v.y << " 0.0\n";
    }
    ofs << "# " << vertices.size() << " vertices\n";
    // Write edges
    for (const auto& e : edges) {
        // OBJ indices start at 1
        ofs << "l " << (e.v1 + 1) << " " << (e.v2 + 1) << "\n";
    }
    ofs << "# " << edges.size() << " edges\n";
}