#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Source is OCW PA lab - 3, knapsack problem .

int sushi_1(int nf, int ns, int budget, vector<int> &prices, vector<vector<int>> &grades)
{
  const int total_budget = nf * budget;
  int sum_grades = 0;

  vector<vector<int>> dp(ns + 1, vector<int>(total_budget + 1, 0));

  for (int i = 1; i <= ns; ++i)
  {
    for (int j = 0; j <= total_budget; j++)
    {
      if (j - prices[i - 1] >= 0)
      {
        sum_grades = dp[i - 1][j - prices[i - 1]];

        for (int k = 0; k < nf; ++k)
        {
          sum_grades += grades[k][i - 1];
        }

        dp[i][j] = max(dp[i - 1][j], sum_grades);
      }
      else
      {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[ns][total_budget];
}

int sushi_2(int nf, int ns, int budget, vector<int> &prices, vector<vector<int>> &grades)
{
  const int total_budget = nf * budget;
  int sum_grades = 0;

  vector<vector<int>> dp((ns * 2) + 1, vector<int>(total_budget + 1, 0));

  for (int i = 1; i <= ns * 2; ++i)
  {
    int price_index = (i > ns) ? ((i % ns == 0) ? ns - 1 : i % ns - 1) : i - 1;

    for (int j = 0; j <= total_budget; ++j)
    {
      if (j - prices[price_index] >= 0)
      {
        sum_grades = dp[i - 1][j - prices[price_index]];

        for (int k = 0; k < nf; ++k)
        {
          sum_grades += grades[k][price_index];
        }

        dp[i][j] = max(dp[i - 1][j], sum_grades);
      }
      else
      {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  return dp[ns * 2][total_budget];
}

// Source is GeeksForGeeks - Extended Knapsack Problem

int sushi_3(int nf, int ns, int budget, vector<int> &prices, vector<vector<int>> &grades)
{
  const int total_budget = nf * budget;

  vector<int> sum_grades_all(ns);
  for (int i = 0; i < ns; ++i)
  {
    for (int j = 0; j < nf; ++j)
    {
      sum_grades_all[i] += grades[j][i];
    }
  }

  vector<vector<int>> prev_dp(total_budget + 1, vector<int>(nf + 1, 0));
  vector<vector<int>> dp(total_budget + 1, vector<int>(nf + 1, 0));

  for (int i = 1; i <= ns * 2; ++i)
  {
    int price_index =
        (i > ns) ? ((i % ns == 0) ? ns - 1 : i % ns - 1) : (i - 1);

    for (int j = 0; j <= total_budget; ++j)
    {
      for (int k = 1; k <= nf; ++k)
      {
        dp[j][k] = prev_dp[j][k];

        if (j >= prices[price_index])
        {
          int sum_grades = prev_dp[j - prices[price_index]][k - 1] +
                           sum_grades_all[price_index];
          dp[j][k] = max(dp[j][k], sum_grades);
        }
      }
    }

    prev_dp = dp;
  }

  return dp[total_budget][nf];
}

int main()
{
  ifstream fin("sushi.in");
  ofstream fout("sushi.out");

  int task; // task number

  int nf;     // number of friends
  int ns;     // number of sushi types
  int budget; // how much each of you is willing to spend

  vector<int> prices; // prices of each sushi type
  vector<vector<int>>
      grades; // the grades you and your friends gave to each sushi type

  fin >> task;
  fin >> nf >> ns >> budget;

  prices.assign(ns, 0);
  grades.assign(nf, vector<int>(ns, 0));

  // price of each sushi
  for (int i = 0; i < ns; ++i)
  {
    fin >> prices[i];
  }

  // each friends rankings of sushi types
  for (int i = 0; i < nf; ++i)
  {
    for (int j = 0; j < ns; ++j)
    {
      fin >> grades[i][j];
    }
  }

  int ans = -1;

  switch (task)
  {
  case 1:
    ans = sushi_1(nf, ns, budget, prices, grades);
    break;
  case 2:
    ans = sushi_2(nf, ns, budget, prices, grades);
    break;
  case 3:
    ans = sushi_3(nf, ns, budget, prices, grades);
    break;
  default:
    fout << "wrong task number" << endl;
  }

  fout << ans << endl;

  return 0;
}
