#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <array>
#include <unordered_map>

struct Graph
{
  int N;
  int Q;
  std::vector<std::array<int, 2>> questions;
  std::vector<std::vector<int>> deposits;
  std::vector<int> can_reach;
  std::vector<bool> visited;
  std::unordered_map<int, int> index_to_deposit;
  std::unordered_map<int, int> deposit_to_index;

  Graph(int N, int Q)
  {
    this->N = N;
    this->Q = Q;
    deposits = std::vector<std::vector<int>>(N + 1);
    can_reach = std::vector<int>(N + 1, 0);
    visited = std::vector<bool>(N + 1, false);
  }

  void add_question(int d, int e)
  {
    questions.push_back({d, e});
  }

  void add_deposit(int d, int t)
  {
    deposits[d].push_back(t);
  }

  void dfs(const int &n, int &index)
  {
    visited[n] = true;
    index_to_deposit[index] = n;
    deposit_to_index[n] = index;
    can_reach[n] = 1;

    for (const auto &ngh : deposits[n])
    {
      if (!visited[ngh])
      {
        index++;
        dfs(ngh, index);
        can_reach[n] += can_reach[ngh];
      }
    }
  }

  void answer_questions(std::ofstream &fout)
  {
    int index = 0;
    dfs(1, index);
    for (int i = 0; i < Q; ++i)
    {
      int d = questions[i][0];
      int e = questions[i][1];

      if (e > can_reach[d] - 1)
      {
        fout << -1 << "\n";
      }
      else
      {
        int index = deposit_to_index[d];
        int answer = index_to_deposit[index + e];
        fout << answer << "\n";
      }
    }
  }
};

int main(void)
{
  std::ifstream fin("magazin.in");
  std::ofstream fout("magazin.out");

  int N, Q, d;

  fin >> N >> Q;

  Graph g(N, Q);

  for (int i = 2; i < N + 1; ++i)
  {
    fin >> d;
    g.add_deposit(d, i);
  }

  for (int i = 0; i < Q; ++i)
  {
    int v, w;
    fin >> v >> w;
    g.add_question(v, w);
  }

  g.answer_questions(fout);

  return 0;
}
