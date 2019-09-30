#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
      int first, second = 0;
      vector<int> ret;
      for(first = 0; first <  nums.size() - 1; ++first) {
	second = first + 1;
	for (;second < nums.size(); ++second) {
	  if(nums[first] + nums[second] == target) {
	    ret.push_back(first);
	    ret.push_back(second);
	    return ret;
	  }
	}
      }
      return ret;
   }
private:
  void swap(vector<int>& nums, int pos1, int pos2) {
    int tmp = nums[pos1];
    nums[pos1] = nums[pos2];
    nums[pos2] = tmp;
    return;
  }
  int partition(vector<int>&nums, int low, int high) {
    int pivot = nums[high-1];
    int scanner = low;
    int boundary = low - 1;
    while(scanner < high -1) {
      if(nums[scanner] <= pivot)
	swap(nums, ++boundary, scanner);
      scanner++;
    }
    swap(nums, ++boundary, high-1);
    return boundary;
  }
  void sortIter(vector<int>& nums, int low, int high) {
    if(low >= high) return;
    int boundary = partition(nums, low, high);
    sortIter(nums,low, boundary-1);
    sortIter(nums,boundary+1, high);
    return;
  }

private:
  unordered_set<int> set;
};

int main() {
  //static const int tmp[] = {217,231,523,52,547,243,648,509,415,149,689,710,265,187,370,56,977,182,400,329,471,805,955,989,255,766,38,566,79,843,295,229,988,108,781,619,704,542,335,307,359,907,727,959,161,699,123,650,147,459,657,188,304,268,405,685,620,721,351,570,899,60,388,771,24,659,425,440,508,373,32,645,409,272,356,175,533,740,370,152,34,510,745,251,227,494,258,527,817,773,178,194,860,387,627,851,449,736,15,212,529,950,316,28,65,484,968,63,4,643,795,669,203,677,139,636,289,555,430,849,150,493,301,377,240,873,965,441,230,349,447,470};
  static const int tmp[] = {3,2,4};
  vector<int> given(tmp, tmp + sizeof(tmp)/sizeof(tmp[0]));
  int target = 6;
  class Solution cal;
  vector<int> ret = cal.twoSum(given, target);
  if(ret.empty())
    std::cout << "not find solution" << endl;
  else
    std::cout << "first element " << ret[0] << " second is " << ret[1] << endl;


  // ret = cal.twoSum(given, 718);
  // if(ret.empty())
  //   std::cout << "not find solution" << endl;
  // else
  //   std::cout << "first element " << ret[0] << " second is " << ret[1] << endl;

  return 0;
}
