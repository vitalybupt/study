#include <vector>
#include <iostream>

using std::vector;


class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
      vector<vector<int>> ret;
      vector<int> num;
      generate(ret, 0, nums);
      return ret;
    }
private:
  void generate(vector<vector<int>>& ret, int begin,  vector<int> nums) {
    if( begin >= nums.size() ) {
      ret.push_back(nums);
      return;
    }
    for(int i = begin; i < nums.size(); ++i) {
      swap(nums, begin, i);
      if(begin == 2) {
	std::cout << nums[0] << nums[1] << nums[2] << std::endl;
      }
      generate(ret, begin+1, nums);
      swap(nums, i, begin);
    }
  }

  void swap(vector<int>& nums, int n1, int n2) {
    int tmp = nums[n2];
    nums[n2] = nums[n1];
    nums[n1] = tmp;
    return;
  }
};

int main() {
  vector<int> nums = {1, 2, 3};
  class Solution cal;
  vector<vector<int>> ret = cal.permute(nums);
  for(vector<int> const & v1 : ret) {
    for(int const & data : v1) {
      std::cout << data << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
