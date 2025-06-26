#pragma once
#include <array>
#include <functional>
#include <cmath>

struct Vertex {
    double x;
    double y;
    bool operator==(Vertex const& other) const noexcept {
        return x == other.x && y == other.y;
    }
};

struct VertexHash {
    std::size_t operator()(Vertex const& v) const noexcept {
        auto h1 = std::hash<long long>()(static_cast<long long>(std::llround(v.x * 1e6)));
        auto h2 = std::hash<long long>()(static_cast<long long>(std::llround(v.y * 1e6)));
        return h1 ^ (h2 << 1);
    }
};
