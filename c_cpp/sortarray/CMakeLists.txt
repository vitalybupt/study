set(HDRS
  include/sortarray.h
  )

add_library(sortarray SHARED src/sortarray.c)
target_compile_options(sortarray PUBLIC -Og -g -Wall -Werror -Wno-unused --std=gnu99 -Wmissing-declarations)
target_include_directories(sortarray PUBLIC include/)

add_executable(demo_array src/main.c ${HDRS})
target_compile_options(demo_array PUBLIC -Og -g -Wall -Werror -Wno-unused --std=gnu99 -Wmissing-declarations)
target_include_directories(demo_array PUBLIC include/)

target_link_libraries(demo_array LINK_PUBLIC sortarray)

