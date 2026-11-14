#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^(m+n)), Space = O(m+n) (recursion stack)
class Solution
{
private:
  int helperF(int m, int n)
  {
    if (m == 0 || n == 0)
      return 1;
    return helperF(m - 1, n) + helperF(m, n - 1);
  }

public:
  int uniquePaths(int m, int n)
  {
    return helperF(m - 1, n - 1);
  }
};

// Approach 2: Memoization
// Time = O(m*n), Space = O(m*n) + O(m+n) (recursion stack)
class Solution
{
private:
  int helperF(int m, int n, vector<vector<int>> &dp)
  {
    if (m == 0 || n == 0)
      return 1;
    if (dp[m][n] != -1)
      return dp[m][n];
    return dp[m][n] = helperF(m - 1, n, dp) + helperF(m, n - 1, dp);
  }

public:
  int uniquePaths(int m, int n)
  {
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return helperF(m - 1, n - 1, dp);
  }
};

// Approach 3: Tabulation
// Time = O(m*n), Space = O(m*n)
class Solution
{
public:
  int uniquePaths(int m, int n)
  {
    if (m == 1 || n == 1)
      return 1;
    vector<vector<int>> dp(m, vector<int>(n));
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i == 0 || j == 0)
          dp[i][j] = 1;
        else
          dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }

    return dp[m - 1][n - 1];
  }
};

// Approach 4: Space Optimization
// Time = O(m*n), Space = O(min(m,n)) by swapping m and n to use the smaller dimension for dp array
class Solution
{
public:
  int uniquePaths(int m, int n)
  {
    if (m == 1 || n == 1)
      return 1;

    if ((n > m))
      swap(m, n); // to reduce space complexity by using the smaller dimension for dp array
    vector<int> dp(n, 1);

    for (int i = 1; i < m; i++)
    {
      for (int j = 1; j < n; j++)
      {
        dp[j] += dp[j - 1];
      }
    }

    return dp[n - 1];
  }
};

// Approach 5: Combinatorics
// Time = O(min(m,n)), Space = O(1)
class Solution
{
public:
  int uniquePaths(int m, int n)
  {
    if (m == 1 || n == 1)
      return 1;

    int total = m + n - 2;
    int r = min(m - 1, n - 1);

    // Calculate totalCr = total! / (r! * (total - r)!)
    long long result = 1;
    for (int i = 0; i < r; i++)
    {
      result = result * (total - i) / (i + 1);
    }
    return (int)result;
  }
};