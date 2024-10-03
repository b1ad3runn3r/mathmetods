#include <iostream>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include "storage.hpp"
#include "utils.hpp"
#include <chrono>

#include "word_splitting.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    const auto power = std::strtoull(argv[1], nullptr, 10);
    auto vec_size = static_cast<size_t>(std::pow(2, power));
    boost::dynamic_bitset<uint64_t> test1(vec_size);
    boost::dynamic_bitset<uint64_t> test2(vec_size);
    test1 = utils::generate_random_bitset<uint64_t>(test1);
    test2 = utils::generate_random_bitset<uint64_t>(test2);

    bool res_1 = false;
    auto start_1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < vec_size; ++i) {
        res_1 ^= (test1[i] & test2[i]);
    }
    auto end_1 = std::chrono::high_resolution_clock::now();
    auto delta1 = std::chrono::duration_cast<std::chrono::microseconds>(end_1 - start_1).count();
    std::cout << res_1 << " Usual took " << delta1 << " ms" << std::endl;

    auto start_2 = std::chrono::high_resolution_clock::now();
    bool res_2 = word_splitting::multiply(test1, test2);
    auto end_2 = std::chrono::high_resolution_clock::now();
    auto delta2 = std::chrono::duration_cast<std::chrono::microseconds>(end_2 - start_2).count();
    std::cout << "Optimized took " << delta2 << " ms" << std::endl;

    assert(res_1 == res_2);
    return 0;
}
