#include <iostream>
#include <limits.h>


class Solution {
public:
    int reverse(int x) {
      int sum = 0; int remain = 0;
      while(x != 0) {
	sum = sum*10 + x%10;
	x = x/10;
      }
      int max = 0x7fffffff;
      return sum > INT_MAX || sum < INT_MIN ? 0 : sum;
    }
};

int main() {
  class Solution sol;
  int ret = sol.reverse(-123);
  std::cout << ret << std::endl;
  return 0;
}
