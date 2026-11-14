#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, int currA, int clipA)
  {
    if (currA == n)
      return 0;
    if (currA > n)
      return 1e9; // Return a large number to indicate invalid path but not INT_MAX to avoid overflow

    int copyThenPaste = 2 + helperF(n, 2 * currA, currA);
    int directPaste = 1 + helperF(n, currA + clipA, clipA);

    return min(copyThenPaste, directPaste);
  }

public:
  int minSteps(int n)
  {
    if (n == 1)
      return 0;
    return 1 + helperF(n, 1, 1); // 1 added for initial copy
  }
};

// Approach 2: Memoization
// Time = O(n^2), Space = O(n^2) + O(n) (recursion stack)
class Solution
{
private:
  int helperF(int n, int currA, int clipA, vector<vector<int>> &dp)
  {
    if (currA == n)
      return 0;
    if (currA > n)
      return 1e9;
    if (dp[currA][clipA] != -1)
      return dp[currA][clipA];

    int copyThenPaste = 2 + helperF(n, 2 * currA, currA, dp);
    int directPaste = 1 + helperF(n, currA + clipA, clipA, dp);

    return dp[currA][clipA] = min(copyThenPaste, directPaste);
  }

public:
  int minSteps(int n)
  {
    if (n == 1)
      return 0;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
    return 1 + helperF(n, 1, 1, dp); // 1 added for initial copy
  }
};

// Approach 3: Tabulation
// Time = O(n^2), Space = O(n^2)
class Solution
{
public:
  int minSteps(int n)
  {
    if (n == 1)
      return 0;
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 1e9));
    dp[1][1] = 0; // Starting point: 1 'A' on screen and nothing copied yet (no steps taken yet)

    for (int currA = 1; currA <= n; ++currA)
    {
      for (int clipA = 1; clipA <= currA; ++clipA)
      {
        if (dp[currA][clipA] == 1e9)
          continue; // Skip unreachable states

        // Copy then Paste
        if (2 * currA <= n)
          dp[2 * currA][currA] = min(dp[2 * currA][currA], dp[currA][clipA] + 2);

        // Direct Paste
        if (currA != 1 && currA + clipA <= n)
          dp[currA + clipA][clipA] = min(dp[currA + clipA][clipA], dp[currA][clipA] + 1);
      }
    }

    int result = INT_MAX;
    for (int clipA = 1; clipA <= n; ++clipA)
    {
      result = min(result, dp[n][clipA]);
    }
    return result;
  }
};

// Approach 4: Mathematical Factorization (Linear)
// Time = O(n), Space = O(1)
class Solution
{
public:
  int minSteps(int n)
  {
    int steps = 0;
    for (int i = 2; i <= n; ++i)
    {
      while (n % i == 0)
      {
        steps += i;
        n /= i;
      }
    }
    return steps;
  }
};

// Approach 5: Optimized Factorization
// Time = O(sqrt(n)), Space = O(1)
class Solution
{
public:
  int minSteps(int n)
  {
    int steps = 0;
    for (int i = 2; i * i <= n; ++i)
    {
      while (n % i == 0)
      {
        steps += i;
        n /= i;
      }
    }
    if (n > 1)
      steps += n; // If n is prime
    return steps;
  }
};