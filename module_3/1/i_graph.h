#pragma once

#include <vector>

struct IGraph {
  explicit IGraph(size_t vertices_count) : vertices_count_(vertices_count) {}
  virtual ~IGraph() = default;

  virtual void AddEdge(size_t from, size_t to) = 0;
  virtual size_t VerticesCount() const { return vertices_count_; }
  virtual std::vector<size_t> GetNextVertices(size_t vertex) const = 0;
  virtual std::vector<size_t> GetPrevVertices(size_t vertex) const = 0;
 protected:
  size_t vertices_count_;
};
