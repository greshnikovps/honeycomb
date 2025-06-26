#pragma once
#include "Vertex.h"
#include "Edge.h"
#include <vector>

/**
 * @brief Class for generating a hexagonal (honeycomb) grid using a matrix of vertex indices.
 *
 * HexGridMatrix builds vertices and edges to form a correct honeycomb structure without duplicates or 'whiskers' at the edges.
 * Allows exporting vertices and edges for visualization or saving to OBJ.
 */
class HexGridMatrix {
public:
    /**
     * @brief Grid configuration parameters.
     * @param width   Number of hexagons horizontally
     * @param height  Number of hexagons vertically
     * @param side    Hexagon edge length
     * @param flatTop Orientation (flatTop=true means horizontal rows)
     */
    struct Config {
        int width;    ///< Number of hexagons horizontally
        int height;   ///< Number of hexagons vertically
        double side;  ///< Hexagon edge length
        bool flatTop; ///< Orientation (flatTop=true means horizontal rows)
    };

    /**
     * @brief Constructor with configuration parameters.
     */
    explicit HexGridMatrix(Config cfg);
    /**
     * @brief Generate the grid (vertices and edges).
     */
    void generate();
    /**
     * @brief Get the list of all grid vertices.
     */
    const std::vector<Vertex>& vertices() const noexcept;
    /**
     * @brief Get the list of all grid edges.
     */
    const std::vector<Edge>& edges() const noexcept;

private:
    Config cfg_; ///< Grid configuration
    std::vector<Vertex> vertices_; ///< All grid vertices
    std::vector<Edge> edges_;      ///< All grid edges
    std::vector<std::vector<std::size_t>> vertexIndexes_; ///< Vertex indices by row and column
    void generateVertices();
    void generateHorizontalEdges();
    void generateVerticalEdges();
    Vertex computeVertex(int row, int col) const;
    void addEdges(int row, int col);
}; 