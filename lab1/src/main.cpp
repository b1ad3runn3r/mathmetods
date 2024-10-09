#include <iostream>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include "storage.hpp"
#include "utils.hpp"
#include <chrono>

#include "word_splitting.hpp"

using block_type = uint64_t;
size_t vec_size;
#define TIMES 20

bool multiply(const boost::dynamic_bitset<block_type> &test1, const boost::dynamic_bitset<block_type> &test2) {
    bool res_1 = false;
    for (size_t i = 0; i < vec_size; ++i) {
        res_1 ^= (test1[i] & test2[i]);
    }

    return res_1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    const auto power = std::strtoull(argv[1], nullptr, 10);

    uint64_t times_original[TIMES] = {0};
    uint64_t times_optimized_1[TIMES] = {0};
    uint64_t times_optimized_2[TIMES] = {0};
    storage::Storage bv_storage(power);

    for (int repet = 0; repet < TIMES; ++repet) {

        vec_size = static_cast<size_t>(std::pow(2, power));
        boost::dynamic_bitset<block_type> test1(vec_size);
        boost::dynamic_bitset<block_type> test2(vec_size);

        test1 = utils::generate_random_bitset<block_type>(test1);
        test2 = utils::generate_random_bitset<block_type>(test2);

        auto start_1 = std::chrono::high_resolution_clock::now();
        bool res_1 = multiply(test1, test2);
        auto end_1 = std::chrono::high_resolution_clock::now();
        times_original[repet] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_1 - start_1).count();

        std::vector<uint64_t> a_nums;
        std::vector<uint64_t> b_nums;
        a_nums.reserve(test1.num_blocks());
        b_nums.reserve(test2.num_blocks());
        boost::to_block_range(test1, std::back_inserter(a_nums));
        boost::to_block_range(test1, std::back_inserter(b_nums));

        auto start_2 = std::chrono::high_resolution_clock::now();
        bool res_2 = word_splitting::multiply<block_type>(a_nums, b_nums);
        auto end_2 = std::chrono::high_resolution_clock::now();
        times_optimized_1[repet] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_2 - start_2).count();

        auto start_3 = std::chrono::high_resolution_clock::now();
        bool res_3 = bv_storage.multiply(a_nums, b_nums);
        auto end_3 = std::chrono::high_resolution_clock::now();
        times_optimized_2[repet] = std::chrono::duration_cast<std::chrono::nanoseconds>(end_3 - start_3).count();
    }

        boost::multiprecision::int256_t avg_orig = 0;
        boost::multiprecision::int256_t avg_opt_1 = 0;
        boost::multiprecision::int256_t avg_opt_2 = 0;
        for (int i = 0; i < TIMES; ++i) {
            avg_orig += times_original[i];
            avg_opt_1 += times_optimized_1[i];
            avg_opt_2 += times_optimized_2[i];
        }

        std::cout << avg_orig / TIMES << std::endl;
        std::cout << avg_opt_1 / TIMES << std::endl;
        std::cout << avg_opt_2 / TIMES << std::endl;


    return 0;
}
