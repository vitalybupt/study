#include <vector>
#include <string>
#include <iostream>

using std::vector;
using std::string;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
      vector<vector<string>> ret;
      for(string const & str : strs) {
	std::cout << sortString(str) << std::endl;
      }
      return ret;
    }
private:
  int searchStr(string str, int low, int high, char c) {
    if(low > high) return low;
    int mid = (low+high)/2;
    if(str[mid] <= c) {
      low = mid+1;
    } else {
      high = mid -1;
    }
    return searchStr(str, low, high, c);    
  }
  
  void insertString(string& ret, char c) {
    if(ret.length() == 0) {
      ret.push_back(c);
      return;
    }
    int pos = searchStr(ret, 0, ret.length(), c);
    std::cout << ret << " " << pos << std::endl;
    ret.insert(pos, 1,  c);
    return;
  }
  string sortString(string str) {
    string ret;
    for(int i = 0; i < str.length(); ++i) {
      insertString(ret, str[i]);
    }
    return ret;
  }
};

int main() {
  class Solution  cal;
  vector<string> input;
  input.push_back("adc");
  cal.groupAnagrams(input);
  return 0;
}
