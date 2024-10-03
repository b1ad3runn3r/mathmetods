#ifndef UTILS_HPP
#define UTILS_HPP

#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <random>

namespace utils {
    template <typename T>
    boost::dynamic_bitset<T> &generate_random_bitset(boost::dynamic_bitset<T> &bitset) {
        std::random_device rd;
        std::uniform_int_distribution<char> dist(0, 1);
        for (size_t i = 0; i < bitset.size(); ++i) {
            bitset[i] = dist(rd);
        }

        return bitset;
    }
}

#endif // UTILS_HPP
