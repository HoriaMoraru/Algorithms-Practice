#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int MOD = 1'000'000'007;

string decode(string &enc)
{
  int read_index = 0;
  int enc_len = enc.length();
  string decoded = "";
  char current = '\0';
  int char_nr = 0;

  while (read_index < enc_len)
  {

    char c = enc[read_index];
    if (isdigit(c))
    {
      char_nr = 10 * char_nr + (c - '0');
    }
    else
    {
      if (current != '\0')
      {
        for (int i = 0; i < char_nr; ++i)
        {
          decoded += current;
        }
      }
      current = c;
      char_nr = 0;
    }
    read_index++;
  }
  if (current != '\0')
  {
    for (int i = 0; i < char_nr; ++i)
    {
      decoded += current;
    }
  }
  return decoded;
}

int badgpt(string &enc)
{
  const string decoded = decode(enc);
  const int decoded_len = decoded.length();

  vector<int> dp(decoded_len + 1, 0);

  dp[0] = 1;
  dp[1] = 1;

  for (int i = 2; i <= decoded_len; ++i)
  {
    if (decoded[i - 1] != 'n' && decoded[i - 1] != 'u')
    {
      dp[i] = dp[i - 1];
    }
    else
    {
      const string possible_pair = decoded.substr(i - 2, 2);
      dp[i] = dp[i - 1];
      if (possible_pair.compare("nn") == 0 || possible_pair.compare("uu") == 0)
      {
        dp[i] = (dp[i] + dp[i - 2]) % MOD;
      }
    }
  }

  return dp[decoded_len] % MOD;
}

int main()
{
  ifstream fin("badgpt.in");
  ofstream fout("badgpt.out");

  string encoding;

  fin >> encoding;

  int res = badgpt(encoding);

  fout << res << endl;

  return 0;
}