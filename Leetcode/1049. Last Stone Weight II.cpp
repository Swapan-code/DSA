// Same to problem: Partition a set into two subsets with minimum absolute sum difference (Striver -> DP)
#include <bits/stdc++.h>
using namespace std;

// Approach 1: DP
// Time = O(n*sum), Space = O(n*sum)
class Solution
{
public:
  int lastStoneWeightII(vector<int> &stones)
  {
    int n = stones.size();
    int sum = 0;
    for (auto i : stones)
      sum += i;
    vector<vector<bool>> dp(n, vector<bool>(sum + 1, 0));
    dp[0][stones[0]] = 1;
    for (int i = 0; i < n; i++)
      dp[i][0] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j <= sum; j++)
      {
        bool pick = (j - stones[i] >= 0) ? dp[i - 1][j - stones[i]] : false;
        bool skip = dp[i - 1][j];

        dp[i][j] = pick || skip;
      }
    }

    int ans = 1e6;
    for (int j = 0; j <= sum / 2; j++)
    {
      if (dp[n - 1][j])
      {
        ans = min(ans, 2 * abs(j - sum / 2) + (sum & 1));
      }
    }

    return ans;
  }
};

// Approach 2: Space Optimisation
// Time = O(n*sum), Space = O(sum)
class Solution
{
public:
  int lastStoneWeightII(vector<int> &stones)
  {
    int n = stones.size();
    int sum = 0;
    for (auto i : stones)
      sum += i;
    vector<bool> prev(sum + 1, 0);
    vector<bool> curr(sum + 1, 0);
    prev[stones[0]] = 1;
    prev[0] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= sum; j++)
      {
        bool pick = (j - stones[i] >= 0) ? prev[j - stones[i]] : false;
        bool skip = prev[j];

        curr[j] = pick || skip;
      }
      swap(prev, curr);
    }

    int ans = sum;
    for (int j = 0; j <= sum / 2; j++)
    {
      if (prev[j])
      {
        ans = min(ans, 2 * abs(j - sum / 2) + (sum & 1));
      }
    }

    return ans;
  }
};