#include <bits/stdc++.h>
using namespace std;

// Approach 1: Plain Recursion
// Time = O(2^n), Space = O(n) (recursion stack)
class Solution
{
public:
  int climbStairs(int n)
  {
    if (n <= 1)
      return 1;
    return climbStairs(n - 1) + climbStairs(n - 2);
  }
};

// Approach 2: Memoization
// Time = O(n), Space = O(n) (recursion stack + dp array)
class Solution
{
private:
  int helperF(int n, vector<long long> &dp)
  {
    if (n <= 1)
      return 1;
    if (dp[n] != -1)
      return dp[n];

    return dp[n] = helperF(n - 1, dp) + helperF(n - 2, dp);
  }

public:
  int climbStairs(int n)
  {
    vector<long long> dp(n + 1, -1);
    return helperF(n, dp);
  }
};

// Approach 3: Tabulation
// Time = O(n), Space = O(n) (dp array)
class Solution
{
public:
  int climbStairs(int n)
  {
    vector<long long> dp(n + 1);
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
      dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
  }
};

// Approach 4: Space Optimization
// Time = O(n), Space = O(1)
class Solution
{
public:
  int climbStairs(int n)
  {
    int prev2 = 1, prev1 = 1;
    for (int i = 2; i <= n; i++)
    {
      int curr = prev2 + prev1;
      prev2 = prev1;
      prev1 = curr;
    }
    return prev1;
  }
};

// Approach 5: Matrix Exponentiation
// Time = O(logn), Space = O(1)
#include <bits/stdc++.h>
using namespace std;
#define vvll vector<vector<long long>>
class Solution
{
private:
  vvll matrixMultiply(const vvll &A, const vvll &B)
  {
    vvll res(2, vector<long long>(2));
    res[0][0] = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    res[0][1] = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    res[1][0] = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    res[1][1] = A[1][0] * B[0][1] + A[1][1] * B[1][1];
    return res;
  }

  vvll matrixPower(vvll &A, int n)
  {
    vvll res = {{1, 0}, {0, 1}};
    while (n)
    {
      if (n & 1)
        res = matrixMultiply(res, A);
      A = matrixMultiply(A, A);
      n >>= 1;
    }
    return res;
  }

public:
  int climbStairs(int n)
  {
    vvll A = {{1, 1}, {1, 0}};
    A = matrixPower(A, n - 1);
    return A[0][0] + A[0][1];
  }
};