#include <vector>
#include <bits/stdc++.h>

using std::vector;

class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
      std::sort(nums.begin(), nums.end());
      int ret = nums[0] + nums[1] + nums.back();
      for(int i = 0; i < nums.size() - 2; ++i) {
	int j = i+1; int k = nums.size() - 1;
	while(j < k) {
	  if(abs(nums[i] + nums[j] + nums[k] - target) < abs(ret - target))
	    ret = nums[i] + nums[j] + nums[k];
	  if(nums[i] + nums[j] + nums[k] < target) j++;
	  else k--;
	}
      }
      return ret;
    }
};

int main() {
  class Solution sol;
  vector<int> input = {1,1,1,1};
  sol.threeSumClosest(input, -100);
  return 0;
}
