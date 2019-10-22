#include <iostream>
#include <string>

using std::string;

class Solution {
public:
    bool isMatch(string s, string p) {
      int match = false;
      row = s.length();
      col = p.length();
      
      P = new bool*[s.length()];
      for(int i = 0; i < s.length(); i++) {
	P[i] = new bool[p.length()];
      }
      for(int i = 0; i < s.length(); i++) {
	for(int j = 0; j < p.length(); j++) {
	  P[i][j] = false;
	}
      }
      P[0][0] = true;

      for(int i = 0; i < s.length(); i++) {
	bool subStrMatch = false;
	for(int j = 0; j < p.length(); j++) {
	  if(p[j] == s[i] && P[i-1][j-1] == true) {
	    P[i][j] = true; subStrMatch = true; continue;
	  } else if(p[j] == '-' && P[i-1][j-1] == true) {
	    P[i][j] = true; subStrMatch = true; continue;
	  } else if(p[j] == '*' && P[i-1][j] == true) {
	    P[i][j] = true; subStrMatch = true; continue;
	  }
	}
	if(subStrMatch == false) {cleanup(); return false;}
      }
      return match;
    }

private:
  void cleanup() {
    for(int i = 0; i < row; i++) {
      delete []P[i];
    }
    delete []P;
    return;
  }

  bool **P;
  int row; int col;
  
};

int main() {
  class Solution sol;
  string  input = "aa";
  string pattern = "a";
  bool ret = sol.isMatch(input, pattern);
  //std::cout << ret ? "match" : "not match" << std::endl;
  return 0;
}
