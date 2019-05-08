#include "c_arc_graph.h"

CArcGraph::CArcGraph(const CArcGraph &other) : CArcGraph(other.vertices_count_) {
  graph_ = other.graph_;
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
