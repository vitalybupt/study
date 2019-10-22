#include <iostream>
#include <string>

using std::string;

class Solution {
public:
    bool isMatch(string s, string p) {
      row = s.length();
      col = p.length();
      
      P = new bool*[row+1];
      for(int i = 0; i < row + 1; i++) {
	P[i] = new bool[col];
      }
      for(int i = 0; i < row + 1; i++) {
	for(int j = 0; j < col + 1; j++) {
	  P[i][j] = false;
	}
      }
      P[0][0] = true;

      for(int j = 1; j < col + 1; j++) 
	if(p[j-1] == '*' && P[0][j-1] == true)
	  P[0][j] = true;
      
      for(int i = 1; i < row + 1; i++) {
	bool subStrMatch = false;
	for(int j = 1; j < col + 1; j++) {
	  if(p[j-1] == s[i-1] && P[i-1][j-1] == true) {
	    P[i][j] = true; subStrMatch = true; continue;
	  } else if(p[j-1] == '-' && P[i-1][j-1] == true) {
	    P[i][j] = true; subStrMatch = true; continue;
	  } else if(p[j-1] == '*' && P[i-1][j] == true) {
	    P[i][j] = true; subStrMatch = true; continue;
	  }
	}
	if(subStrMatch == false) {cleanup(); return false;}
      }
      return P[row][col];
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
  string  input = "ab";
  string pattern = "a*";
  bool ret = sol.isMatch(input, pattern);
  std::cout << (ret == true ? "match" : "not match") << std::endl;
  return 0;
}





