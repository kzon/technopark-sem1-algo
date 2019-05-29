#include "c_matrix_graph.h"

CMatrixGraph::CMatrixGraph(size_t vertices_count) : IGraph(vertices_count) {
  graph_ = new size_t *[vertices_count];
  for (size_t i = 0; i < vertices_count; ++i)
    graph_[i] = new size_t[vertices_count]();
}

CMatrixGraph::CMatrixGraph(const IGraph &other) : CMatrixGraph(other.VerticesCount()) {
  for (size_t from = 0; from < vertices_count_; ++from) {
    auto vertices = other.GetNextVertices(from);
    for (const auto to : vertices)
      AddEdge(from, to);
  }
}

CMatrixGraph::~CMatrixGraph() {
  for (size_t i = 0; i < vertices_count_; ++i)
    delete[] graph_[i];
  delete[] graph_;
}

void CMatrixGraph::AddEdge(size_t from, size_t to) {
  assert(from < vertices_count_ && to < vertices_count_);
  graph_[from][to]++;
}

std::vector<size_t> CMatrixGraph::GetNextVertices(size_t vertex) const {
  std::vector<size_t> next_vertices;
  for (size_t i = 0; i < vertices_count_; ++i)
    for (size_t j = 0; j < graph_[vertex][i]; ++j)
      next_vertices.push_back(i);
  return next_vertices;
}

std::vector<size_t> CMatrixGraph::GetPrevVertices(size_t vertex) const {
  std::vector<size_t> prev_vertices;
  for (size_t i = 0; i < vertices_count_; ++i)
    for (size_t j = 0; j < graph_[i][vertex]; ++j)
      prev_vertices.push_back(i);
  return prev_vertices;
}