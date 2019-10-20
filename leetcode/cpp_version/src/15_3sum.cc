#include <vector>
#include <iostream>

using std::vector;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      vector<vector<int>> ret;
      if(nums.size() < 3) return ret;
      quickSort(nums, 0, nums.size());
      for(int i = 0; i < nums.size() - 2; ++i) {
	if(nums[i] == nums[i+1]) continue;
	vector<vector<int>> tmp = twoSum(nums, i+1, 0-nums[i]);
	ret.insert(ret.end(),tmp.begin(), tmp.end());
      }
      return ret;
    }
private:
  vector<vector<int>> twoSum(vector<int>& nums, int low, int target) {
    vector<vector<int>> ret;
    int firstIndex = low-1;
    int secIndex = low;
    int thirdIndex = low + 1;
    while(secIndex < nums.size() - 1) {
      if(nums[secIndex] + nums[thirdIndex] == target) {
	vector<int> tmp = {nums[firstIndex], nums[secIndex], nums[thirdIndex]};
	ret.push_back(tmp);
	secIndex = skipDuplicate(nums, secIndex);
	thirdIndex = secIndex+1;
	continue;
      }
      thirdIndex = skipDuplicate(nums, thirdIndex);
      if(thirdIndex >= nums.size()) {
	secIndex = skipDuplicate(nums, secIndex);
	thirdIndex = secIndex+1;
      }
    }
    return ret;
  }

  void quickSort(vector<int>& nums, int low, int high) {
    if(low >= high) return;
    int pivot = nums[high-1];
    int scanner = low;
    int boundary = low-1;
    while(scanner < high - 1) {
      if(nums[scanner] < pivot) {
	swap(nums, ++boundary, scanner);
      }
      scanner++;
    }
    swap(nums, ++boundary, high-1);
    quickSort(nums, low, boundary - 1);
    quickSort(nums, boundary+1, high);
  }
  void swap(vector<int>&nums, int p1, int p2) {
    int tmp = nums[p1];
    nums[p1] = nums[p2];
    nums[p2] = tmp;
    return;
  }

  int skipDuplicate(vector<int>&nums, int pos) {
    while(pos < nums.size() - 1){
      if(nums[pos] == nums[pos+1]) {
	pos++;
	continue;
      }
      break;
    }
    return pos+1;
  }
};

int main() {
  class Solution sol;
  vector<int> input = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
  sol.threeSum(input);
  return 0;
}
