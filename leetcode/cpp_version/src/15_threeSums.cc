#include <iostream>
#include <vector>

using std::vector;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
      vector<vector<int>> ret;
      if(nums.size() < 3) return ret;

      sortIter(nums, 0, nums.size() - 1);

      for(int i = 0; i < nums.size() - 2; skip(nums, i, true)) {
	int j = i + 1; int k = nums.size() -1;
	int target = -nums[i];
	while(j < k) {
	  if(nums[j] + nums[k] < target) {
	    skip(nums, j, true);
	    continue;
	  } else if(nums[j] + nums[k] > target) {
	    skip(nums, k, false);
	  } else {
	    vector<int> tmp = {nums[i], nums[j], nums[k]};
	    ret.push_back(tmp);
	    skip(nums,j, true);
	    continue;
	  }
	}
      }
      return ret;
    }
private:
  void skip(vector<int>& nums, int& p, bool forward) {
    if(forward) {
      int r = nums.size() - 1;
    
      while(p < r) {
	if(nums[p] != nums[p+1]) {
	  ++p;
	  return;
	}
	++p;
      }
      ++p;
    } else {
      while(p > 0) {
	if(nums[p-1] != nums[p]) {
	  --p;
	  return;
	}
	--p;
      }
      --p;
    }
    return;
  }
  void swap(vector<int>& nums, int p1, int p2) {
    int tmp = nums[p1];
    nums[p1] = nums[p2];
    nums[p2] = tmp;
    return;
  }
  void sortIter(vector<int>& nums, int low, int high) {
    if(low >= high) return;
    int pivot = nums[high];
    int scanner = low; int boundary = low-1;
    while(scanner < high) {
      if(nums[scanner] < pivot) swap(nums, scanner, ++boundary);
      scanner++;
    }
    swap(nums, ++boundary, high);
    sortIter(nums, low, boundary-1);
    sortIter(nums, boundary+1, high);
    return;
  }
};

int main() {
  vector<int> input = {-1, 0, 1, 2, -1, -4};
  class Solution sol;
  sol.threeSum(input);
  return 0;
}
