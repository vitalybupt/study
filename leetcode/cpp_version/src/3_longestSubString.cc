#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // table store pos of each character in cur substring
        vector<int> p_table(26, -1);
        // store the first character of cur substring
        int head = -1;
        int len = 0; int max = 0; int cur_pos = 0;
	while(s[cur_pos] == ' ') { ++cur_pos;}

	if(cur_pos == s.size()) return 0;
        for(; cur_pos < s.size(); cur_pos++) {
            // calculate the index of input character in pos table
            int p_index = s[cur_pos] - 'a';
            if(head == -1 ) head = p_index; // first input character
            if(p_table[p_index] == -1) {
                /* no conflict in cur substring
                    store index of input character
                    expand cur substring length
                */
                p_table[p_index] = cur_pos; 
                len ++;
            } else {
                /* conflict in cur substring
                    - update head of substring to the next character
                    of cur substring
                    - update max length if needed
                    - update cur substring lengh as cur input pos minus
                    previous pos of the input character
                    - update pos of input characterd
                */
                int prev_pos = p_table[p_index];
                head = s[prev_pos+1] - 'a';
                if(len > max) max = len;
                len = cur_pos - prev_pos;
                p_table[p_index] = cur_pos;
            }
        }
        return max;
        return 0;
    }
};

int main() {
  class Solution sol;
  sol.lengthOfLongestSubstring(" ");
  return 0;
}
