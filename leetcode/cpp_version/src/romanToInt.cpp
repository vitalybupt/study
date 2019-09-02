// Symbol       Value
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000

class Solution {
public:
  int romanToInt(string s) {
    int val = 0; int prev_val = 0;
    int count = 0;
    for(int i = 0; i < s.size(); ++i) {
      switch(s[i]) {
      case 'I':
	val = 1;
	break;
      case 'V':
	val = 5;
	break;
      case 'X':
	val =10;
	break;
      case 'L':
	val = 50;
	break;
      case 'C':
	val = 100;
	break;
      case 'D':
	val = 500;
	break;
      case 'M':
	val = 1000;
	break;
      default:
	break;
      }
      count += val;
      if(val > prev_val)
	count -= 2*prev_val;
      prev_val = val;
    }
    return count;        
  }
};

int main() {
}
