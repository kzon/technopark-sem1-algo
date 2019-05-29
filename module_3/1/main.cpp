#include <iostream>
#include <algorithm>
#include "c_matrix_graph.h"
#include "c_list_graph.h"
#include "c_set_graph.h"
#include "c_arc_graph.h"

const size_t VERTICES_COUNT = 4;

void AddEdges(IGraph &graph) {
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 2);
  graph.AddEdge(1, 3);
  graph.AddEdge(2, 3);
}

void AssertGraphsEquals(const IGraph &graph_1, const IGraph &graph_2) {
  assert(graph_1.VerticesCount() == graph_2.VerticesCount());
  for (size_t vertex = 0; vertex < graph_1.VerticesCount(); ++vertex) {
    auto next_vertices_1 = graph_1.GetNextVertices(vertex);
    auto next_vertices_2 = graph_2.GetNextVertices(vertex);
    std::sort(next_vertices_1.begin(), next_vertices_1.end());
    std::sort(next_vertices_2.begin(), next_vertices_2.end());
    assert(next_vertices_1 == next_vertices_2);
  }
}

void TestGraphCopy(const IGraph& graph) {
  CMatrixGraph matrix_graph(graph);
  AssertGraphsEquals(graph, matrix_graph);
  CListGraph list_graph(graph);
  AssertGraphsEquals(graph, list_graph);
  CSetGraph set_graph(graph);
  AssertGraphsEquals(graph, set_graph);
  CArcGraph arc_graph(graph);
  AssertGraphsEquals(graph, arc_graph);
}

void TestMatrixGraph() {
  CMatrixGraph graph(VERTICES_COUNT);
  AddEdges(graph);
  TestGraphCopy(graph);
}

void TestListGraph() {
  CListGraph graph(VERTICES_COUNT);
  AddEdges(graph);
  TestGraphCopy(graph);
}

void TestSetGraph() {
  CSetGraph graph(VERTICES_COUNT);
  AddEdges(graph);
  TestGraphCopy(graph);
}

void TestArcGraph() {
  CArcGraph graph(VERTICES_COUNT);
  AddEdges(graph);
  TestGraphCopy(graph);
}

int main() {
  TestMatrixGraph();
  TestListGraph();
  TestSetGraph();
  TestArcGraph();

  return 0;
}