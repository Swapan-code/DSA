#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^k) = O(2^(3*n)), Space = O(n)
class Solution
{
private:
  int helperF(int s, int e, vector<int> &slices, int n)
  {
    if (n == 0 || s > e)
      return 0;

    int take = slices[s] + helperF(s + 2, e, slices, n - 1);
    int skip = helperF(s + 1, e, slices, n);
    return max(take, skip);
  }

public:
  int maxSizeSlices(vector<int> &slices)
  {
    int k = slices.size();
    int n = k / 3;
    int op1 = helperF(0, k - 2, slices, n);
    int op2 = helperF(1, k - 1, slices, n);
    return max(op1, op2);
  }
};

// Approach 2: Memoization
// Time = O(k*n) = O(n^2), Space = O(n^2) + O(n) for recursion stack
class Solution
{
private:
  int helperF(int s, int e, vector<int> &slices, int n, vector<vector<int>> &dp)
  {
    if (n == 0 || s > e)
      return 0;

    if (dp[s][n] != -1)
      return dp[s][n];

    int take = slices[s] + helperF(s + 2, e, slices, n - 1, dp);
    int skip = helperF(s + 1, e, slices, n, dp);
    return dp[s][n] = max(take, skip);
  }

public:
  int maxSizeSlices(vector<int> &slices)
  {
    int k = slices.size();
    int n = k / 3;
    vector<vector<int>> dp1(k, vector<int>(n + 1, -1));
    vector<vector<int>> dp2(k, vector<int>(n + 1, -1));
    int op1 = helperF(0, k - 2, slices, n, dp1);
    int op2 = helperF(1, k - 1, slices, n, dp2);
    return max(op1, op2);
  }
};

// Approach 3: Tabulation
// Time = O(k*n) = O(n^2), Space = O(k*n) = O(n^2)
class Solution
{
private:
  int helperF(int s, int e, vector<int> &slices, int n)
  {
    vector<vector<int>> dp(3 * n + 2, vector<int>(n + 1, 0));
    for (int i = e; i >= s; i--)
    {
      for (int j = 1; j <= n; j++)
      {
        int take = slices[i] + dp[i + 2][j - 1];
        int skip = dp[i + 1][j];
        dp[i][j] = max(take, skip);
      }
    }

    return dp[s][n];
  }

public:
  int maxSizeSlices(vector<int> &slices)
  {
    int k = slices.size();
    int n = k / 3;

    int op1 = helperF(0, k - 2, slices, n);
    int op2 = helperF(1, k - 1, slices, n);
    return max(op1, op2);
  }
};

// Approach 4: Space Optimization
// Time = O(k*n) = O(n^2), Space = O(n)
class Solution
{
private:
  int helperF(int s, int e, vector<int> &slices, int n)
  {
    vector<int> prev2(n + 1, 0);
    vector<int> prev1(n + 1, 0);
    vector<int> curr(n + 1, 0);
    for (int i = e; i >= s; i--)
    {
      for (int j = 1; j <= n; j++)
      {
        int take = slices[i] + prev2[j - 1];
        int skip = prev1[j];
        curr[j] = max(take, skip);
      }

      swap(prev2, prev1);
      swap(prev1, curr);
    }

    return prev1[n];
  }

public:
  int maxSizeSlices(vector<int> &slices)
  {
    int k = slices.size();
    int n = k / 3;

    int op1 = helperF(0, k - 2, slices, n);
    int op2 = helperF(1, k - 1, slices, n);
    return max(op1, op2);
  }
};