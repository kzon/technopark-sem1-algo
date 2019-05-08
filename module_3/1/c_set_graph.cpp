#include "c_set_graph.h"

CSetGraph::CSetGraph(size_t vertices_count) : IGraph(vertices_count) {
  graph_ = new SetType[vertices_count];
}

CSetGraph::CSetGraph(const CSetGraph &other) : CSetGraph(other.vertices_count_) {
  for (size_t i = 0; i < vertices_count_; ++i)
    graph_[i] = other.graph_[i];
}

CSetGraph::~CSetGraph() {
  delete[] graph_;
}

void CSetGraph::AddEdge(size_t from, size_t to) {
  assert(from < vertices_count_ && to < vertices_count_);
  graph_[from].insert(to);
}

std::vector<size_t> CSetGraph::GetNextVertices(size_t vertex) const {
  return {graph_[vertex].begin(), graph_[vertex].end()};
}
std::vector<size_t> CSetGraph::GetPrevVertices(size_t vertex) const {
  std::vector<size_t> prev_vertices;
  for (size_t i = 0; i < vertices_count_; ++i) {
    if (i == vertex)
      continue;
    if (graph_[i].find(vertex) != graph_[i].end())
        prev_vertices.push_back(i);
  }
  return prev_vertices;
}


