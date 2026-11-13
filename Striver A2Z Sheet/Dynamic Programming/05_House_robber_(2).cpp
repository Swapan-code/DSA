#include <bits/stdc++.h>
using namespace std;

// Directly doing Version 2: Negative numbers are also allowed in the array

// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int s, int e, vector<int> &nums)
  {
    if (e == s)
      return max(0, nums[s]);
    if (e == s + 1)
      return max({0, nums[s], nums[s + 1]});

    int take = nums[e] + helperF(s, e - 2, nums);
    int dontTake = helperF(s, e - 1, nums);
    return max(take, dontTake);
  }

public:
  int houseRobber(vector<int> &money)
  {
    int n = money.size();
    if (n == 1)
      return max(0, money[0]);
    return max(helperF(0, n - 2, money), helperF(1, n - 1, money));
  }
};

// Approach 2: Memoization
// Time = O(n), Space = O(n) + O(n) (recursion stack)
class Solution
{
private:
  int helperF(int s, int e, vector<int> &nums, vector<int> &dp)
  {
    if (e == s)
      return max(0, nums[s]);
    if (e == s + 1)
      return max({0, nums[s], nums[s + 1]});
    if (dp[e] != -1)
      return dp[e];

    int take = nums[e] + helperF(s, e - 2, nums, dp);
    int dontTake = helperF(s, e - 1, nums, dp);
    return dp[e] = max(take, dontTake);
  }

public:
  int houseRobber(vector<int> &money)
  {
    int n = money.size();
    if (n == 1)
      return max(0, money[0]);

    vector<int> dp1(n, -1), dp2(n, -1);
    int choice1 = helperF(0, n - 2, money, dp1);
    int choice2 = helperF(1, n - 1, money, dp2);
    return max(choice1, choice2);
  }
};

// Approach 3: Tabulation
// Time = O(n), Space = O(n)
class Solution
{
private:
  int helperF(int s, int e, vector<int> &nums, vector<int> &dp)
  {
    if (e == s)
      return max(0, nums[s]);
    dp[s] = max(0, nums[s]);
    dp[s + 1] = max({0, nums[s], nums[s + 1]});

    for (int i = s + 2; i <= e; i++)
    {
      dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }

    return dp[e];
  }

public:
  int houseRobber(vector<int> &money)
  {
    int n = money.size();
    if (n == 1)
      return max(0, money[0]);

    vector<int> dp(n);
    int choice1 = helperF(0, n - 2, money, dp);
    int choice2 = helperF(1, n - 1, money, dp);
    return max(choice1, choice2);
  }
};

// Approach 4: Space Optimization
// Time = O(n), Space = O(1)
class Solution
{
private:
  int helperF(int s, int e, vector<int> &nums)
  {
    if (e == s)
      return max(0, nums[s]);
    int prev2 = max(0, nums[s]);
    int prev1 = max({0, nums[s], nums[s + 1]});

    for (int i = s + 2; i <= e; i++)
    {
      int curr = max(prev1, prev2 + nums[i]);
      prev2 = prev1;
      prev1 = curr;
    }

    return prev1;
  }

public:
  int houseRobber(vector<int> &money)
  {
    int n = money.size();
    if (n == 1)
      return max(0, money[0]);

    int choice1 = helperF(0, n - 2, money);
    int choice2 = helperF(1, n - 1, money);
    return max(choice1, choice2);
  }
};
