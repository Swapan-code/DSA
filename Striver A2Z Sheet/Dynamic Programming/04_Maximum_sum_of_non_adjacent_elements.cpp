#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &nums)
  {
    if (n == 0)
      return nums[0];
    if (n == 1)
      return max(nums[0], nums[1]);

    int take = nums[n] + helperF(n - 2, nums);
    int dontTake = helperF(n - 1, nums);
    return max(take, dontTake);
  }

public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    return helperF(n - 1, nums);
  }
};

// Approach 2: Memoization
// Time = O(n), Space = O(n) + O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &nums, vector<int> &dp)
  {
    if (n == 0)
      return nums[0];
    if (n == 1)
      return max(nums[0], nums[1]);
    if (dp[n] != -1)
      return dp[n];

    int take = nums[n] + helperF(n - 2, nums, dp);
    int dontTake = helperF(n - 1, nums, dp);
    return dp[n] = max(take, dontTake);
  }

public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    vector<int> dp(n, -1);
    return helperF(n - 1, nums, dp);
  }
};

// Approach 3: Tabulation
// Time = O(n), Space = O(n)
class Solution
{
public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    if (n == 1)
      return nums[0];
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++)
    {
      dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[n - 1];
  }
};

// Approach 4: Space Optimization
// Time = O(n), Space = O(1)
class Solution
{
public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    if (n == 1)
      return nums[0];
    int prev2 = nums[0];
    int prev1 = max(nums[0], nums[1]);

    for (int i = 2; i < n; i++)
    {
      int curr = max(prev1, prev2 + nums[i]);
      prev2 = prev1;
      prev1 = curr;
    }

    return prev1;
  }
};

// Version 2: Negative numbers are allowed in the array

// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &nums)
  {
    if (n == 0)
      return max(0, nums[0]);
    if (n == 1)
      return max({0, nums[0], nums[1]});

    int take = nums[n] + helperF(n - 2, nums);
    int dontTake = helperF(n - 1, nums);
    return max(take, dontTake);
  }

public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    return helperF(n - 1, nums);
  }
};

// Approach 2: Memoization
// Time = O(n), Space = O(n) + O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &nums, vector<int> &dp)
  {
    if (n == 0)
      return max(0, nums[0]);
    if (n == 1)
      return max({0, nums[0], nums[1]});
    if (dp[n] != -1)
      return dp[n];

    int take = nums[n] + helperF(n - 2, nums, dp);
    int dontTake = helperF(n - 1, nums, dp);
    return dp[n] = max(take, dontTake);
  }

public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    vector<int> dp(n, -1);
    return helperF(n - 1, nums, dp);
  }
};

// Approach 3: Tabulation
// Time = O(n), Space = O(n)
class Solution
{
public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    if (n == 1)
      return max(0, nums[0]);
    vector<int> dp(n);
    dp[0] = max(0, nums[0]);
    dp[1] = max({0, nums[0], nums[1]});

    for (int i = 2; i < n; i++)
    {
      dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[n - 1];
  }
};

// Approach 4: Space Optimization
// Time = O(n), Space = O(1)
class Solution
{
public:
  int nonAdjacent(vector<int> &nums)
  {
    int n = nums.size();
    if (n == 1)
      return max(0, nums[0]);
    int prev2 = max(0, nums[0]);
    int prev1 = max({0, nums[0], nums[1]});

    for (int i = 2; i < n; i++)
    {
      int curr = max(prev1, prev2 + nums[i]);
      prev2 = prev1;
      prev1 = curr;
    }

    return prev1;
  }
};

// Version 3: Negative numbers are allowed in the array and at least one element must be selected
// That is if all elements are negative, we have to select the maximum element from the array
