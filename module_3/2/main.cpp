#include <iostream>
#include <vector>
#include <limits>

size_t CountShortestWays(const std::vector<size_t> *graph, size_t vertex_count, size_t start, size_t finish);

int main() {
  size_t v, n, u, w;
  std::cin >> v >> n;
  auto *graph = new std::vector<size_t>[v];

  for (size_t i = 0; i < n; ++i) {
    std::cin >> u >> w;
    graph[u].push_back(w);
    graph[w].push_back(u);
  }

  std::cin >> u >> w;
  std::cout << CountShortestWays(graph, v, u, w) << '\n';

  delete[] graph;
  return 0;
}

bool *processing;
size_t shortest_way_length = std::numeric_limits<size_t>::max() - 1,
    shortest_ways_count = 0;

void DFS(const std::vector<size_t> *graph,
         size_t current,
         size_t finish,
         size_t depth) {
  if (depth > shortest_way_length)
    return;

  processing[current] = true;
  for (const size_t i : graph[current]) {
    if (i == finish) {
      if (depth < shortest_way_length) {
        shortest_way_length = depth;
        shortest_ways_count = 1;
      } else if (depth == shortest_way_length)
        shortest_ways_count++;
      break;  // При кратных ребрах будет WA
    } else if (!processing[i]) {
      for (const size_t j : graph[current])
        processing[j] = true;
      DFS(graph, i, finish, depth + 1);
      for (const size_t j : graph[current])
        processing[j] = false;
    }
  }
  processing[current] = false;
}

size_t CountShortestWays(const std::vector<size_t> *graph, size_t vertex_count, size_t start, size_t finish) {
  processing = new bool[vertex_count]();
  DFS(graph, start, finish, 0);
  delete[] processing;
  return shortest_ways_count;
}
