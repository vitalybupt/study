f_profiler
##########
测试 IO 的时候 function_profile 的情况。
在测试之前，创建大小为 2G 的 random 文件，然后利用 mmap 将文件映射到内存空间，之后读取。
在读取过程中，使用 function_profile 检查内核函数的使用情况。
创建了多个线程，每个线程独立的处理一个文件，考虑到这些线程共享 vm area，在处理文件时，当 page fault 发生，应该会竞争 mmap_rwsem 锁，从而引起性能下降。而线程越多，应该趋势越明显。

测试脚本::
  测试时，首先创建内容为 random 的 binary 文件，然后调用 f_profile，当程序结束退出后，检查各个 CPU 上的统计信息。
