#ifndef WORD_SPLITTING_HPP
#define WORD_SPLITTING_HPP

#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <chrono>

namespace word_splitting {
    template<typename T>
    auto multiply(boost::dynamic_bitset<T> &a, boost::dynamic_bitset<T> &b, bool &result) {
        std::vector<T> a_nums;
        std::vector<T> b_nums;
        a_nums.reserve(a.num_blocks());
        b_nums.reserve(b.num_blocks());

        auto start_2 = std::chrono::high_resolution_clock::now();
        boost::to_block_range(a, std::back_inserter(a_nums));

        boost::to_block_range(b, std::back_inserter(b_nums));
        bool res = false;



        for (uint64_t i = 0; i < a_nums.size(); i++) {
            res ^= std::popcount(a_nums[i] & b_nums[i]) % 2;
        }

        auto end_2 = std::chrono::high_resolution_clock::now();
        auto delta2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_2 - start_2).count();
        result = res;

        return delta2;
    }
}

#endif // WORD_SPLITTING_HPP
