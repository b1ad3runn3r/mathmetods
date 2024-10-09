#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace storage {
    class Storage {
    private:
        std::vector<boost::dynamic_bitset<>> matrix;
        size_t power;

    public:
        explicit Storage(size_t vec_size);
        [[nodiscard]] bool multiply(const std::vector<uint64_t> &a_nums, const std::vector<uint64_t> &b_nums) const noexcept;
        [[nodiscard]] bool get_value(const uint64_t a, const uint64_t b) const {return matrix.at(a).at(b); }
    };
}

#endif // STORAGE_HPP
