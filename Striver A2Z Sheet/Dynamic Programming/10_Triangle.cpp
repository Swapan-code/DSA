#include <bits/stdc++.h>
using namespace std;

// Approach 1: Dynamic Programming
// Time = O(n^2), Space = O(n^2)
class Solution
{
public:
  int minimumTotal(vector<vector<int>> &triangle)
  {
    int n = triangle.size();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int j = 0; j < n; j++)
      dp[n - 1][j] = triangle[n - 1][j];

    for (int i = n - 2; i >= 0; i--)
    {
      for (int j = 0; j <= i; j++)
      {
        dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
      }
    }

    return dp[0][0];
  }
};

// Approach 2: Space Optimization
// Time = O(n^2), Space = O(n)
class Solution
{
public:
  int minimumTotal(vector<vector<int>> &triangle)
  {
    int n = triangle.size();
    vector<int> dp(n);
    for (int j = 0; j < n; j++)
      dp[j] = triangle[n - 1][j];

    for (int i = n - 2; i >= 0; i--)
    {
      for (int j = 0; j <= i; j++)
      {
        dp[j] = triangle[i][j] + min(dp[j], dp[j + 1]);
      }
    }

    return dp[0];
  }
};

// Optional in-place variant: if you may modify the input, replace dp with triangle itself and use triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]), which uses no extra space. In an interview, ask first whether modifying the input is allowed.