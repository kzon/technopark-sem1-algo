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
    graph[w].push_back(u);
  }

  std::cin >> u >> w;
  assert(u < v && w < v);
  std::cout << CountShortestWays(graph, v, u, w) << '\n';

  delete[] graph;
  return 0;
}

size_t CountShortestWays(const std::vector<size_t> *graph, size_t vertex_count, size_t start, size_t finish) {
  auto *way_lengths = new size_t[vertex_count];
  // @todo
  for (size_t i = 0; i < vertex_count; ++i)
    way_lengths[i] = std::numeric_limits<size_t>::max() - 1;
  auto *way_counts = new size_t[vertex_count]();
  std::queue<size_t> queue;

  way_lengths[start] = 0;
  way_counts[start] = 1;
  queue.push(start);

  while (!queue.empty()) {
    size_t current = queue.front();
    queue.pop();
    for (const size_t vertex : graph[current]) {
      if (way_lengths[current] + 1 < way_lengths[vertex]) {
        queue.push(vertex);
        way_lengths[vertex] = way_lengths[current] + 1;
        way_counts[vertex] = way_counts[current];
      } else if (way_lengths[current] + 1 == way_lengths[vertex])
        way_counts[vertex] += way_counts[current];
    }
  }

  delete[] way_lengths;
  delete[] way_counts;
  return way_counts[finish];
}
