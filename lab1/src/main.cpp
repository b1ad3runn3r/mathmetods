#include <iostream>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include "storage.hpp"

int main() {
    storage::Storage storage_15(15);

    std::cout << storage_15.get_value(358, 437) << std::endl;



    return 0;
}
