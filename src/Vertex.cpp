#include "Vertex.h"
#include <cmath>

bool Vertex::operator==(Vertex const& other) const noexcept {
    return x == other.x && y == other.y;
}

std::size_t VertexHash::operator()(Vertex const& v) const noexcept {
    // Quantize coords to avoid floating errors; here using std::hash<double> is acceptable
    auto h1 = std::hash<long long>()(static_cast<long long>(std::llround(v.x * 1e6)));
    auto h2 = std::hash<long long>()(static_cast<long long>(std::llround(v.y * 1e6)));
    return h1 ^ (h2 << 1);
} 