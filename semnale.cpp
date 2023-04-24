#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

constexpr int MOD = 1'000'000'007;

/*
First implementation of type1 , using a three dimensional matrix which for
some reason skyrockets the execution time to more than 5x. I implemented the
same algorithm logic below , but using 2 two dimensional matrices, which has
a way less execution time, but keeps the same time complexity , although it
has a higher space complexity .

int semnale_type1(int zeros, int ones) {
  const int total_bytes = zeros + ones;

  vector<vector<vector<int>>> dp(
      total_bytes + 1, vector<vector<int>>(ones + 1, vector<int>(2, 0)));

  dp[1][0][0] = 1;
  dp[1][1][1] = 1;

  dp[2][0][0] = 1;
  dp[2][1][0] = 1;
  dp[2][1][1] = 1;

  for (int i = 3; i <= total_bytes; ++i) {
    int max_ones = min(i, ones);

    for (int j = 0; j <= max_ones; ++j) {
      dp[i][j][0] = (j == 0) ? 1 : (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
      dp[i][j][1] = (j == 0) ? 0 : dp[i - 1][j - 1][0];
    }
  }
  return (dp[total_bytes][ones][0] + dp[total_bytes][ones][1]) % MOD;
}
*/

int semnale_type1(int zeros, int ones)
{
  const int total_bytes = zeros + ones;

  vector<vector<int>> dp_one_last(total_bytes + 1, vector<int>(ones + 1, 0));
  vector<vector<int>> dp_zero_last(total_bytes + 1, vector<int>(ones + 1, 0));

  dp_zero_last[1][0] = 1;
  dp_one_last[1][1] = 1;

  dp_zero_last[2][0] = 1;
  dp_zero_last[2][1] = 1;
  dp_one_last[2][1] = 1;

  for (int i = 3; i <= total_bytes; ++i)
  {
    dp_zero_last[i][0] = 1;
    int max_ones = min(ones, i);

    for (int j = 1; j <= max_ones; ++j)
    {
      dp_zero_last[i][j] = (dp_zero_last[i - 1][j] + dp_one_last[i - 1][j]) % MOD;
      dp_one_last[i][j] = dp_zero_last[i - 1][j - 1];
    }
  }

  return (dp_zero_last[total_bytes][ones] + dp_one_last[total_bytes][ones]) % MOD;
}

int semnale_type2(int zeros, int ones)
{
  const int total_bytes = zeros + ones;

  vector<vector<int>> dp_one_last(total_bytes + 1, vector<int>(ones + 1, 0));
  vector<vector<int>> dp_zero_last(total_bytes + 1, vector<int>(ones + 1, 0));

  dp_zero_last[1][0] = 1;
  dp_one_last[1][1] = 1;

  dp_zero_last[2][0] = 1;
  dp_zero_last[2][1] = 1;
  dp_one_last[2][1] = 1;
  dp_one_last[2][2] = 1;

  for (int i = 3; i <= total_bytes; ++i)
  {
    dp_zero_last[i][0] = 1;
    int max_ones = min(ones, i);

    for (int j = 1; j <= max_ones; ++j)
    {
      dp_zero_last[i][j] = (dp_zero_last[i - 1][j] + dp_one_last[i - 1][j]) % MOD;
      dp_one_last[i][j] = (dp_zero_last[i - 1][j - 1] + dp_zero_last[i - 2][j - 2]) % MOD;
    }
  }

  return (dp_zero_last[total_bytes][ones] + dp_one_last[total_bytes][ones]) % MOD;
}

int main()
{
  ifstream fin("semnale.in");
  ofstream fout("semnale.out");

  int sig_type, zeros, ones;

  fin >> sig_type >> zeros >> ones;

  switch (sig_type)
  {
  case 1:
    fout << semnale_type1(zeros, ones);
    break;
  case 2:
    fout << semnale_type2(zeros, ones);
    break;
  default:
    fout << "wrong task number" << endl;
  }

  return 0;
}
