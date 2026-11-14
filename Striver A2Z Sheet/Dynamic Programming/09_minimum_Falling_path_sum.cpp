#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(n * 3^n), Space = O(n) for recursion stack
class Solution
{
private:
  int helperF(int i, int j, vector<vector<int>> &matrix)
  {
    if (j < 0 || j >= matrix.size())
      return INT_MAX;
    if (i == 0)
      return matrix[i][j];

    int opt1 = helperF(i - 1, j - 1, matrix);
    int opt2 = helperF(i - 1, j, matrix);
    int opt3 = helperF(i - 1, j + 1, matrix);
    return matrix[i][j] + min({opt1, opt2, opt3});
  }

public:
  int minFallingPathSum(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    long long ans = LLONG_MAX;
    for (int j = 0; j < n; j++)
    {
      long long sum = helperF(n - 1, j, matrix);
      ans = min(ans, sum);
    }
    return ans;
  }
};

// Approach 2: Memoization
// Time = O(n^2), Space = O(n^2) + O(n) for recursion stack
class Solution
{
private:
  int helperF(int i, int j, vector<vector<int>> &matrix,
              vector<vector<int>> &dp)
  {
    if (j < 0 || j >= matrix.size())
      return INT_MAX;
    if (i == 0)
      return matrix[i][j];
    if (dp[i][j] != INT_MAX)
      return dp[i][j];

    int opt1 = helperF(i - 1, j - 1, matrix, dp);
    int opt2 = helperF(i - 1, j, matrix, dp);
    int opt3 = helperF(i - 1, j + 1, matrix, dp);
    return dp[i][j] = matrix[i][j] + min({opt1, opt2, opt3});
  }

public:
  int minFallingPathSum(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    long long ans = LLONG_MAX;
    for (int j = 0; j < n; j++)
    {
      long long sum = helperF(n - 1, j, matrix, dp);
      ans = min(ans, sum);
    }
    return ans;
  }
};

// Approach 3: Tabulation
// Time = O(n^2), Space = O(n^2)
class Solution
{
public:
  int minFallingPathSum(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int j = 0; j < n; j++)
    {
      dp[0][j] = matrix[0][j];
    }

    for (int i = 1; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        int opt1 = (j >= 1) ? dp[i - 1][j - 1] : INT_MAX;
        int opt2 = dp[i - 1][j];
        int opt3 = (j + 1 < n) ? dp[i - 1][j + 1] : INT_MAX;
        dp[i][j] = matrix[i][j] + min({opt1, opt2, opt3});
      }
    }

    int ans = INT_MAX;
    for (int j = 0; j < n; j++)
    {
      ans = min(ans, dp[n - 1][j]);
    }
    return ans;
  }
};

// Approach 4: Space Optimization
// Time = O(n^2), Space = O(n)
class Solution
{
public:
  int minFallingPathSum(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    vector<int> prev(n);
    for (int j = 0; j < n; j++)
    {
      prev[j] = matrix[0][j];
    }

    for (int i = 1; i < n; i++)
    {
      vector<int> curr(n);
      for (int j = 0; j < n; j++)
      {
        int opt1 = (j >= 1) ? prev[j - 1] : INT_MAX;
        int opt2 = prev[j];
        int opt3 = (j + 1 < n) ? prev[j + 1] : INT_MAX;
        curr[j] = matrix[i][j] + min({opt1, opt2, opt3});
      }
      prev = curr;
    }

    int ans = INT_MAX;
    for (int j = 0; j < n; j++)
    {
      ans = min(ans, prev[j]);
    }
    return ans;
  }
};