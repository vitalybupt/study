cmake_minimum_required (VERSION 2.8.11)

if(ENABLE_TESTS)
  enable_testing()
endif(ENABLE_TESTS)


SET(HDRS
  include/sortlist.h)

add_library(sortlist SHARED src/sortlist.c)
target_compile_options(sortlist PUBLIC -O2 -Wall -Werror -Wno-unused --std=gnu99 -Wmissing-declarations)
target_include_directories(sortlist PUBLIC ${CMAKE_SOURCE_DIR}/sortlist/include)

add_executable(demo src/main.c ${HDRS})
target_compile_options(demo PUBLIC -O2 -Wall -Werror -Wno-unused --std=gnu99 -Wmissing-declarations)
target_include_directories(demo PUBLIC ${CMAKE_SOURCE_DIR}/sortlist/include)

target_link_libraries(demo LINK_PUBLIC sortlist)

if(ENABLE_TESTS)
  add_subdirectory(test/mocks)
  add_subdirectory(test/testsuites/)
endif(ENABLE_TESTS)
