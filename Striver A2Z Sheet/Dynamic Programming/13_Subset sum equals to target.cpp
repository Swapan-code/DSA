#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
private:
  bool helperF(int i, int j, vector<int> &arr, int target)
  {
    if (j == 0)
      return true;
    if (j < 0 || i < 0)
      return false;

    bool pick = helperF(i - 1, j - arr[i], arr, target);
    bool skip = helperF(i - 1, j, arr, target);
    return pick || skip;
  }

public:
  bool isSubsetSum(vector<int> arr, int target)
  {
    if (target == 0)
      return true;
    int n = arr.size();
    return helperF(n - 1, target, arr, target);
  }
};

// Approach 2: Recursion + Memoization
// Time = O(n*target), Space = O(n*target) + O(n) (recursion stack)
class Solution
{
private:
  bool helperF(int i, int j, vector<int> &arr, int target, vector<vector<int>> &dp)
  {
    if (j == 0)
      return true;
    if (j < 0 || i < 0)
      return false;

    if (dp[i][j] != -1)
      return dp[i][j];
    bool pick = helperF(i - 1, j - arr[i], arr, target, dp);
    bool skip = helperF(i - 1, j, arr, target, dp);
    return dp[i][j] = pick || skip;
  }

public:
  bool isSubsetSum(vector<int> arr, int target)
  {
    if (target == 0)
      return true;
    int n = arr.size();
    vector<vector<int>> dp(n, vector<int>(target + 1, -1));
    return helperF(n - 1, target, arr, target, dp);
  }
};

// Approach 3: Tabulation
// Time = O(n*target), Space = O(n*target)
class Solution
{
public:
  bool isSubsetSum(vector<int> arr, int target)
  {
    if (target == 0)
      return true;
    int n = arr.size();
    vector<vector<bool>> dp(n, vector<bool>(target + 1, 0));
    if (arr[0] <= target)
      dp[0][arr[0]] = 1;
    for (int i = 0; i < n; i++)
      dp[i][0] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j <= target; j++)
      {
        bool pick = (j - arr[i] >= 0) ? dp[i - 1][j - arr[i]] : false;
        bool skip = dp[i - 1][j];

        dp[i][j] = pick || skip;
      }
    }

    return dp[n - 1][target];
  }
};

// Approach 4: Space Optimization
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
};

// Version 2: Negative numbers are allowed in the array and target can be negative as well
// Time = O(n*(posSum - negSum)), Space = O(posSum - negSum)
class Solution
{
public:
  bool isSubsetSum(vector<int> arr, int target)
  {
    if (target == 0)
      return true;
    int n = arr.size();
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

    int offset = abs(negSum);
    int size = posSum - negSum;
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
};