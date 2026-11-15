// Similar to problem: Subset Sum Equal to Target (Striver -> DP)

#include <bits/stdc++.h>
using namespace std;

// arr[i] >= 0

// Approach 1: DP
// Time = O(n*target), Space = O(n*target)
class Solution
{
public:
  int perfectSum(vector<int> &arr, int K)
  {
    int n = arr.size();
    vector<vector<long long>> dp(n, vector<long long>(K + 1, 0));
    long long mod = 1e9 + 7;

    // Take first
    if (arr[0] <= K)
      dp[0][arr[0]]++;

    // Skip first
    dp[0][0]++;

    // If first element is 0 -> dp[0][0] becomes 2 which is needed

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= K; j++)
      {
        long long pick = (j - arr[i] >= 0) ? dp[i - 1][j - arr[i]] : 0;
        long long skip = dp[i - 1][j];

        dp[i][j] = (pick + skip) % mod;
      }
    }

    return dp[n - 1][K];
  }
};

// Approach 2: Space Optimization
// Time = O(n*target), Space = O(target)
class Solution
{
public:
  int perfectSum(vector<int> &arr, int K)
  {
    int n = arr.size();
    vector<long long> prev(K + 1, 0);
    vector<long long> curr(K + 1, 0);
    long long mod = 1e9 + 7;

    // Take first
    if (arr[0] <= K)
      prev[arr[0]]++;

    // Skip first
    prev[0]++;

    // If first element is 0 -> dp[0][0] becomes 2 which is needed

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= K; j++)
      {
        long long pick = (j - arr[i] >= 0) ? prev[j - arr[i]] : 0;
        long long skip = prev[j];

        curr[j] = (pick + skip) % mod;
      }
      swap(prev, curr);
    }

    return prev[K];
  }
};