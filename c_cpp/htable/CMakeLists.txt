add_executable(demo_htable main.c)
target_compile_options(demo_htable PUBLIC -Og -g -Wall -Werror -Wno-unused --std=gnu99 -Wmissing-declarations -I .)
