#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
      int length1 = strs[0].length()/4 + (strs[0].length()%4 > 0 ? 1 : 0);
      std::cout << length1 << std::endl;
      int length1 = strs[0].length()/4 + (strs[0].length()%4 > 0 ? 1 : 0);
      std::cout << length1 << std::endl;
    }
};

int main() {
  class Solution sol;
  vector<string> input ={"flower", "flow"};
  sol.longestCommonPrefix(input);
  return 0;
}
