#include "HexGridMatrix.h"
#include "ExporterOBJ.h"
#include <iostream>
#include <string>

#ifdef USE_VTK
#include "VisualizerVTK.h"
#endif

struct ProgramOptions {
    int width = 20;
    int height = 20;
    double side = 1.0;
    bool doVisualize = true;
    std::string outputFile = "honeycomb.obj";
};

void printHelp(const char* progName) {
    std::cout << "Usage: " << progName << " [options]\n"
              << "  -w, --width <int>       grid width (columns)\n"
              << "  -h, --height <int>      grid height (rows)\n"
              << "  -s, --side <double>     side length (default 1.0)\n"
              << "  --pointy                use pointy-top orientation (default flat-top)\n"
              << "  --no-visualize          disable VTK visualization\n"
              << "  -o, --output <file>     output OBJ file (default honeycomb.obj)\n";
}

bool parseArguments(int argc, char* argv[], ProgramOptions& opts) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "-w" || arg == "--width") && i + 1 < argc) {
            opts.width = std::stoi(argv[++i]);
        } else if ((arg == "-h" || arg == "--height") && i + 1 < argc) {
            opts.height = std::stoi(argv[++i]);
        } else if ((arg == "-s" || arg == "--side") && i + 1 < argc) {
            opts.side = std::stod(argv[++i]);
        } else if (arg == "--no-visualize") {
            opts.doVisualize = false;
        } else if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
            opts.outputFile = argv[++i];
        } else if (arg == "-?" || arg == "--help") {
            printHelp(argv[0]);
            return false;
        } else {
            std::cerr << "Unknown argument: " << arg << "\n";
            printHelp(argv[0]);
            return false;
        }
    }
    return true;
}

HexGridMatrix createMatrixGrid(const ProgramOptions& opts) {
    HexGridMatrix::Config cfg{opts.width, opts.height, opts.side};
    HexGridMatrix grid(cfg);
    grid.generate();
    return grid;
}

void exportGrid(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges, const std::string& outputFile) {
    ExporterOBJ::exportGrid(vertices, edges, outputFile);
    std::cout << "Exported to " << outputFile << "\n";
}

#ifdef USE_VTK
void visualizeGrid(const std::vector<Vertex>& vertices, const std::vector<Edge>& edges) {
    VisualizerVTK::visualize(vertices, edges);
}
#endif

int main(int argc, char* argv[]) {
    try {
        ProgramOptions opts;
        if (!parseArguments(argc, argv, opts)) {
            return 0;
        }
        HexGridMatrix grid = createMatrixGrid(opts);
        std::cout << "[Matrix] Generated grid: " << grid.vertices().size() << " vertices, "
                    << grid.edges().size() << " edges.\n";
        exportGrid(grid.vertices(), grid.edges(), opts.outputFile);
#ifdef USE_VTK
        if (opts.doVisualize) {
            visualizeGrid(grid.vertices(), grid.edges());
        }
#endif
    } catch (std::exception const& ex) {
        std::cerr << "Error: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}