#pragma once
#include <utility>
#include <functional>

struct Edge {
    std::size_t v1;
    std::size_t v2;
    Edge(std::size_t a, std::size_t b) noexcept {
        if (a < b) { v1 = a; v2 = b; }
        else { v1 = b; v2 = a; }
    }
    bool operator==(Edge const& other) const noexcept {
        return v1 == other.v1 && v2 == other.v2;
    }
};

struct EdgeHash {
    std::size_t operator()(Edge const& e) const noexcept {
        return std::hash<std::size_t>()(e.v1) ^ (std::hash<std::size_t>()(e.v2) << 1);
    }
};