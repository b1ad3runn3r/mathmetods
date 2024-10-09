#ifndef WORD_SPLITTING_HPP
#define WORD_SPLITTING_HPP

#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <chrono>

namespace word_splitting {
    template<typename T>
    auto multiply(const std::vector<uint64_t> &a_nums, const std::vector<uint64_t> &b_nums) {
        bool res = false;
        for (uint64_t i = 0; i < a_nums.size(); i++) {
            res ^= std::popcount(a_nums[i] & b_nums[i]) % 2;
        }

        return res;
    }
}

#endif // WORD_SPLITTING_HPP
