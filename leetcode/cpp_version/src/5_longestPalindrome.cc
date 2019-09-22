#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Solution {
public:
    string longestPalindrome(string s) {
      int maxLength = 0;
      int startPos = 0;
      vector<int> dict1;
      vector<int> dict2;
      int curCenter = 0;
      int curDiameter = 0;

      /*
	cur diameter is odd:          cur diameter is even:
	e a b f b a e                 e a b f f b a e
          m   c   i r                     m c   i   r
	mirror = 2c-i;	              mirror = 2c-i+1;
	
	expand 1:                      	expand 2:
	l = mirror-dict1[mirror]         l = mirror-dict2[mirror]

	r = c + (diameter/2); rad = min(mirror-l, r-i);
      */
      for(int index = 0; index < s.length(); index ++) {
	int pos1 = 0; int pos2 = 0; int mirror = 0;
	if(curDiameter%2 == 0) {
	  mirror = 2*curCenter - index + 1; 
	} else {
	  mirror = 2*curCenter - index; 
	}
	int l = mirror - dict1[mirror];
	int r = curCenter + (curDiameter/2);
	int rad = (mirror - l < r - index ? mirror - l : r - index);
	int length1 = expand(s, index - rad , index + rad, &pos1);
	l =  mirror - dict2[mirror];
	rad = (mirror - l < r - index ? mirror - l : r - index);
	int length2 = expand(s, index - rad + 1, index + rad, &pos2);
	dict1.push_back(length1/2);dict2.push_back(length2/2);
	if(length1 > length2) {
	  if(length1 > maxLength) {
	    maxLength = length1;
	    startPos = pos1;
	  }
	} else {
	  if(length2> maxLength) {
	    maxLength = length2;
	    startPos = pos2;
	  }
	}
      }
      for(const int & rad : dict1) {
	std::cout << rad << std::endl;
      }
      for(const int & rad : dict2) {
	std::cout << rad << std::endl;
      }
      return s.substr(startPos, maxLength);
    }
private:
  int expand(string s, int backward, int forward, int* pos) {
    while(backward >= 0 && forward < s.length() && s[backward] == s[forward]) {
      backward--;
      forward++;
    }
    *pos = backward+1;
    return (forward - backward - 1);
  }
};

int main () {
  class Solution sol;
  string ret = sol.longestPalindrome("cbba");
  std::cout << ret << std::endl;
  return 0;
}
