#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <utility>

using std::vector;
using std::string;
using std::unordered_map;
using std::pair;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
      vector<vector<string>> ret;
      unordered_map<string, vector<string>> mp;
      for(string const & str : strs) {
	mp[sortString(str)].push_back(str);
      }
      for(auto const & val : mp) {
	ret.push_back(val.second);
      }
      return ret;
    }
private:
  string sortString(string str) {
    char table[26] = {0};
    string ret;
    for(int i = 0; i < str.length(); ++i) {
      int pos = str[i] - 'a';
      table[pos]++;
    }
    for(int i = 0; i < 26; ++i) {
      for(int j = 0; j < table[i]; ++j) {
	ret.push_back(i+'a');
      }
    }
    return ret;
  }
};

int main() {
  class Solution  cal;
  vector<string> input;
  input.push_back("aedc");
  cal.groupAnagrams(input);
  return 0;
}
