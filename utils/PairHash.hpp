#pragma once
#include <utility>
#include <functional>
// A custom hash function structure for std::pair, bcs unordered map and set don't have hash function for it
struct PairHash {
    template<typename T1, typename T2>
    // overloading function call operator
    std::size_t operator()(const std::pair<T1, T2>& p) const noexcept {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        // A simple way to combine hashes
        // (I could use boost::hash_combine but didn't to avoid extra library)
        // ^ - XOR (commutative)
        // << - bit left shift
        // The bit shifting helps avoid collisions bcs xor of (a, b) is same as (b, a)
        return h1 ^ (h2 << 1);
    }
};
