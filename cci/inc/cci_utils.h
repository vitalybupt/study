#ifndef CCI_UTILS_H
#define CCI_UTILS_H

#ifdef DEBUG
#define dbg_printf(...) fprintf(stderr, __VA_ARGS__)
#else
#define dbg_printf(...) do{} while(0)
#endif
#define max(x,y)				\
      __extension__ ({ __typeof__ (x) _x = (x);	\
      __typeof__ (y) _y = (y);			\
      _x > _y ? _x : _y; })
#endif
