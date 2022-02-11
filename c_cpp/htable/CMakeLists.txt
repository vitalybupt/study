cmake_minimum_required(VERSION 3.1.0)
option(ENABLE_ASAN "Build with address sanitizer" OFF)

add_executable(demo_htable main.c)

if(ENABLE_ASAN)
  add_compile_options(-fno-omit-frame-pointer -fsanitize=address -static-libasan)
  set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -static-libasan")
endif()

target_compile_options(demo_htable PUBLIC -Og -g -Wall -Werror -Wno-unused --std=gnu99 -Wmissing-declarations -I${PROJECT_SOURCE_DIR} )
