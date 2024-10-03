#include <iostream>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "storage.hpp"
#include "utils.hpp"
#include <chrono>

#include "word_splitting.hpp"

using block_type = uint64_t;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    uint64_t times_original[100] = {0};
    uint64_t times_optimized[100] = {0};

    for (int repet = 0; repet < 100; ++repet) {
        const auto power = std::strtoull(argv[1], nullptr, 10);
        auto vec_size = static_cast<size_t>(std::pow(2, power));
        boost::dynamic_bitset<block_type> test1(vec_size);
        boost::dynamic_bitset<block_type> test2(vec_size);

        test1 = utils::generate_random_bitset<block_type>(test1);
        test2 = utils::generate_random_bitset<block_type>(test2);

        bool res_1 = false;
        auto start_1 = std::chrono::high_resolution_clock::now();
        for (size_t i = 0; i < vec_size; ++i) {
            res_1 ^= (test1[i] & test2[i]);
        }
        auto end_1 = std::chrono::high_resolution_clock::now();
        auto delta1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_1 - start_1).count();

        times_original[repet] = delta1;

        bool res_2 = false;
        auto delta2 = word_splitting::multiply<block_type>(test1, test2, res_2);

        times_optimized[repet] = delta2;

        assert(res_1 == res_2);
    }

    boost::multiprecision::int256_t avg_orig = 0;
    boost::multiprecision::int256_t avg_opt = 0;
    for (int i = 0; i < 100; ++i) {
        avg_orig += times_original[i];
        avg_opt += times_optimized[i];
    }

    std::cout << avg_orig / 100 << std::endl;
    std::cout << avg_opt / 100 << std::endl;

    return 0;
}
