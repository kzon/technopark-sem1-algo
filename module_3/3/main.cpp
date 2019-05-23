/*
 * Кобзев Антон АПО-11
 *
 * Задача № 3 Города
 *
 * Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается
 * в этот же город.
 * Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
 * N ≤ 10000, M ≤ 250000. Длина каждой дороги ≤ 10000.
 *
 * Формат ввода
 * Первая строка содержит число N – количество городов.
 * Вторая строка содержит число M - количество дорог.
 * Каждая следующая строка содержит описание дороги (откуда, куда, время в пути). Все указанные дороги двусторонние. Между любыми двумя городами может быть больше одной дороги.
 * Последняя строка содержит маршрут (откуда и куда нужно доехать).
 *
 * Формат вывода
 * Вывести длину самого короткого маршрута.
 */

#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <limits>
#include <cassert>

using Edge = std::pair<size_t, size_t>;

struct Graph {
  using ListType = std::vector<Edge>;

  explicit Graph(size_t vertices_count);
  ~Graph();

  void AddEdge(size_t from, size_t to, size_t weight);
  inline size_t VerticesCount() const { return vertices_count_; }
  Graph::ListType GetEdgesFromVertex(size_t vertex) const;

 private:
  ListType *graph_;
  size_t vertices_count_;
};

size_t FindShortestWay(const Graph &graph, size_t from, size_t to);

int main() {
  size_t vertices_count, edge_count, from, to, weight;
  std::cin >> vertices_count >> edge_count;
  Graph graph(vertices_count);

  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }

  std::cin >> from >> to;
  std::cout << '\n' << FindShortestWay(graph, from, to) << '\n';

  return 0;
}

Graph::Graph(size_t vertices_count) : vertices_count_(vertices_count) {
  graph_ = new ListType[vertices_count];
}

Graph::~Graph() {
  delete[] graph_;
}

void Graph::AddEdge(size_t from, size_t to, size_t weight) {
  assert(from < vertices_count_ && to < vertices_count_);
  graph_[from].push_back(Edge{to, weight});
  if (from != to)
    graph_[to].push_back(Edge{from, weight});
}

Graph::ListType Graph::GetEdgesFromVertex(size_t vertex) const {
  assert(vertex < vertices_count_);
  return graph_[vertex];
}

size_t FindShortestWay(const Graph &graph, size_t from, size_t to) {
  assert(from < graph.VerticesCount() && to < graph.VerticesCount());
  auto *distances = new size_t[graph.VerticesCount()];
  for (size_t i = 0; i < graph.VerticesCount(); ++i)
    distances[i] = std::numeric_limits<size_t>::max();
  using queue_elem = std::pair<size_t, size_t>;
  std::priority_queue<queue_elem, std::vector<queue_elem>, std::greater<queue_elem>> queue;  // Min Heap
  distances[from] = 0;
  queue.push({0, from});
  while (!queue.empty()) {
    size_t current = queue.top().second;
    queue.pop();
    for (const auto &edge : graph.GetEdgesFromVertex(current)) {
      if (distances[edge.first] > distances[current] + edge.second) {
        distances[edge.first] = distances[current] + edge.second;
        queue.push({distances[edge.first], edge.first});
      }
    }
  }

  delete[] distances;
  return distances[to];
}