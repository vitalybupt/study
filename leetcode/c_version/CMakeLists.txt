add_executable(3sum src/3sum.c)
target_compile_options(3sum PUBLIC -Os  --std=gnu99)

add_executable(merge src/mergeintervals.c)
target_compile_options(merge PUBLIC -O0 -g  --std=gnu99)

add_executable(insert src/insertintervals.c)
target_compile_options(insert PUBLIC -O0 -g  --std=gnu99)

add_executable(validateBST src/validateBST.c)
target_compile_options(validateBST PUBLIC -O0 -g  --std=gnu99)

add_executable(traverseBST src/traverseBST.c)
target_compile_options(traverseBST PUBLIC -O0 -g  --std=gnu99)

add_executable(isPalindrome src/isPalindrome.c)
target_compile_options(isPalindrome PUBLIC -O0 -g  --std=gnu99)

add_executable(wordladder src/wordladder.c)
target_compile_options(wordladder PUBLIC -pg  --std=gnu99)
