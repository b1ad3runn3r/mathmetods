#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <boost/dynamic_bitset/dynamic_bitset.hpp>

namespace storage {
    class Storage {
    private:
        std::vector<boost::dynamic_bitset<>> matrix;

    public:
        explicit Storage(size_t vec_size);
        [[nodiscard]] bool get_value(const boost::dynamic_bitset<>& a, const boost::dynamic_bitset<>& b) const noexcept;
        [[nodiscard]] bool get_value(uint32_t a, uint32_t b) const noexcept;
    };
}

#endif // STORAGE_HPP
