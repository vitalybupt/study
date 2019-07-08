cmake_minimum_required (VERSION 2.8.11)

if(ENABLE_TESTS)
  enable_testing()
endif(ENABLE_TESTS)

add_library(sortlist sortlist.c)

add_executable(demo main.c)
target_link_libraries(demo LINK_PUBLIC sortlist)

if(ENABLE_TESTS)
  add_subdirectory(test/mocks)
  add_subdirectory(test/testsuites/)
endif(ENABLE_TESTS)
