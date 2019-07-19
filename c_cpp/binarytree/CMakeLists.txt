cmake_minimum_required(VERSION 2.8)

SET(HDRS
  include/binarytree.h)

add_library(binarytree SHARED src/binarytree.c)
target_compile_options(binarytree PUBLIC -Og -g -Wall -Werror -Wno-unused -Wmissing-declarations --std=gnu99)
target_include_directories(binarytree PUBLIC ${CMAKE_SOURCE_DIR}/binarytree/include)

add_executable(demo_binarytree src/main.c ${HDRS})
target_compile_options(demo_binarytree PUBLIC -Og -g -Wall -Werror -Wno-unused -Wmissing-declarations --std=gnu99)
target_include_directories(binarytree PUBLIC ${CMAKE_SOURCE_DIR}/binarytree/include)

target_link_libraries(demo_binarytree LINK_PUBLIC binarytree)
  
