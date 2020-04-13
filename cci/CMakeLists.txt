cmake_minimum_required (VERSION 2.8.11)
project (crackcodeinterview)

include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(lib)

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR} C_SRCS)
add_executable(cci ${C_SRCS})
target_link_libraries(cci utils)