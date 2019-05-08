#pragma once

#include "i_graph.h"
#include <unordered_set>

struct CSetGraph : public IGraph {
  explicit CSetGraph(size_t vertices_count);
  CSetGraph(const CSetGraph& other);
  ~CSetGraph() override;
  void AddEdge(size_t from, size_t to) override;
  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;
 private:
  using SetType = std::unordered_set<size_t>;
  SetType *graph_;
};