#include <bits/stdc++.h>
using namespace std;

// Approach 1: Two-Pass DP
// Time = O(n), Space = O(n)
class Solution
{
public:
  int minimumTime(string s)
  {
    int n = s.size();
    vector<int> dp1(n);
    vector<int> dp2(n);

    dp1[0] = s[0] == '1' ? 1 : 0;

    for (int i = 1; i < n; i++)
    {
      if (s[i] == '0')
        dp1[i] = dp1[i - 1];
      else
        dp1[i] = min(dp1[i - 1] + 2, i + 1);
    }

    dp2[n - 1] = s[n - 1] == '1' ? 1 : 0;

    for (int i = 1; i < n; i++)
    {
      if (s[n - i - 1] == '0')
        dp2[n - i - 1] = dp2[n - i];
      else
        dp2[n - i - 1] = min(dp2[n - i] + 2, i + 1);
    }

    int ans = min(dp1[n - 1], dp2[0]);
    for (int i = 1; i < n; i++)
    {
      ans = min(ans, dp1[i - 1] + dp2[i]);
    }

    return ans;
  }
};

// Approach 2: One-Pass DP
// Time = O(n), Space = O(n)
class Solution
{
public:
  int minimumTime(string s)
  {
    int n = s.size();
    vector<int> dp(n);

    dp[0] = s[0] == '1' ? 1 : 0;
    int ans = n; // Full remove from right

    for (int i = 1; i < n; i++)
    {
      if (s[i] == '0')
        dp[i] = dp[i - 1];
      else
        dp[i] = min(dp[i - 1] + 2, i + 1);

      ans = min(ans, dp[i - 1] + n - i); // Split
    }

    ans = min(ans, dp[n - 1]); // Full remove from left
    return ans;
  }
};

// Approach 3: One-Pass DP with Constant Space
// Time = O(n), Space = O(1)
class Solution
{
public:
  int minimumTime(string s)
  {
    int n = s.size();

    int prev = s[0] == '1' ? 1 : 0;
    int ans = n; // Full remove from right

    for (int i = 1; i < n; i++)
    {
      int curr;
      if (s[i] == '0')
        curr = prev;
      else
        curr = min(prev + 2, i + 1);

      ans = min(ans, prev + n - i); // Split
      prev = curr;
    }

    ans = min(ans, prev); // Full remove from left
    return ans;
  }
};