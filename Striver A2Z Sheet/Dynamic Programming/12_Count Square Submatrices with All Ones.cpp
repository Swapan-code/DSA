#include <bits/stdc++.h>
using namespace std;

// Approach 1: Dynamic Programming
// Time = O(m*n), Space = O(m*n)
class Solution
{
public:
  int countSquares(vector<vector<int>> &matrix)
  {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n));
    int ans = 0;

    for (int j = 0; j < n; j++)
    {
      dp[0][j] = matrix[0][j];
      ans += dp[0][j];
    }
    for (int i = 1; i < m; i++)
    {
      dp[i][0] = matrix[i][0];
      ans += dp[i][0];
    }

    for (int i = 1; i < m; i++)
    {
      for (int j = 1; j < n; j++)
      {
        if (matrix[i][j] == 0)
          dp[i][j] = 0;
        else
          dp[i][j] =
              1 + min({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]});
        ans += dp[i][j];
      }
    }

    return ans;
  }
};

// Approach 2: Dynamic Programming (Space Optimization)
// Time = O(m*n), Space = O(n)
class Solution
{
public:
  int countSquares(vector<vector<int>> &matrix)
  {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> prev(n);
    vector<int> curr;
    int ans = 0;

    for (int j = 0; j < n; j++)
    {
      prev[j] = matrix[0][j];
      ans += prev[j];
    }

    for (int i = 1; i < m; i++)
    {
      curr.assign(n, 0);
      for (int j = 0; j < n; j++)
      {
        if (j == 0 && matrix[i][j] == 1)
        {
          curr[0] = 1;
          ans++;
        }
        else if (matrix[i][j] == 1)
        {
          curr[j] = 1 + min({prev[j - 1], prev[j], curr[j - 1]});
          ans += curr[j];
        }
      }

      swap(prev, curr);
    }

    return ans;
  }
};

// Approach 3: Dynamic Programming (Space Optimization)
// Time = O(m*n), Space = O(n)
// This approach is similar to Approach 2, but we use only one array to store the previous row's values and a variable to store the diagonal value.
class Solution
{
public:
  int countSquares(vector<vector<int>> &matrix)
  {
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> dp(n);
    int ans = 0;

    for (int j = 0; j < n; j++)
    {
      dp[j] = matrix[0][j];
      ans += dp[j];
    }

    int diagonalValue = 0;
    for (int i = 1; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        int temp = dp[j];
        if (j == 0)
        {
          dp[0] = matrix[i][0];
          ans += matrix[i][0];
        }
        else if (matrix[i][j] == 1)
        {
          dp[j] = 1 + min({diagonalValue, dp[j], dp[j - 1]});
          ans += dp[j];
        }
        else
        {
          dp[j] = 0;
        }
        diagonalValue = temp;
      }
    }

    return ans;
  }
};