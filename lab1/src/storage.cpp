#include "storage.hpp"

namespace storage {
    Storage::Storage(size_t vec_size) {
        auto x = static_cast<uint64_t>(std::pow(2, vec_size));
        auto y = x;

        matrix.resize(y);
        for (auto &vec : matrix) {
            vec.resize(x);
        }

        for (uint64_t a = 0; a < y; ++a) {
            for (uint64_t b = 0; b < x; ++b) {
                matrix[a][b] = std::popcount(a & b) % 2;
            }
        }
    }

    bool Storage::get_value(const boost::dynamic_bitset<>& a, const boost::dynamic_bitset<>& b) const noexcept {
        return matrix[a.to_ulong()][b.to_ulong()];
    }

    bool Storage::get_value(const uint32_t a, const uint32_t b) const noexcept {
        return matrix[a][b];
    }
}