#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <class T>
struct comparator
{
  bool descending;

  comparator(bool des = false) { descending = des; }

  bool operator()(const T &a, const T &b) const
  {
    if (descending)
    {
      return a > b;
    }
    else
    {
      return a < b;
    }
  }
};

int64_t nostory_1(vector<int> &fl, vector<int> &sl)
{
  sort(fl.begin(), fl.end(), comparator<int>());
  sort(sl.begin(), sl.end(), comparator<int>(true));

  int64_t sum = 0;

  for (auto it_fl = fl.begin(), it_sl = sl.begin(); it_fl != fl.end(); ++it_fl, ++it_sl)
  {
    sum += max(*it_fl, *it_sl);
  }

  return sum;
}

/*
This commented function also works but I found that using min and max heaps
reduces the time complexity to O(N) while the implementation below would be
O(NlogN).

int64_t nostory_2(vector<int> &fl, vector<int> &sl, int moves)
{
    int64_t sum = 0;
    int fe, se;
    vector<int> min_vec;
    vector<int> max_vec;
    int local_max;

    moves = min(moves, int(fl.size()));

    for (auto it_fl = fl.begin(), it_sl = sl.begin(); it_fl != fl.end();
++it_fl, ++it_sl)
    {
        fe = *it_fl;
        se = *it_sl;
        local_max = max(fe, se);
        min_vec.push_back(min(fe, se));
        max_vec.push_back(local_max);
        sum += local_max;
    }

    sort(max_vec.begin(), max_vec.end(), comparator<int>());
    sort(min_vec.begin(), min_vec.end(), comparator<int>(true));

    int curent_move = 0;

    while (curent_move < moves)
    {
        min_vec[curent_move] > max_vec[curent_move] ? sum += (min_vec[curent_move] - max_vec[curent_move]) : sum; curent_move++;
    }

    return sum;
}
*/

int64_t nostory_2(vector<int> &fl, vector<int> &sl, int moves)
{
  int64_t sum = 0;
  priority_queue<int> min_heap;
  priority_queue<int, vector<int>, comparator<int>> max_heap(comparator<int>(true));

  moves = min(moves, int(fl.size()));

  for (auto it_fl = fl.begin(), it_sl = sl.begin(); it_fl != fl.end(); ++it_fl, ++it_sl)
  {
    int fe = *it_fl;
    int se = *it_sl;
    int local_max = max(fe, se);

    max_heap.push(local_max);
    min_heap.push(min(fe, se));

    sum += local_max;
  }

  while (moves > 0)
  {
    int min_val = min_heap.top();
    int max_val = max_heap.top();

    if (min_val > max_val)
    {
      sum += (min_val - max_val);
    }
    else
    {
      break;
    }

    min_heap.pop();
    max_heap.pop();

    moves--;
  }

  return sum;
}

vector<int> ReadVector(istream &is, int size)
{
  vector<int> vec(size);
  for (auto &num : vec)
  {
    is >> num;
  }
  return vec;
}

int main()
{
  ifstream fin("nostory.in");
  ofstream fout("nostory.out");

  int task;
  fin >> task;

  int size, moves;
  if (task == 1)
  {
    fin >> size;
  }
  else
  {
    fin >> size >> moves;
  }

  auto a = ReadVector(fin, size);
  auto b = ReadVector(fin, size);

  auto res = task == 1 ? nostory_1(a, b) : nostory_2(a, b, moves);
  fout << res << "\n";

  return 0;
}
