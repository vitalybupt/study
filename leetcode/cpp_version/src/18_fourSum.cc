#include <bits/stdc++.h>
#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
      int low = 0; int high = nums.size() - 1;
      vector<vector<int>> ret;
      int forward = 1;
      if(high < 3) return ret;
      std::sort(nums.begin(), nums.end());
      while(low < high) {
	twoSum(nums, low, high, target, ret);
	int prevLow = low;
	while(low < high && nums[low] == nums[++low]) continue;
	if(low < high)
	  twoSum(nums, low, high, target, ret);
	while(prevLow < high && nums[high] == nums[--high]) continue;
	if(prevLow < high)
	  twoSum(nums, prevLow, high, target, ret);
      }
      return ret;
    }
private:
  void twoSum(vector<int>& nums, int low, int high, int target, vector<vector<int>>& ret) {
    int i = low +1; int j = high -1;
    while(i < j) {
      if(nums[low] + nums[i] + nums[j] + nums[high] == target) {
	vector<int> tmp = {nums[low], nums[i], nums[j], nums[high]};
	ret.push_back(tmp);
	while(i < j && nums[i] == nums[++i]) continue;
	while(i < j && nums[j] == nums[--j]) continue;
      } else if(nums[low] + nums[i] + nums[j] + nums[high] < target) {
	while(i < j && nums[i] == nums[++i]) continue;
      } else {
	while(i < j && nums[j] == nums[--j]) continue;
      }
    }
    return;    
  }
};

int main() {
  vector<int> input = {-5,-4,-3,-2,-1,0,0,1,2,3,4,5};
  class Solution sol;
  vector<vector<int>> ret = sol.fourSum(input, 0);
  for(vector<int>& sum : ret) {
    std::cout << "ret vector: ";
    for(vector<int>::iterator it = sum.begin(); it != sum.end(); it++) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
