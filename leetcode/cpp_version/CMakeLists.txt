cmake_minimum_required(VERSION 2.8.11)

add_executable(2sums src/2sums.cpp)
target_compile_options(2sums PUBLIC -Os)

add_executable(addTwoNumbers src/addTwoNumbers.cpp)
target_compile_options(addTwoNumbers PUBLIC -Os)

add_executable(intToRoman src/intToRoman.cpp)
target_compile_options(intToRoman PUBLIC -Os)

