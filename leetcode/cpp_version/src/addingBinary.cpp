#include <string>
#include <iostream>

using std::string;

class Solution {
public:
  static string addBinary(string a, string b) {
    string res;
    int i = a.size() - 1, j = b.size() -1, cur = 0;
    while(i + j + cur) {
      cur += (i ? a[i--] -'0' : 0) + (j ? b[j--] -'0' : 0);
      res = char(cur%2 + '0') + res;
      cur /= 2;
    }
    return res;
  }
};

int main() {
  std::cout << Solution::addBinary("110", "110") << std::endl;
  return 0;
}
