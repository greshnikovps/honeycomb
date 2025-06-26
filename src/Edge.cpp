#include "Edge.h"

Edge::Edge(std::size_t a, std::size_t b) noexcept {
    if (a < b) { v1 = a; v2 = b; }
    else { v1 = b; v2 = a; }
}

bool Edge::operator==(Edge const& other) const noexcept {
    return v1 == other.v1 && v2 == other.v2;
}

std::size_t EdgeHash::operator()(Edge const& e) const noexcept {
    // Combine hashes
    return std::hash<std::size_t>()(e.v1) ^ (std::hash<std::size_t>()(e.v2) << 1);
} 