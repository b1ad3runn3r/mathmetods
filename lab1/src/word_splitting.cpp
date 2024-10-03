#include "word_splitting.hpp"

namespace word_splitting {
    bool multiply(boost::dynamic_bitset<uint64_t> &a, boost::dynamic_bitset<uint64_t> &b) {
        if (a.size() <= 64) {
            return std::popcount(a.to_ulong() & b.to_ulong()) % 2;
        }

        std::vector<uint64_t> a_nums;
        std::vector<uint64_t> b_nums;
        a_nums.reserve(a.num_blocks());
        b_nums.reserve(b.num_blocks());
        boost::to_block_range(a, std::back_inserter(a_nums));
        boost::to_block_range(b, std::back_inserter(b_nums));
        bool res = false;

        for (uint64_t i = 0; i < a_nums.size(); i++) {
            res ^= std::popcount(a_nums[i] & b_nums[i]) % 2;
        }

        return res;
    }
}
