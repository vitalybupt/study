#include <string>

using std::string;

// Symbol       Value
// I             1
// V             5
// X             10
// L             50
// C             100
// D             500
// M             1000

string intToRoman(int num) {
  string table[4][10] = {{"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"},
			 {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"},
			 {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"},
			 {"", "M", "MM", "MMM"}
			 
  };
  string ret;
  int count = 0;
  while(num > 0) {
    int tmp = num % 10;
    ret = table[count][tmp] + ret;
    num /= 10;
    count ++;
  }
  return ret;
}
int main() {
  
}
