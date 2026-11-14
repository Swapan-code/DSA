#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^(m+n)), Space = O(m+n) (Recursion Stack)
class Solution
{
private:
  int helperF(int i, int j, vector<vector<int>> &obstacleGrid)
  {
    if (i == 0 && j == 0)
      return 1;

    int left = (j >= 1 && obstacleGrid[i][j - 1] != 1)
                   ? helperF(i, j - 1, obstacleGrid)
                   : 0;
    int up = (i >= 1 && obstacleGrid[i - 1][j] != 1)
                 ? helperF(i - 1, j, obstacleGrid)
                 : 0;

    return up + left;
  }

public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
  {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
      return 0;
    return helperF(m - 1, n - 1, obstacleGrid);
  }
};

// Approach 2: Memoization
// Time = O(m*n), Space = O(m*n) + O(m+n) (Recursion Stack)
class Solution
{
private:
  int helperF(int i, int j, vector<vector<int>> &obstacleGrid,
              vector<vector<int>> &dp)
  {
    if (i == 0 && j == 0)
      return 1;
    if (dp[i][j] != -1)
      return dp[i][j];

    int left = (j >= 1 && obstacleGrid[i][j - 1] != 1)
                   ? helperF(i, j - 1, obstacleGrid, dp)
                   : 0;
    int up = (i >= 1 && obstacleGrid[i - 1][j] != 1)
                 ? helperF(i - 1, j, obstacleGrid, dp)
                 : 0;

    return dp[i][j] = up + left;
  }

public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
  {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
      return 0;

    vector<vector<int>> dp(m, vector<int>(n, -1));
    return helperF(m - 1, n - 1, obstacleGrid, dp);
  }
};

// Approach 3: Tabulation
// Time = O(m*n), Space = O(m*n)
class Solution
{
public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
  {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
      return 0;

    vector<vector<int>> dp(m, vector<int>(n));
    dp[0][0] = 1;

    int j = 1;
    while (j < n && obstacleGrid[0][j] == 0)
    {
      dp[0][j] = 1;
      j++;
    }
    while (j < n)
    {
      dp[0][j] = 0;
      j++;
    }

    int i = 1;
    while (i < m && obstacleGrid[i][0] == 0)
    {
      dp[i][0] = 1;
      i++;
    }
    while (i < m)
    {
      dp[i][0] = 0;
      i++;
    }

    for (int i = 1; i < m; i++)
    {
      for (int j = 1; j < n; j++)
      {
        dp[i][j] =
            (obstacleGrid[i][j] != 1) ? dp[i - 1][j] + dp[i][j - 1] : 0;
      }
    }

    return dp[m - 1][n - 1];
  }
};

// Approach 4: Space Optimization
// Time = O(m*n), Space = O(n)
class Solution
{
public:
  int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
  {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
      return 0;

    vector<int> dp(n);
    dp[0] = 1;

    int j = 1;
    while (j < n && obstacleGrid[0][j] == 0)
    {
      dp[j] = 1;
      j++;
    }
    while (j < n)
    {
      dp[j] = 0;
      j++;
    }

    for (int i = 1; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (j == 0)
          dp[j] = (obstacleGrid[i][j] != 1) ? dp[j] : 0;
        else
          dp[j] = (obstacleGrid[i][j] != 1) ? dp[j] + dp[j - 1] : 0;
      }
    }

    return dp[n - 1];
  }
};