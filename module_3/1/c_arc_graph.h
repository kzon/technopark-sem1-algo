#pragma once

#include "i_graph.h"

struct CArcGraph : public IGraph {
  explicit CArcGraph(size_t vertices_count) : IGraph(vertices_count) {}
  CArcGraph(const CArcGraph& other);
  void AddEdge(size_t from, size_t to) override;
  std::vector<size_t> GetNextVertices(size_t vertex) const override;
  std::vector<size_t> GetPrevVertices(size_t vertex) const override;
 private:
  std::vector<std::pair<size_t, size_t>> graph_;
};