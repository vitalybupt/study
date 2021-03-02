/*
  计算对齐后的长度：
  x 是指定的长度
  a 是希望对齐的类型的长度
  返回按 a 对齐后的长度
  按对齐后的长度分配内存以提高性能

  例子：
  每个 obj 需要的长度是5个字节，希望按照4个比特对齐，
  那么计算后的长度为8,每个 obj 实际分配8个字节
  ALIGN(5, 4) == 8
 */
#define ALIGN(x, a) _ALIGN(x, (typeof(x))((a)-1))
#define _ALIGN(x, mask) (((x) + (mask)) & ~(mask))
