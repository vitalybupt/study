cmake_minimum_required(VERSION 2.8.11)

add_executable(2sums src/1_twoSums.cc)
target_compile_options(2sums PUBLIC -O0 -g -std=c++11)

add_executable(revertInteger src/7_revertInteger.cc)
target_compile_options(revertInteger  PUBLIC -O0 -g -std=c++11)

add_executable(longestPalindrome src/5_longestPalindrome.cc)
target_compile_options(longestPalindrome  PUBLIC -O0 -g -std=c++11)

add_executable(threeSums src/15_threeSums.cc)
target_compile_options(threeSums  PUBLIC -O0 -g -std=c++11)

add_executable(courseSchedule src/207_courseSchedule.cpp)
target_compile_options(courseSchedule  PUBLIC -O0 -g -std=c++11)

add_executable(intToRoman src/intToRoman.cpp)
target_compile_options(intToRoman PUBLIC -Os)

add_executable(generateParenthesis src/generateParenthesis.cpp)
target_compile_options(generateParenthesis PUBLIC -Os -std=c++11)

add_executable(permutations src/permutations.cpp)
target_compile_options(permutations  PUBLIC -O0 -g -std=c++11)

add_executable(groupAnagrams src/groupAnagrams.cpp)
target_compile_options(groupAnagrams  PUBLIC -O0 -g -std=c++11)

add_executable(addingBinary src/addingBinary.cpp)
target_compile_options(addingBinary  PUBLIC -O0 -g -std=c++11)

add_executable(courseSchedule src/207_courseSchedule.cpp)
target_compile_options(courseSchedule  PUBLIC -O0 -g -std=c++11)

add_executable(longestPalindrome src/5_longestPalindrome.cc)
target_compile_options(longestPalindrome  PUBLIC -O0 -g -std=c++11)

add_executable(revertInteger src/7_revertInteger.cc)
target_compile_options(revertInteger  PUBLIC -O0 -g -std=c++11)

add_executable(3sum src/15_3sum.cc)
target_compile_options(3sum  PUBLIC -O0 -g -std=c++11)
