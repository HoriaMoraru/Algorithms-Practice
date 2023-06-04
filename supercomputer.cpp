#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

struct Graph
{
  int N;
  std::vector<int> *dependencies;
  std::vector<int> in_degree;

  explicit Graph(int N)
  {
    this->N = N;
    dependencies = new std::vector<int>[N + 1];
    in_degree = std::vector<int>(N + 1, 0);
  }

  ~Graph()
  {
    delete[] dependencies;
  }

  void add_dependency(int v, int w)
  {
    dependencies[v].push_back(w);
    in_degree[w]++;
  }

  int calculate_context_switches(int *data_set,
                                 std::queue<int> &ready_tasks_first,
                                 std::queue<int> &switch_tasks_first)
  {
    std::queue<int> ready_tasks(ready_tasks_first);
    std::queue<int> switch_tasks(switch_tasks_first);

    std::vector<int> in_degree_temp(in_degree);

    int context_switches = 0;

    while (!ready_tasks.empty() || !switch_tasks.empty())
    {
      if (ready_tasks.empty())
      {
        context_switches++;
        ready_tasks.swap(switch_tasks);
      }

      auto task = ready_tasks.front();
      ready_tasks.pop();
      for (auto it = dependencies[task].begin();
           it != dependencies[task].end(); ++it)
      {
        int dependent = *it;
        in_degree_temp[dependent]--;
        if (in_degree_temp[dependent] == 0)
        {
          data_set[dependent] != data_set[task] ? switch_tasks.push(dependent) : ready_tasks.push(dependent);
        }
      }
    }

    return context_switches;
  }

  int min_switches(int *data_set)
  {
    int context_switches[2];

    std::queue<int> ready_tasks;
    std::queue<int> switch_tasks;

    for (int i = 1; i <= N; ++i)
    {
      if (in_degree[i] == 0)
      {
        data_set[i] == 1 ? ready_tasks.push(i) : switch_tasks.push(i);
      }
    }

    context_switches[0] =
        calculate_context_switches(data_set, ready_tasks, switch_tasks);
    context_switches[1] =
        calculate_context_switches(data_set, switch_tasks, ready_tasks);

    return std::min(context_switches[0], context_switches[1]);
  }
};

int main(void)
{
  std::ifstream fin("supercomputer.in");
  std::ofstream fout("supercomputer.out");

  int N, M;

  fin >> N >> M;

  int *data_set = new int[N + 1];

  for (int i = 1; i <= N; ++i)
  {
    fin >> data_set[i];
  }

  Graph g(N);

  for (int i = 0; i < M; ++i)
  {
    int v, w;
    fin >> v >> w;
    g.add_dependency(v, w);
  }

  auto ans = g.min_switches(data_set);

  fout << ans << '\n';

  delete[] data_set;

  return 0;
}
