AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/lib LIB_SRCS)
add_library(utils SHARED ${LIB_SRCS})
target_compile_options(utils PUBLIC -O0 -g3 -pedantic-errors -ansi -Wextra -Wall -Winit-self  -Wuninitialized -Wmissing-declarations -Winit-self --std=gnu11)

set_target_properties(utils PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libutils.so"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/inc/"
)
