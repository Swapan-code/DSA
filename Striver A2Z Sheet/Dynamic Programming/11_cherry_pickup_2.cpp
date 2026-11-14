#include <bits/stdc++.h>
using namespace std;

// Approach 1: DP (Bottom Up) - Tabulation
// Time = O(row*col*col), Space = O(row*col*col)
class Solution
{
public:
  int cherryPickup(vector<vector<int>> &grid)
  {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<vector<int>>> dp(
        row, vector<vector<int>>(col, vector<int>(col, -1)));

    dp[0][0][col - 1] = grid[0][0] + grid[0][col - 1];

    for (int i = 1; i < row; i++)
    {
      for (int j = 0; j < col; j++)
      {
        for (int k = 0; k < col; k++)
        {
          if (j > i || k < col - i - 1)
            continue;

          for (int x = -1; x <= 1; x++)
          {
            for (int y = -1; y <= 1; y++)
            {
              if (j + x >= 0 && j + x < col && k + y >= 0 &&
                  k + y < col && dp[i - 1][j + x][k + y] != -1)
              {
                int cherries = dp[i - 1][j + x][k + y];
                if (j == k)
                {
                  cherries += grid[i][j];
                }
                else
                {
                  cherries += grid[i][j] + grid[i][k];
                }
                dp[i][j][k] = max(cherries, dp[i][j][k]);
              }
            }
          }
        }
      }
    }

    int ans = 0;
    for (int j = 0; j < col; j++)
    {
      for (int k = 0; k < col; k++)
      {
        ans = max(ans, dp[row - 1][j][k]);
      }
    }
    return ans;
  }
};

// Approach 2: DP (Bottom Up) - Space Optimization
// Time = O(row*col*col), Space = O(col*col)
class Solution
{
public:
  int cherryPickup(vector<vector<int>> &grid)
  {
    int row = grid.size();
    int col = grid[0].size();
    vector<vector<int>> prev(col, vector<int>(col, -1));
    vector<vector<int>> curr;

    prev[0][col - 1] = grid[0][0] + grid[0][col - 1];

    for (int i = 1; i < row; i++)
    {
      curr.assign(col, vector<int>(col, -1));
      for (int j = 0; j < col; j++)
      {
        for (int k = 0; k < col; k++)
        {
          if (j > i || k < col - i - 1)
            continue;

          for (int x = -1; x <= 1; x++)
          {
            for (int y = -1; y <= 1; y++)
            {
              if (j + x >= 0 && j + x < col && k + y >= 0 &&
                  k + y < col && prev[j + x][k + y] != -1)
              {
                int cherries = prev[j + x][k + y];
                if (j == k)
                {
                  cherries += grid[i][j];
                }
                else
                {
                  cherries += grid[i][j] + grid[i][k];
                }
                curr[j][k] = max(cherries, curr[j][k]);
              }
            }
          }
        }
      }
      swap(prev, curr);
    }

    int ans = 0;
    for (int j = 0; j < col; j++)
    {
      for (int k = 0; k < col; k++)
      {
        ans = max(ans, prev[j][k]);
      }
    }
    return ans;
  }
};