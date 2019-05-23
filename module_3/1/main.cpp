#include <iostream>
#include "c_matrix_graph.h"
#include "c_list_graph.h"
#include "c_set_graph.h"
#include "c_arc_graph.h"

using GraphType = CListGraph;

int main() {
  size_t vertices_count, edges_count;
  std::cin >> vertices_count >> edges_count;
  GraphType graph(vertices_count);
  for (size_t i = 0; i < edges_count; ++i) {
    size_t vertex1, vertex2;
    std::cin >> vertex1 >> vertex2;
    graph.AddEdge(vertex1, vertex2);
  }

  GraphType graph_copy(graph);
  std::cout << "copy verticles count: " << graph_copy.VerticesCount() << '\n';

  size_t vertex;
  std::cout << "prev vertices for: ";
  std::cin >> vertex;
  for (const auto prev_vertex : graph_copy.GetPrevVertices(vertex))
    std::cout << prev_vertex << ' ';
  std::cout << std::endl;

  std::cout << "next vertices for: ";
  std::cin >> vertex;
  for (const auto next_vertex : graph_copy.GetNextVertices(vertex))
    std::cout << next_vertex << ' ';
  std::cout << std::endl;

  return 0;
}