#include "HexGridMatrix.h"
#include <cmath>
#include <stdexcept>

class HexGridMatrix; // forward for clarity

HexGridMatrix::HexGridMatrix(Config cfg) : cfg_(cfg) {
    if (cfg_.width <= 0 || cfg_.height <= 0 || cfg_.side <= 0) {
        throw std::invalid_argument("Invalid grid configuration");
    }
}

void HexGridMatrix::generate() {
    vertices_.clear();
    edges_.clear();
    vertexIndexes_.clear();
    generateVertices();
    generateHorizontalEdges();
    generateVerticalEdges();
}

void HexGridMatrix::generateVertices() {
    double side = cfg_.side;
    double diag = side * 2;
    int numRows = cfg_.height * 2 + 1;
    vertexIndexes_.resize(numRows);
    for (int row = 0; row < numRows; ++row) {

        int numCols = cfg_.width + 1;
        bool first_or_last_row = (row == 0) || (row == numRows - 1);
        bool even_width = (cfg_.width % 2 == 0);
        if (even_width && first_or_last_row) {
            numCols = numCols - 1;
        }

        double y = row * (side * std::sqrt(3.0) / 2.0);
        double x = (row % 2 == 0) ? 0.0 : - side / 2.0;
        bool nextShort = (row % 2 == 0);
        vertexIndexes_[row].clear();
        for (int col = 0; col < numCols; ++col) {
            vertexIndexes_[row].push_back(vertices_.size());
            vertices_.push_back(Vertex{x, y});
            if (nextShort) x += side;
            else x += diag;
            nextShort = !nextShort;
        }
    }
}

void HexGridMatrix::generateHorizontalEdges() {
    size_t numRows = vertexIndexes_.size();
    for (size_t row = 0; row < numRows; ++row) {
        size_t numCols = vertexIndexes_[row].size();
        for (size_t col = 0; col < numCols - 1; ++col) {
            if ((col % 2) == (row % 2)) {
                edges_.emplace_back(vertexIndexes_[row][col], vertexIndexes_[row][col+1]);
            }
        }
    }
}

void HexGridMatrix::generateVerticalEdges() {
    size_t numRows = vertexIndexes_.size();
    for (int row = 1; row < numRows; ++row) {
        size_t prevCols = vertexIndexes_[row - 1].size();
        size_t currCols = vertexIndexes_[row].size();
        size_t minCols = std::min(prevCols, currCols);
        for (int col = 0; col < minCols; ++col) {
            std::size_t vPrev = vertexIndexes_[row - 1][col];
            std::size_t vCurr = vertexIndexes_[row][col];
            edges_.emplace_back(vPrev, vCurr);
        }
    }
}

const std::vector<Vertex>& HexGridMatrix::vertices() const noexcept {
    return vertices_;
}

const std::vector<Edge>& HexGridMatrix::edges() const noexcept {
    return edges_;
}