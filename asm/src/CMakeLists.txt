AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src EXAMPLE_SRCS)
add_library(example SHARED ${EXAMPLE_SRCS})
target_compile_options(example PUBLIC -O0 -g3 -pedantic-errors -ansi -Wextra -Wall -Winit-self  -Wuninitialized -Wmissing-declarations -Winit-self --std=gnu11)

set_target_properties(example PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libexample.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/inc/"
)
