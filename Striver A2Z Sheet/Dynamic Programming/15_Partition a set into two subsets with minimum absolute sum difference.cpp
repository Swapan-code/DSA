// Similar to problem: Subset Sum Equal to Target (Striver -> DP)

#include <bits/stdc++.h>
using namespace std;

// Approach 1: DP
// Time = O(n*sum), Space = O(n*sum)
class Solution
{
public:
  int minDifference(vector<int> &arr, int n)
  {
    int sum = 0;
    for (auto i : arr)
      sum += i;
    vector<vector<bool>> dp(n, vector<bool>(sum + 1, 0));
    dp[0][arr[0]] = 1;
    for (int i = 0; i < n; i++)
      dp[i][0] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j <= sum; j++)
      {
        bool pick = (j - arr[i] >= 0) ? dp[i - 1][j - arr[i]] : false;
        bool skip = dp[i - 1][j];

        dp[i][j] = pick || skip;
      }
    }

    int ans = sum;
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
  int minDifference(vector<int> &arr, int n)
  {
    int sum = 0;
    for (auto i : arr)
      sum += i;
    vector<bool> prev(sum + 1, 0);
    vector<bool> curr(sum + 1, 0);
    prev[arr[0]] = 1;
    prev[0] = 1;

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j <= sum; j++)
      {
        bool pick = (j - arr[i] >= 0) ? prev[j - arr[i]] : false;
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

// Optional improvements:
// Cap the table at sum/2: you only read columns 0..sum/2 at the end, so filling 0..sum does about twice the work. Dropping the upper half changes nothing about the result.