cmake_minimum_required (VERSION 2.8.11)
project (C_CPP)

add_executable(3sum src/3sum.c)
target_compile_options(3sum PUBLIC -Os  --std=gnu99)

add_executable(merge src/mergeintervals.c)
target_compile_options(merge PUBLIC -O0 -g  --std=gnu99)
