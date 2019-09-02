#include <vector>
#include <string>
#include <iostream>
using std::vector;
using std::string;

class Solution {
public:
    vector<string> generateParenthesis(int n) {
      vector<string> ret;
      generate(ret, "", 0, 0, n);
      for(string const &val : ret) {
	std::cout << val << std::endl;
      }
      return ret;
    }
private:
  void generate(vector<string> ret, string input, int open, int close, int limit) {
    if(open >=  limit && close >= limit) { ret.push_back(input); std::cout<<input<<std::endl; return;}
    if(open < limit) generate(ret, input + "(", open+1, close, limit);
    if(close <limit) generate(ret, input +")", open, close+1, limit);
    return;
  }
};

int main() {
  class Solution cal;
  cal.generateParenthesis(3);
}
