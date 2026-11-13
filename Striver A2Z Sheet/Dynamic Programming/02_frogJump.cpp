#include <bits/stdc++.h>
using namespace std;
// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &heights)
  {
    if (n == 0)
      return 0;

    int oneJump = helperF(n - 1, heights) + abs(heights[n] - heights[n - 1]);
    int twoJump = INT_MAX;
    if (n > 1)
      twoJump = helperF(n - 2, heights) + abs(heights[n] - heights[n - 2]);
    return min(oneJump, twoJump);
  }

public:
  int frogJump(vector<int> &heights)
  {
    int n = heights.size();
    return helperF(n - 1, heights);
  }
};

// Approach 2: Memoization
// Time = O(n), Space = O(n) (recursion stack + dp array)
class Solution
{
private:
  int helperF(int n, vector<int> &heights, vector<long long> &dp)
  {
    if (n == 0)
      return 0;
    if (dp[n] != -1)
      return dp[n];

    int oneJump = helperF(n - 1, heights, dp) + abs(heights[n] - heights[n - 1]);
    int twoJump = INT_MAX;
    if (n > 1)
      twoJump = helperF(n - 2, heights, dp) + abs(heights[n] - heights[n - 2]);
    return dp[n] = min(oneJump, twoJump);
  }

public:
  int frogJump(vector<int> &heights)
  {
    int n = heights.size();
    vector<long long> dp(n, -1);
    return helperF(n - 1, heights, dp);
  }
};

// Approach 3: Tabulation
// Time = O(n), Space = O(n) (dp array)
class Solution
{
public:
  int frogJump(vector<int> &heights)
  {
    int n = heights.size();
    if (n == 1)
      return 0;
    vector<long long> dp(n, -1);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
      int oneJump = dp[i - 1] + abs(heights[i] - heights[i - 1]);
      int twoJump = INT_MAX;
      if (i > 1)
        twoJump = dp[i - 2] + abs(heights[i] - heights[i - 2]);
      dp[i] = min(oneJump, twoJump);
    }
    return dp[n - 1];
  }
};

// Approach 4: Space Optimization
// Time = O(n), Space = O(1)
class Solution
{
public:
  int frogJump(vector<int> &heights)
  {
    int n = heights.size();
    if (n == 1)
      return 0;
    int prev2 = 0;
    int prev1 = 0;
    for (int i = 1; i < n; i++)
    {
      int oneJump = prev1 + abs(heights[i] - heights[i - 1]);
      int twoJump = INT_MAX;
      if (i > 1)
        twoJump = prev2 + abs(heights[i] - heights[i - 2]);
      int curr = min(oneJump, twoJump);

      prev2 = prev1;
      prev1 = curr;
    }
    return prev1;
  }
};