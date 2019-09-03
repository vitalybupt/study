cmake_minimum_required(VERSION 2.8.11)

add_executable(2sums src/2sums.cpp)
target_compile_options(2sums PUBLIC -Os)

add_executable(addTwoNumbers src/addTwoNumbers.cpp)
target_compile_options(addTwoNumbers PUBLIC -Os)

add_executable(intToRoman src/intToRoman.cpp)
target_compile_options(intToRoman PUBLIC -Os)

add_executable(generateParenthesis src/generateParenthesis.cpp)
target_compile_options(generateParenthesis PUBLIC -Os -std=c++11)


add_executable(permutations src/permutations.cpp)
target_compile_options(permutations  PUBLIC -O0 -g -std=c++11)

add_executable(groupAnagrams src/groupAnagrams.cpp)
target_compile_options(groupAnagrams  PUBLIC -O0 -g -std=c++11)

