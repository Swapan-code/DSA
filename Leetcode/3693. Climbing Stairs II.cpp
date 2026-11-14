#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(3^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &costs)
  {
    if (n == 0)
      return 0;

    int oneJump = helperF(n - 1, costs) + 1;
    int twoJump = n >= 2 ? helperF(n - 2, costs) + 4 : INT_MAX;
    int threeJump = n >= 3 ? helperF(n - 3, costs) + 9 : INT_MAX;

    return costs[n - 1] + min({oneJump, twoJump, threeJump});
  }

public:
  int climbStairs(int n, vector<int> &costs)
  {
    return helperF(n, costs);
  }
};

// Approach 2: Memoization
// Time = O(n), Space = O(n) + O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &costs, vector<int> &dp)
  {
    if (n == 0)
      return 0;
    if (dp[n] != -1)
      return dp[n];

    int oneJump = helperF(n - 1, costs, dp) + 1;
    int twoJump = n >= 2 ? helperF(n - 2, costs, dp) + 4 : INT_MAX;
    int threeJump = n >= 3 ? helperF(n - 3, costs, dp) + 9 : INT_MAX;

    return dp[n] = costs[n - 1] + min({oneJump, twoJump, threeJump});
  }

public:
  int climbStairs(int n, vector<int> &costs)
  {
    vector<int> dp(n + 1, -1);
    return helperF(n, costs, dp);
  }
};

// Approach 3: Tabulation
// Time = O(n), Space = O(n)
class Solution
{
public:
  int climbStairs(int n, vector<int> &costs)
  {
    if (n == 1)
      return 1 + costs[0];
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1 + costs[0];
    dp[2] = costs[1] + min(1 + dp[1], 4);

    for (int i = 3; i <= n; i++)
    {
      dp[i] = costs[i - 1] +
              min({dp[i - 1] + 1, dp[i - 2] + 4, dp[i - 3] + 9});
    }

    return dp[n];
  }
};

// Approach 4: Space Optimization
// Time = O(n), Space = O(1)
class Solution
{
public:
  int climbStairs(int n, vector<int> &costs)
  {
    if (n == 1)
      return 1 + costs[0];
    if (n == 2)
      return costs[1] + min(2 + costs[0], 4);

    int prev3 = 0;
    int prev2 = 1 + costs[0];
    int prev1 = costs[1] + min(2 + costs[0], 4);

    for (int i = 3; i <= n; i++)
    {
      int curr = costs[i - 1] + min({prev1 + 1, prev2 + 4, prev3 + 9});

      prev3 = prev2;
      prev2 = prev1;
      prev1 = curr;
    }

    return prev1;
  }
};