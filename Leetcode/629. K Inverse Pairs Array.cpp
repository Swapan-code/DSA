#include <bits/stdc++.h>
using namespace std;

// Approach 1: DP
// Time = O(n*k), Space = O(n*k)
class Solution
{
public:
  int kInversePairs(int n, int k)
  {
    long long mod = 1e9 + 7;
    vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, 0));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++)
    {
      long long sum = 0;
      for (int j = 0; j <= k; j++)
      {
        if (j - i + 1 > 0)
        {
          sum -= dp[i - 1][j - i];
        }
        sum += dp[i - 1][j];
        sum = sum % mod;
        if (sum < 0)
          sum += mod;
        dp[i][j] = sum;
      }
    }

    return dp[n][k];
  }
};

// Approach 2: Space Optimization
// Time = O(n*k), Space = O(k)
class Solution
{
public:
  int kInversePairs(int n, int k)
  {
    long long mod = 1e9 + 7;
    vector<long long> prev(k + 1, 0);
    vector<long long> curr(k + 1, 0);
    prev[0] = 1;

    for (int i = 1; i <= n; i++)
    {
      long long sum = 0;
      for (int j = 0; j <= k; j++)
      {
        if (j - i + 1 > 0)
        {
          sum -= prev[j - i];
        }
        sum += prev[j];
        sum = sum % mod;
        if (sum < 0)
          sum += mod;
        curr[j] = sum;
      }
      swap(prev, curr);
    }

    return prev[k];
  }
};