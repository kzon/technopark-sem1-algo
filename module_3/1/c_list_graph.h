#pragma once

#include <vector>
#include "i_graph.h"

struct CListGraph : public IGraph {
  explicit CListGraph(size_t vertices_count);
  CListGraph(const IGraph &other);
  ~CListGraph() override;
  void AddEdge(size_t from, size_t to) override;
  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;
 private:
  using ListType = std::vector<size_t>;
  ListType* graph_;
};