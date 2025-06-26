#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>

class HexGridMatrix {
public:
    struct Config {
        int width;   // число сот по ширине
        int height;  // число сот по высоте
        double side;
        bool flatTop;
    };

    explicit HexGridMatrix(Config cfg);
    void generate();
    const std::vector<Vertex>& vertices() const noexcept;
    const std::vector<Edge>& edges() const noexcept;

private:
    Config cfg_;
    std::vector<Vertex> vertices_;
    std::vector<Edge> edges_;
    std::vector<std::vector<std::size_t>> vertexIndexes_; // [row][col] -> vertex index
    void generateVertices();
    void generateHorizontalEdges();
    void generateVerticalEdges();
    Vertex computeVertex(int row, int col) const;
    void addEdges(int row, int col);
}; 