#include <bits/stdc++.h>
using namespace std;

// Approach 1: DP
// Time = O(n*W), Space = O(n*W)
class Solution
{
public:
  int knapsack01(vector<int> &wt, vector<int> &val, int n, int W)
  {
    // dp[i][j] = max value using items 0..i with capacity j
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    for (int j = wt[0]; j <= W; j++)
    {
      dp[0][j] = val[0];
    }

    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j <= W; j++)
      {
        int pick = (j >= wt[i]) ? val[i] + dp[i - 1][j - wt[i]] : 0;
        int skip = dp[i - 1][j];
        dp[i][j] = max(pick, skip);
      }
    }

    return dp[n - 1][W];
  }
};

// Approach 2: Space Optimisation
// Time = O(n*W), Space = O(W)
class Solution
{
public:
  int knapsack01(vector<int> &wt, vector<int> &val, int n, int W)
  {
    vector<int> prev(W + 1, 0);
    vector<int> curr(W + 1, 0);

    for (int j = wt[0]; j <= W; j++)
    {
      prev[j] = val[0];
    }

    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j <= W; j++)
      {
        int pick = (j >= wt[i]) ? val[i] + prev[j - wt[i]] : 0;
        int skip = prev[j];
        curr[j] = max(pick, skip);
      }
      swap(prev, curr);
    }

    return prev[W];
  }
};