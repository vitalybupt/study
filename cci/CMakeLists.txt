cmake_minimum_required (VERSION 2.8.11)
project (crackcodeinterview)

include_directories(${CMAKE_SOURCE_DIR}/inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(lib)

find_program(CMAKE_C_CPPCHECK NAMES cppcheck)
if (CMAKE_C_CPPCHECK)
    list(
        APPEND CMAKE_C_CPPCHECK 
            "--enable=warning"
	    "--enable=style"	
            "--inconclusive"
            "--force" 
            "--inline-suppr"
            "--suppressions-list=${CMAKE_SOURCE_DIR}/CppCheckSuppressions.txt"
    )
endif()

AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR} C_SRCS)

add_executable(cci ${C_SRCS})
target_compile_options(cci PUBLIC -O0 -g3 -pedantic-errors -ansi -Wextra -Wall -Winit-self  -Wuninitialized -Wmissing-declarations -Winit-self --std=gnu17)
target_link_libraries(cci utils)


