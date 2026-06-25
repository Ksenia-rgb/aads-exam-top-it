#include "model.hpp"

#include <cstddef>
#include <string>
#include <utility>

#include "array.hpp"
#include "hashmap.hpp"

namespace burukov
{

  Graph makeGraph()
  {
    Graph graph{makeArray< Vertex >(4), makeHashMap< size_t, size_t >(16)};
    return graph;
  }

  void clearGraph(Graph& graph)
  {
    for (size_t i = 0; i < graph.vertices.size; ++i)
    {
      clearArray(graph.vertices.data[i].edges);
    }
    clearArray(graph.vertices);
    clearHashMap(graph.index);
  }

  Vertex* findVertex(Graph& graph, size_t id)
  {
    size_t* pos = findHashMap(graph.index, id);
    if (!pos)
    {
      return nullptr;
    }
    return std::addressof(graph.vertices.data[*pos]);
  }

  Vertex& obtainVertex(Graph& graph, size_t id)
  {
    Vertex* found = findVertex(graph, id);
    if (found)
    {
      return *found;
    }
    Vertex vertex{id, "", false, makeArray< Edge >(2)};
    size_t newPos = graph.vertices.size;
    try
    {
      pushBackArray(graph.vertices, std::move(vertex));
    }
    catch (...)
    {
      clearArray(vertex.edges);
      throw;
    }
    insertHashMap(graph.index, id, newPos);
    return graph.vertices.data[newPos];
  }

  void addMeeting(Graph& graph, size_t first, size_t second, size_t duration)
  {
    if (first == second)
    {
      return;
    }
    obtainVertex(graph, first);
    obtainVertex(graph, second);
    Vertex* left = findVertex(graph, first);
    Vertex* right = findVertex(graph, second);
    Edge forward{second, duration};
    pushBackArray(left->edges, std::move(forward));
    Edge backward{first, duration};
    pushBackArray(right->edges, std::move(backward));
  }

}
