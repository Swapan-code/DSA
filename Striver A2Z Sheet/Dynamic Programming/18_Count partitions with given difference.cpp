#include <bits/stdc++.h>
using namespace std;

// Approach 1: DP
// Time = O(n*sum), Space = O(n*sum)
class Solution
{
public:
  int countPartitions(int n, int diff, vector<int> &arr)
  {
    long long mod = 1e9 + 7;
    long long sum = 0;
    for (auto i : arr)
      sum += i;

    if (diff > sum)
      return 0;
    if ((sum - diff) & 1)
      return 0;

    vector<vector<long long>> dp(n, vector<long long>(sum + 1, 0));
    dp[0][0]++;
    dp[0][arr[0]]++;

    for (long long i = 1; i < n; i++)
    {
      for (long long j = 0; j <= sum; j++)
      {
        long long pick = (j - arr[i] >= 0) ? dp[i - 1][j - arr[i]] : 0;
        long long skip = dp[i - 1][j];
        dp[i][j] = (pick + skip) % mod;
      }
    }

    return dp[n - 1][(sum - diff) / 2];

    // Sum(s1) - Sum(s2) = diff
    // Sum(s1) + Sum(s2) = sum
    // => Sum(s2) = (sum-diff)/2 and Sum(s1) = (sum+diff)/2
    // So basically converted to -> count subsets with sum K problem
  }
};

// Approach 2: Space Optimisation
// Time = O(n*sum), Space = O(sum)
class Solution
{
public:
  int countPartitions(int n, int diff, vector<int> &arr)
  {
    long long mod = 1e9 + 7;
    long long sum = 0;
    for (auto i : arr)
      sum += i;

    if (diff > sum)
      return 0;
    if ((sum - diff) & 1)
      return 0;

    vector<long long> prev(sum + 1, 0);
    vector<long long> curr(sum + 1, 0);
    prev[0]++;
    prev[arr[0]]++;

    for (long long i = 1; i < n; i++)
    {
      for (long long j = 0; j <= sum; j++)
      {
        long long pick = (j - arr[i] >= 0) ? prev[j - arr[i]] : 0;
        long long skip = prev[j];
        curr[j] = (pick + skip) % mod;
      }
      swap(prev, curr);
    }

    return prev[(sum - diff) / 2];

    // Sum(s1) - Sum(s2) = diff
    // Sum(s1) + Sum(s2) = sum
    // => Sum(s2) = (sum-diff)/2 and Sum(s1) = (sum+diff)/2
    // So basically converted to -> count subsets with sum K problem
  }
};

// Small fixes:
// The table is wider than needed: you only read column (sum - diff) / 2, but you fill all sum + 1 columns. Cap the table at target = (sum - diff) / 2. That saves about half the work, and more when d is large. With a smaller n·sum, it also reduces the memory risk.