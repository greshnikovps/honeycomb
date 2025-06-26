# HoneycombFrame

A generator for hexagonal (honeycomb) grids with OBJ export and optional VTK visualization.

## Features
- Generates a regular hexagonal grid (honeycomb) with configurable size and edge length
- Exports the grid to OBJ format
- Optional visualization using VTK
- Two grid generation algorithms: classic (HexGrid) and matrix-based (HexGridMatrix)

## Build Instructions

```sh
cmake -S . -B build 
cmake --build build
```

- To disable visualization: `-DUSE_VTK=OFF`

## Usage

```sh
./HoneycombFrame [options]
```

### Command-line options
- `-w, --width <int>`       — grid width (number of hexagons horizontally)
- `-h, --height <int>`      — grid height (number of hexagons vertically)
- `-s, --side <double>`     — hexagon edge length
- `--no-visualize`          — disable visualization
- `--matrix`                — use the matrix-based algorithm (HexGridMatrix)
- `-o, --output <file>`     — output OBJ file name

## Code Structure
- `src/HexGridMatrix.cpp`, `include/HexGridMatrix.h` — matrix-based honeycomb grid generation
- `src/main.cpp` — entry point, argument parsing, export, visualization
- `src/ExporterOBJ.cpp` — OBJ export
- `src/VisualizerVTK.cpp` — VTK visualization (if enabled)
- `Vertex.h`, `Edge.h` — vertex and edge structures

## Example

```sh
./HoneycombFrame --width 10 --height 10 --side 1.0 --no-visualize -o honeycomb.obj
```
