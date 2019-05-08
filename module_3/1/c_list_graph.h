#pragma once

#include <list>
#include "i_graph.h"

struct CListGraph : public IGraph {
  explicit CListGraph(size_t vertices_count);
  CListGraph(const CListGraph &other);
  ~CListGraph() override;
  void AddEdge(size_t from, size_t to) override;
  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;
 private:
  using ListType = std::list<size_t>;
  ListType* graph_;
};