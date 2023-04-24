#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

int64_t feribot(const int max_feris, const vector<int64_t> &cars)
{
  if (max_feris < 1)
  {
    return -1;
  }

  int64_t low = *(max_element(cars.begin(), cars.end()));
  int64_t high = accumulate(cars.begin(), cars.end(), 0LL);
  int64_t mid;
  int nr_feris;
  int64_t current_cost;

  while (low < high)
  {
    nr_feris = 1;
    current_cost = 0;
    mid = low + ((high - low) >> 1);

    for (auto &car : cars)
    {
      if (current_cost + car <= mid)
      {
        current_cost += car;
        continue;
      }
      else
      {
        nr_feris++;
        if (nr_feris > max_feris)
        {
          break;
        }
        current_cost = car;
      }
    }
    if (nr_feris <= max_feris)
    {
      high = mid;
    }
    else
    {
      low = mid + 1;
    }
  }
  return low;
}

vector<int64_t> ReadVector(istream &is, int size)
{
  vector<int64_t> vec(size);
  for (auto &num : vec)
  {
    is >> num;
  }
  return vec;
}

int main()
{
  ifstream fin("feribot.in");
  ofstream fout("feribot.out");

  int size, max_feris;
  fin >> size >> max_feris;

  vector<int64_t> cars = ReadVector(fin, size);

  int64_t res = feribot(max_feris, cars);

  fout << res << endl;

  return 0;
}