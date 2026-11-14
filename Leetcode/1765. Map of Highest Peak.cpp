#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  vector<vector<int>> highestPeak(vector<vector<int>> &isWater)
  {
    int m = isWater.size();
    int n = isWater[0].size();

    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (isWater[i][j] != 1)
        {
          int left = (j - 1 >= 0) ? isWater[i][j - 1] : 1e9;
          int up = (i - 1 >= 0) ? isWater[i - 1][j] : 1e9;
          isWater[i][j] = 1 + min(left, up);
        }
        else
        {
          isWater[i][j] = 0;
        }
      }
    }

    for (int i = m - 1; i >= 0; i--)
    {
      for (int j = n - 1; j >= 0; j--)
      {
        if (isWater[i][j] != 0)
        {
          int right = (j + 1 < n) ? isWater[i][j + 1] : 1e9;
          int bottom = (i + 1 < m) ? isWater[i + 1][j] : 1e9;
          isWater[i][j] = min(isWater[i][j], 1 + min(right, bottom));
        }
      }
    }

    return isWater;
  }
};