#include <bits/stdc++.h>
using namespace std;

// Approach 1: BFS
// Time = O(m*n), Space = O(m*n)
class Solution
{
public:
  vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
  {
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<bool>> visited(m, vector<bool>(n, false));
    vector<vector<int>> ans(m, vector<int>(n));
    queue<pair<int, int>> q;

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (mat[i][j] == 0)
        {
          q.push({i, j});
          visited[i][j] = true;
        }
      }
    }

    int dist = 0;
    while (!q.empty())
    {
      int k = q.size();
      for (int id = 1; id <= k; id++)
      {
        int i = q.front().first;
        int j = q.front().second;
        ans[i][j] = dist;
        q.pop();

        if (i + 1 < m && !visited[i + 1][j])
        {
          q.push({i + 1, j});
          visited[i + 1][j] = true;
        }
        if (i - 1 >= 0 && !visited[i - 1][j])
        {
          q.push({i - 1, j});
          visited[i - 1][j] = true;
        }
        if (j + 1 < n && !visited[i][j + 1])
        {
          q.push({i, j + 1});
          visited[i][j + 1] = true;
        }
        if (j - 1 >= 0 && !visited[i][j - 1])
        {
          q.push({i, j - 1});
          visited[i][j - 1] = true;
        }
      }
      dist++;
    }

    return ans;
  }
};

// Approach 2: Two-Pass DP
// Time = O(m*n), Space = O(m*n)
class Solution
{
public:
  vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
  {
    int m = mat.size();
    int n = mat[0].size();
    vector<vector<int>> dp(m, vector<int>(n));

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (mat[i][j] != 0)
        {
          int left = (j - 1 >= 0) ? dp[i][j - 1] : 1e9;
          int up = (i - 1 >= 0) ? dp[i - 1][j] : 1e9;
          dp[i][j] = 1 + min(left, up);
        }
        else
        {
          dp[i][j] = 0;
        }
      }
    }

    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = n - 1; j >= 0; j--)
      {
        if (mat[i][j] != 0)
        {
          int right = (j + 1 < n) ? dp[i][j + 1] : 1e9;
          int bottom = (i + 1 < m) ? dp[i + 1][j] : 1e9;
          dp[i][j] = min(dp[i][j], 1 + min(right, bottom));
        }
        else
        {
          dp[i][j] = 0;
        }
      }
    }

    return dp;
  }
};

// Approach 3: Dynamic Programming (Space Optimization, In-place Modification if allowed)
// Time = O(m*n), Space = O(1)
class Solution
{
public:
  vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
  {
    int m = mat.size();
    int n = mat[0].size();

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (mat[i][j] != 0)
        {
          int left = (j - 1 >= 0) ? mat[i][j - 1] : 1e9;
          int up = (i - 1 >= 0) ? mat[i - 1][j] : 1e9;
          mat[i][j] = 1 + min(left, up);
        }
      }
    }

    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = n - 1; j >= 0; j--)
      {
        if (mat[i][j] != 0)
        {
          int right = (j + 1 < n) ? mat[i][j + 1] : 1e9;
          int bottom = (i + 1 < m) ? mat[i + 1][j] : 1e9;
          mat[i][j] = min(mat[i][j], 1 + min(right, bottom));
        }
        else
        {
          mat[i][j] = 0;
        }
      }
    }

    return mat;
  }
};