#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <limits>
#include <cassert>

using Edge = std::pair<size_t, size_t>;

struct CListGraph {
  using ListType = std::list<Edge>;

  explicit CListGraph(size_t vertices_count);
  ~CListGraph();

  void AddEdge(size_t from, size_t to, size_t weight);
  inline size_t VerticesCount() const { return vertices_count_; }
  inline CListGraph::ListType GetEdgesFromVertex(size_t vertex) const;

 private:
  ListType *graph_;
  size_t vertices_count_;
};

size_t FindShortestWay(const CListGraph &graph, size_t from, size_t to);

int main() {
  size_t vertices_count, edge_count, from, to, weight;
  std::cin >> vertices_count >> edge_count;
  CListGraph graph(vertices_count);

  for (size_t i = 0; i < edge_count; ++i) {
    std::cin >> from >> to >> weight;
    graph.AddEdge(from, to, weight);
  }

  std::cin >> from >> to;
  assert(from < vertices_count && to < vertices_count);
  std::cout << '\n' << FindShortestWay(graph, from, to) << '\n';

  return 0;
}

CListGraph::CListGraph(size_t vertices_count) : vertices_count_(vertices_count) {
  graph_ = new ListType[vertices_count];
}

CListGraph::~CListGraph() {
  delete[] graph_;
}

void CListGraph::AddEdge(size_t from, size_t to, size_t weight) {
  assert(from < vertices_count_ && to < vertices_count_);
  graph_[from].push_back(Edge{to, weight});
  if (from != to)
    graph_[to].push_back(Edge{from, weight});
}

CListGraph::ListType CListGraph::GetEdgesFromVertex(size_t vertex) const {
  return graph_[vertex];
}

size_t FindShortestWay(const CListGraph &graph, size_t from, size_t to) {
  auto *distances = new size_t[graph.VerticesCount()];
  for (size_t i = 0; i < graph.VerticesCount(); ++i)
    distances[i] = std::numeric_limits<size_t>::max();
  using queue_elem = std::pair<size_t, size_t>;
  std::priority_queue<queue_elem, std::vector<queue_elem>, std::greater<queue_elem>> queue;
  distances[from] = 0;
  queue.push(std::make_pair(0, from));
  while (!queue.empty()) {
    size_t current = queue.top().second;
    queue.pop();
    for (const auto &edge : graph.GetEdgesFromVertex(current)) {
      if (distances[edge.first] > distances[current] + edge.second) {
        distances[edge.first] = distances[current] + edge.second;
        queue.push(std::make_pair(distances[edge.first], edge.first));
      }
    }
  }

  delete[] distances;
  return distances[to];
}