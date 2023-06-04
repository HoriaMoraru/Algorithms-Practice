#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

struct Graph
{
  int N;
  std::vector<std::vector<int>> railways;
  std::vector<std::vector<int>> reverse_railways;
  std::vector<int> parent;
  std::vector<int> found;
  std::vector<int> low_link;
  std::vector<bool> in_stack;
  std::stack<int> visited;
  std::vector<int> in_degree;

  explicit Graph(int N)
  {
    this->N = N;
    railways = std::vector<std::vector<int>>(N + 1);
    reverse_railways = std::vector<std::vector<int>>(N + 1);
    parent = std::vector<int>(N + 1, -1);
    found = std::vector<int>(N + 1, -1);
    low_link = std::vector<int>(N + 1, -1);
    in_stack = std::vector<bool>(N + 1, false);
    in_degree = std::vector<int>(N + 1, 0);
  }

  void add_railway(int v, int w)
  {
    railways[v].push_back(w);
    reverse_railways[w].push_back(v);
    in_degree[w]++;
  }

  int get_min_railways(int S)
  {
    int time = 0;
    int min_railways = 0;
    for (int i = 1; i <= N; ++i)
    {
      if (parent[i] == -1)
      {
        parent[i] = i;
        tarjan_dfs(i, time, S, min_railways);
      }
    }

    return min_railways;
  }

  void tarjan_dfs(int n, int &time, int S, int &min_railways)
  {
    time++;

    found[n] = time;
    low_link[n] = found[n];
    visited.push(n);
    in_stack[n] = true;

    for (auto it = railways[n].begin(); it != railways[n].end(); ++it)
    {
      auto ngh = *it;
      if (parent[ngh] != -1)
      {
        if (in_stack[ngh])
        {
          low_link[n] = std::min(low_link[n], found[ngh]);
        }
        continue;
      }

      parent[ngh] = n;
      tarjan_dfs(ngh, time, S, min_railways);
      low_link[n] = std::min(low_link[n], low_link[ngh]);
    }

    if (low_link[n] == found[n])
    {
      bool found_source = false;
      std::vector<int> scc;
      do
      {
        auto v = visited.top();
        visited.pop();
        in_stack[v] = false;

        if (v == S)
        {
          found_source = true;
        }

        scc.push_back(v);
      } while (scc.back() != n);

      if (!found_source)
      {
        if (scc.size() == 1)
        {
          auto first = scc.front();
          in_degree[first] == 0 ? min_railways++ : min_railways;
        }
        else
        {
          bool found_out_edge = false;
          for (const auto &n_scc : scc)
          {
            for (auto it = reverse_railways[n_scc].begin();
                 it != reverse_railways[n_scc].end(); ++it)
            {
              auto ngh = *it;
              if (std::find(scc.begin(), scc.end(), ngh) == scc.end())
              {
                found_out_edge = true;
                break;
              }
            }

            if (found_out_edge)
            {
              break;
            }
          }
          !found_out_edge ? min_railways++ : min_railways;
        }
      }
    }
  }
};

int main(void)
{
  std::ifstream fin("ferate.in");
  std::ofstream fout("ferate.out");

  int N, M, S;
  fin >> N >> M >> S;

  Graph g(N);

  for (int i = 0; i < M; i++)
  {
    int v, w;
    fin >> v >> w;
    g.add_railway(v, w);
  }

  fout << g.get_min_railways(S) << "\n";

  return 0;
}
