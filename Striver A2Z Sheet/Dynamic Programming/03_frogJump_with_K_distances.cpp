#include <bits/stdc++.h>
using namespace std;
// Approach 1: Plain Recursion
// Time = O(k^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, vector<int> &heights, int k)
  {
    if (n == 0)
      return 0;
    if (n <= k)
      return abs(heights[n] - heights[0]);

    int minCost = INT_MAX;
    for (int i = 1; i <= k; i++)
    {
      int cost =
          helperF(n - i, heights, k) + abs(heights[n] - heights[n - i]);
      minCost = min(minCost, cost);
    }

    return minCost;
  }

public:
  int frogJump(vector<int> &heights, int k)
  {
    int n = heights.size();
    return helperF(n - 1, heights, k);
  }
};

// Approach 2: Memoization
// Time = O(nk), Space = O(n) (recursion stack + dp array)
class Solution
{
private:
  int helperF(int n, vector<int> &heights, int k, vector<int> &dp)
  {
    if (n == 0)
      return 0;
    if (n <= k)
      return abs(heights[n] - heights[0]);
    if (dp[n] != -1)
      return dp[n];

    int minCost = INT_MAX;
    for (int i = 1; i <= k; i++)
    {
      int cost =
          helperF(n - i, heights, k, dp) + abs(heights[n] - heights[n - i]);
      minCost = min(minCost, cost);
    }

    return dp[n] = minCost;
  }

public:
  int frogJump(vector<int> &heights, int k)
  {
    int n = heights.size();
    vector<int> dp(n, -1);
    return helperF(n - 1, heights, k, dp);
  }
};

// Approach 3: Tabulation
// Time = O(nk), Space = O(n) (dp array)
class Solution
{
public:
  int frogJump(vector<int> &heights, int k)
  {
    int n = heights.size();
    if (n == 1)
      return 0;
    vector<int> dp(n, -1);
    dp[0] = 0;
    for (int i = 1; i < n; i++)
    {
      int minCost = INT_MAX;
      for (int j = 1; j <= k; j++)
      {
        int cost = INT_MAX;
        if (i >= j)
          cost = dp[i - j] + abs(heights[i] - heights[i - j]);
        minCost = min(minCost, cost);
      }
      dp[i] = minCost;
    }
    return dp[n - 1];
  }
};

// Approach 4: Space Optimization
// Time = O(nk), Space = O(k)
class Solution
{
public:
  int frogJump(vector<int> &heights, int k)
  {
    int n = heights.size();
    if (n == 1)
      return 0;

    vector<int> v(k, 0);
    for (int i = 1; i < n; i++)
    {
      int minCost = INT_MAX;
      for (int j = 1; j <= k; j++)
      {
        int cost = INT_MAX;
        if (i >= j)
          cost = v[k - j] + abs(heights[i] - heights[i - j]);
        minCost = min(minCost, cost);
      }

      int curr = minCost;
      for (int id = 0; id < k - 1; id++)
      {
        v[id] = v[id + 1];
      }
      v[k - 1] = curr;
    }
    return v[k - 1];
  }
};