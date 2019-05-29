#pragma once

#include "i_graph.h"

struct CMatrixGraph : public IGraph {
  explicit CMatrixGraph(size_t vertices_count);
  CMatrixGraph(const IGraph &other);
  ~CMatrixGraph() override;
  void AddEdge(size_t from, size_t to) override;
  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;
 private:
  size_t **graph_;
};