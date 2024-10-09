#include "storage.hpp"

namespace storage {
    Storage::Storage(size_t vec_size) {
        power = vec_size;
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

    bool Storage::multiply(const std::vector<uint64_t> &a_nums, const std::vector<uint64_t> &b_nums) const noexcept {
        // split vector into blocks

        bool res = false;
        for (int i = 0; i < a_nums.size(); ++i) {
            // split every block into out stuff
            uint64_t block_a = a_nums[i];
            uint64_t block_b = b_nums[i];

            uint64_t accum_a;
            uint64_t accum_b;

            auto quot = 64 / power;
            uint64_t mask = static_cast<uint64_t>(std::pow(2, power)) - 1;
            for (auto j = 0; j < quot; ++j) {
                res ^= get_value(block_a & mask, block_b & mask);
                block_a >>= power;
                block_b >>= power;
            }
            auto rem = 64 % power;
            auto rem_mask = static_cast<uint64_t>(std::pow(2, rem)) - 1;

            res ^= get_value(block_a & rem_mask, block_b & rem_mask);

        }

        return res;
    }

}