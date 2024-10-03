cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0167 NEW)
project("lab1" CXX)
set(CMAKE_CXX_STANDARD 20)

find_package(Boost)

add_executable(lab1
        src/main.cpp
        src/storage.hpp
        src/storage.cpp
        src/word_splitting.cpp
        src/word_splitting.hpp
        src/utils.cpp
        src/utils.hpp
)

add_compile_options("-O2")
target_link_libraries(lab1 PRIVATE Boost::headers)
