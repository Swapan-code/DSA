// Similar to problem: Subset Sum Equal to Target (Striver -> DP)

#include <bits/stdc++.h>
using namespace std;

// Time = O(n*target), Space = O(target)
class Solution
{
public:
  bool isSubsetSum(vector<int> arr, int target)
  {
    if (target == 0)
      return true;
    int n = arr.size();
    vector<int> prev(target + 1, 0);
    vector<int> curr(target + 1, 0);
    prev[0] = 1;
    if (arr[0] <= target)
      prev[arr[0]] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= target; j++)
      {
        bool pick = (j - arr[i] >= 0) ? prev[j - arr[i]] : false;
        bool skip = prev[j];

        curr[j] = pick || skip;
      }
      swap(prev, curr);
    }

    return prev[target];
  }

  bool canPartition(vector<int> &nums)
  {
    int sum = 0;
    for (auto i : nums)
      sum += i;

    if (sum & 1)
      return false;
    return isSubsetSum(nums, sum / 2);
  }
};

// Version 2: Negative values are allowed in array and Subsets can be empty
class Solution
{
public:
  bool isSubsetSum(vector<int> arr, int target)
  {
    if (target == 0)
      return true;

    int posSum = 0, negSum = 0;
    for (auto i : arr)
    {
      if (i > 0)
        posSum += i;
      else
        negSum += i;
    }

    if (target < negSum || target > posSum)
      return false;

    int size = posSum - negSum;
    int offset = abs(negSum);
    int n = arr.size();
    vector<int> prev(size + 1, 0);
    vector<int> curr(size + 1, 0);
    prev[offset] = 1;
    if (offset + arr[0] <= size)
      prev[offset + arr[0]] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= size; j++)
      {
        bool pick = (j - arr[i] >= 0 && j - arr[i] <= size) ? prev[j - arr[i]] : false;
        bool skip = prev[j];

        curr[j] = pick || skip;
      }
      swap(prev, curr);
    }

    return prev[target + offset];
  }

  bool canPartition(vector<int> &nums)
  {
    int sum = 0;
    for (auto i : nums)
      sum += i;

    if (sum & 1)
      return false;
    return isSubsetSum(nums, sum / 2);
  }
};

// Version 3: Negative values allowed, both subsets must be non-empty
// Time = O(n * (posSum - negSum)), Space = O(posSum - negSum)
class Solution
{
private:
  // Is there a NON-EMPTY subset of arr[0..m-1] with sum == target?
  bool isSubsetSum(vector<int> &arr, int target, int m)
  {
    int posSum = 0, negSum = 0;
    for (int i = 0; i < m; i++)
    {
      if (arr[i] > 0)
        posSum += arr[i];
      else
        negSum += arr[i];
    }

    if (target < negSum || target > posSum)
      return false;

    int size = posSum - negSum;
    int offset = abs(negSum); // index j means sum (j - offset)

    vector<int> prev(size + 1, 0); // sums of NON-EMPTY subsets so far
    vector<int> curr(size + 1, 0);

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j <= size; j++)
      {
        bool pick = (j - arr[i] >= 0 && j - arr[i] <= size) ? prev[j - arr[i]] : false;
        bool skip = prev[j];

        curr[j] = pick || skip;
      }
      curr[offset + arr[i]] = 1; // arr[i] on its own (starts a new non-empty subset)
      swap(prev, curr);
    }

    return prev[target + offset];
  }

public:
  bool canPartition(vector<int> &nums)
  {
    int n = nums.size();
    int sum = accumulate(nums.begin(), nums.end(), 0);

    if (sum & 1)
      return false;

    // total 0: each half must sum to 0, so look for a non-empty zero-sum
    // subset that leaves the last element out (it ends up in the other half)
    if (sum == 0)
      return isSubsetSum(nums, sum / 2, n - 1);
    else
      return isSubsetSum(nums, sum / 2, n);
  }
};