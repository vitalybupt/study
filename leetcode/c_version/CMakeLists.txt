cmake_minimum_required(VERSION 2.8)

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

add_executable(validnum src/validNumber.c)
target_compile_options(validnum PUBLIC -O0 -g  --std=gnu99)

add_executable(sortArray src/912_sortArray.c)
target_compile_options(sortArray PUBLIC -O0 -g  --std=gnu99)

add_executable(sortList src/148_sortList.c)
target_compile_options(sortList PUBLIC -O0 -g  --std=gnu99)

add_executable(jumpGame src/55_jumpGame.c)
target_compile_options(jumpGame PUBLIC -O0 -g  --std=gnu99)

add_executable(maxProfit src/121_maxProfit.c)
target_compile_options(maxProfit PUBLIC -O0 -g  --std=gnu99)

add_executable(maxProfit2 src/122_maxProfit.c)
target_compile_options(maxProfit2 PUBLIC -O0 -g  --std=gnu99)

add_executable(gasStation src/134_gasStation.c)
target_compile_options(gasStation PUBLIC -O0 -g  --std=gnu99)

add_executable(recoverTree src/99_recoverTree.c)
target_compile_options(recoverTree PUBLIC -O0 -g  --std=gnu99)

add_executable(containerWithWater src/11_containerWithWater.c)
target_compile_options(containerWithWater PUBLIC -O0 -g  --std=gnu99)

add_executable(longestCommonPrefix src/14_longestCommonPrefix.c)
target_compile_options(longestCommonPrefix  PUBLIC -O0 -g -std=gnu99)

add_executable(zigzagConversion src/6_zigzagConversion.c)
target_compile_options(zigzagConversion PUBLIC -O0 -g  --std=gnu99)
