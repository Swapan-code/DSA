#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int i, int j, vector<vector<int>> &matrix)
  {
    if (i == 0)
      return matrix[0][j];

    int best = INT_MIN;
    for (int id = 0; id < 3; id++)
    {
      if (id != j)
      {
        best = max(best, helperF(i - 1, id, matrix));
      }
    }

    return matrix[i][j] + best;
  }

public:
  int ninjaTraining(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    int opt1 = helperF(n - 1, 0, matrix);
    int opt2 = helperF(n - 1, 1, matrix);
    int opt3 = helperF(n - 1, 2, matrix);
    return max({opt1, opt2, opt3});
  }
};

// Approach 2: Memoization
// Time = O(n*3), Space = O(n*3) + O(n) (recursion stack)
// Reason for O(n*3) is that we have n rows and 3 columns in the dp array. And, for each cell, we are calculating the maximum points by checking the other two columns in the previous row. Hence, the time complexity is O(n*3).
class Solution
{
private:
  int helperF(int i, int j, vector<vector<int>> &matrix,
              vector<vector<int>> &dp)
  {
    if (i == 0)
      return matrix[0][j];
    if (dp[i][j] != -1)
      return dp[i][j];

    int best = INT_MIN;
    for (int id = 0; id < 3; id++)
    {
      if (id != j)
      {
        best = max(best, helperF(i - 1, id, matrix, dp));
      }
    }

    return dp[i][j] = matrix[i][j] + best;
  }

public:
  int ninjaTraining(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(3, -1));
    int opt1 = helperF(n - 1, 0, matrix, dp);
    int opt2 = helperF(n - 1, 1, matrix, dp);
    int opt3 = helperF(n - 1, 2, matrix, dp);
    return max({opt1, opt2, opt3});
  }
};

// Approach 3: Tabulation
// Time = O(n*3), Space = O(n*3)
class Solution
{
public:
  int ninjaTraining(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(3));
    dp[0][0] = matrix[0][0];
    dp[0][1] = matrix[0][1];
    dp[0][2] = matrix[0][2];

    for (int i = 1; i < n; i++)
    {
      dp[i][0] = matrix[i][0] + max(dp[i - 1][1], dp[i - 1][2]);
      dp[i][1] = matrix[i][1] + max(dp[i - 1][0], dp[i - 1][2]);
      dp[i][2] = matrix[i][2] + max(dp[i - 1][0], dp[i - 1][1]);
    }
    return max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2]});
  }
};

// Approach 4: Space Optimization
// Time = O(n*3), Space = O(1)
class Solution
{
public:
  int ninjaTraining(vector<vector<int>> &matrix)
  {
    int n = matrix.size();
    vector<int> prev(3);
    prev[0] = matrix[0][0];
    prev[1] = matrix[0][1];
    prev[2] = matrix[0][2];

    for (int i = 1; i < n; i++)
    {
      vector<int> curr(3);
      curr[0] = matrix[i][0] + max(prev[1], prev[2]);
      curr[1] = matrix[i][1] + max(prev[0], prev[2]);
      curr[2] = matrix[i][2] + max(prev[0], prev[1]);
      prev = curr;
    }
    return max({prev[0], prev[1], prev[2]});
  }
};