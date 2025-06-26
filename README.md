# HoneycombFrame

This project generates a 20×20 hexagonal grid frame (vertices and edges) with side length 1,
eliminating duplicate vertices/edges, and exports the geometry in OBJ format. Optionally,
visualizes the frame using VTK. Structured as a CMake project with dependencies managed via vcpkg manifest.

## Features
- Generate hex grid using axial coordinates
- Deduplicate vertices and edges
- Export to Wavefront OBJ
- Optional visualization via VTK
- Modern C++17, clean architecture

## Directory Structure
```
HoneycombFrame/
├── CMakeLists.txt
├── vcpkg.json
├── include/
│   ├── HexGrid.hpp
│   ├── Vertex.hpp
│   ├── Edge.hpp
│   ├── ExporterOBJ.hpp
│   └── VisualizerVTK.hpp
├── src/
│   ├── HexGrid.cpp
│   ├── ExporterOBJ.cpp
│   ├── VisualizerVTK.cpp
│   └── main.cpp
└── tests/ (optional)
    └── HexGridTest.cpp
```

## Build Instructions
1. Install vcpkg and integrate with CMake (manifest mode).
2. From project root:
   ```sh
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
3. Run the application:
   ```sh
   ./HoneycombFrame
   ```

## Usage
By default, generates a 20×20 grid and exports to `honeycomb.obj`. Use CLI options to adjust size or enable VTK visualization.
