#include <bits/stdc++.h>
using namespace std;

// Approach 1 : Recursion
// Time = O(3^n), Space = O(n)
class Solution
{
private:
  bool helperF(int index, int nextJump, vector<int> &stones,
               unordered_map<int, int> &mpp)
  {
    if (index == stones.size() - 1)
      return true;

    if (mpp.find(stones[index] + nextJump) == mpp.end())
      return false;

    int nextIndex = mpp[stones[index] + nextJump];
    bool opt1 =
        (nextJump > 1) ? helperF(nextIndex, nextJump - 1, stones, mpp) : 0;
    bool opt2 = helperF(nextIndex, nextJump, stones, mpp);
    bool opt3 = helperF(nextIndex, nextJump + 1, stones, mpp);
    return opt1 || opt2 || opt3;
  }

public:
  bool canCross(vector<int> &stones)
  {
    int n = stones.size();

    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++)
      mpp[stones[i]] = i;

    return helperF(0, 1, stones, mpp);
  }
};

// Approach 2 : Recursion + Memoization
// Time = O(n^2), Space = O(n^2)
class Solution
{
private:
  bool helperF(int index, int nextJump, vector<int> &stones,
               unordered_map<int, int> &mpp, vector<vector<int>> &dp)
  {
    if (index == stones.size() - 1)
      return true;

    if (mpp.find(stones[index] + nextJump) == mpp.end())
      return false;

    if (dp[index][nextJump] != -1)
      return dp[index][nextJump];

    int nextIndex = mpp[stones[index] + nextJump];
    bool opt1 = (nextJump > 1)
                    ? helperF(nextIndex, nextJump - 1, stones, mpp, dp)
                    : 0;
    bool opt2 = helperF(nextIndex, nextJump, stones, mpp, dp);
    bool opt3 = helperF(nextIndex, nextJump + 1, stones, mpp, dp);
    return dp[index][nextJump] = opt1 || opt2 || opt3;
  }

public:
  bool canCross(vector<int> &stones)
  {
    int n = stones.size();

    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++)
      mpp[stones[i]] = i;

    vector<vector<int>> dp(n, vector<int>(n, -1));

    return helperF(0, 1, stones, mpp, dp);
  }
};

// Approach 3 : Tabulation
// Time = O(n^2), Space = O(n^2)
class Solution
{
public:
  bool canCross(vector<int> &stones)
  {
    int n = stones.size();

    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++)
      mpp[stones[i]] = i;

    vector<vector<int>> dp(n, vector<int>(n, 0));
    dp[0][1] = 1;
    for (int i = 0; i < n; i++)
    {
      for (int j = 1; j < n; j++)
      {
        if (dp[i][j])
        {
          if (mpp.find(stones[i] + j) == mpp.end())
            continue;
          int nextIndex = mpp[stones[i] + j];
          if (j >= 1)
            dp[nextIndex][j - 1] = 1;
          dp[nextIndex][j] = 1;
          if (j + 1 < n)
            dp[nextIndex][j + 1] = 1;
        }
      }
    }

    for (int j = 1; j < n; j++)
    {
      if (dp[n - 1][j])
        return true;
    }
    return false;
  }
};
