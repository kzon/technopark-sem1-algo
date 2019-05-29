#include "c_arc_graph.h"

CArcGraph::CArcGraph(const IGraph &other) : CArcGraph(other.VerticesCount()) {
  for (size_t from = 0; from < vertices_count_; ++from) {
    auto vertices = other.GetNextVertices(from);
    for (const auto to : vertices)
      AddEdge(from, to);
  }
}

void CArcGraph::AddEdge(size_t from, size_t to) {
  assert(from < vertices_count_ && to < vertices_count_);
  graph_.emplace_back(from, to);
}

std::vector<size_t> CArcGraph::GetNextVertices(size_t vertex) const {
  std::vector<size_t> next_vertices;
  for (const auto &edge : graph_)
    if (edge.first == vertex)
      next_vertices.push_back(edge.second);
  return next_vertices;
}
std::vector<size_t> CArcGraph::GetPrevVertices(size_t vertex) const {
  std::vector<size_t> prev_vertices;
  for (const auto &edge : graph_)
    if (edge.second == vertex)
      prev_vertices.push_back(edge.first);
  return prev_vertices;
}
