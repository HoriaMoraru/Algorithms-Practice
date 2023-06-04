#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>

constexpr int MAX = std::numeric_limits<int>::max();
constexpr int SOURCE = 1;

struct Graph
{
  int N;
  std::vector<std::vector<std::pair<int, int>>> edges;
  std::vector<std::vector<std::pair<int, int>>> teleport_edges;

  explicit Graph(int N)
  {
    this->N = N;
    edges = std::vector<std::vector<std::pair<int, int>>>(N + 1);
    teleport_edges = std::vector<std::vector<std::pair<int, int>>>(N + 1);
  }

  void add_edge(int v, int w, int c)
  {
    edges[v].push_back({w, c});
    edges[w].push_back({v, c});
  }

  void add_teleport_edge(int v, int w, int p)
  {
    for (int i = p; i <= N; i += p)
    {
      teleport_edges[v].push_back({w, 1});
      teleport_edges[w].push_back({v, 1});
    }
  }

  int dijkstra_teleport()
  {
    std::vector<int> d(N + 1, MAX);
    std::vector<bool> visited(N + 1, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>()>>
        cost_g;

    d[SOURCE] = 0;
    cost_g.push({0, SOURCE});

    while (!cost_g.empty())
    {
      auto [dist, node] = cost_g.top();
      cost_g.pop();
      if (visited[node])
      {
        continue;
      }
      visited[node] = true;

      for (const auto &ngh : edges[node])
      {
        if (d[ngh.first] > d[node] + ngh.second)
        {
          d[ngh.first] = d[node] + ngh.second;
          cost_g.push({d[ngh.first], ngh.first});
        }
      }

      for (const auto &ngh : teleport_edges[node])
      {
        if (d[ngh.first] > d[node] + ngh.second)
        {
          d[ngh.first] = d[node] + ngh.second;
          cost_g.push({d[ngh.first], ngh.first});
        }
      }
    }

    return d[N];
  }
};

int main()
{
  std::ifstream fin("teleportare.in");
  std::ofstream fout("teleportare.out");

  int N, M, K;

  fin >> N >> M >> K;

  Graph g(N);

  for (int i = 0; i < M; ++i)
  {
    int v, w, c;
    fin >> v >> w >> c;
    g.add_edge(v, w, c);
  }

  for (int i = 0; i < K; ++i)
  {
    int v, w, p;
    fin >> v >> w >> p;
    g.add_teleport_edge(v, w, p);
  }

  fout << g.dijkstra_teleport() << "\n";
}
