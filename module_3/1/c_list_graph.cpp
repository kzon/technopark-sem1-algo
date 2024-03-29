#include "c_list_graph.h"

CListGraph::CListGraph(size_t vertices_count) : IGraph(vertices_count) {
  graph_ = new ListType[vertices_count];
}

CListGraph::CListGraph(const IGraph &other) : CListGraph(other.VerticesCount()) {
  for (size_t from = 0; from < vertices_count_; ++from) {
    auto vertices = other.GetNextVertices(from);
    for (const auto to : vertices)
      AddEdge(from, to);
  }
}

CListGraph::~CListGraph() {
  delete[] graph_;
}

void CListGraph::AddEdge(size_t from, size_t to) {
  assert(from < vertices_count_ && to < vertices_count_);
  graph_[from].push_back(to);
}

std::vector<size_t> CListGraph::GetNextVertices(size_t vertex) const {
  return {graph_[vertex].begin(), graph_[vertex].end()};
}

std::vector<size_t> CListGraph::GetPrevVertices(size_t vertex) const {
  std::vector<size_t> prev_vertices;
  for (size_t i = 0; i < vertices_count_; ++i) {
    if (i == vertex)
      continue;
    for (const size_t v : graph_[i])
      if (v == vertex)
        prev_vertices.push_back(i);
  }
  return prev_vertices;
}
