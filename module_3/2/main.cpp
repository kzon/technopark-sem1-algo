#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cassert>

size_t CountShortestWays(const std::vector<size_t> *graph, size_t vertex_count, size_t start, size_t finish);

int main() {
  size_t v, n, u, w;
  std::cin >> v >> n;
  auto *graph = new std::vector<size_t>[v];

  for (size_t i = 0; i < n; ++i) {
    std::cin >> u >> w;
    assert(u < v && w < v);
    graph[u].push_back(w);
    if (u != w)
      graph[w].push_back(u);
  }

  std::cin >> u >> w;
  assert(u < v && w < v);
  std::cout << CountShortestWays(graph, v, u, w) << '\n';

  delete[] graph;
  return 0;
}

size_t CountShortestWays(const std::vector<size_t> *graph, size_t vertex_count, size_t start, size_t finish) {
  std::vector<size_t> way_lengths(vertex_count, std::numeric_limits<size_t>::max() - 1);
  std::vector<size_t> way_counts(vertex_count, 0);
  std::vector<size_t> visited(vertex_count, false);
  std::queue<size_t> queue;

  way_lengths[start] = 0;
  way_counts[start] = 1;
  queue.push(start);
  visited[start] = true;

  while (!queue.empty()) {
    size_t current = queue.front();
    queue.pop();
    for (const size_t vertex : graph[current]) {
      if (!visited[vertex]) {
        queue.push(vertex);
        visited[vertex] = true;
      }
      if (way_lengths[current] + 1 < way_lengths[vertex]) {
        way_lengths[vertex] = way_lengths[current] + 1;
        way_counts[vertex] = way_counts[current];
      } else if (way_lengths[current] + 1 == way_lengths[vertex])
        way_counts[vertex] += way_counts[current];
    }
  }

  return way_counts[finish];
}