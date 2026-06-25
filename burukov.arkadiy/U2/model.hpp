#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstddef>
#include <string>

#include "array.hpp"
#include "hashmap.hpp"

namespace burukov
{

  struct Edge
  {
    size_t partner;
    size_t duration;
  };

  struct Vertex
  {
    size_t id;
    std::string description;
    bool described;
    darray< Edge > edges;
  };

  struct Graph
  {
    darray< Vertex > vertices;
    hashMap< size_t, size_t > index;
  };

  Graph makeGraph();
  void clearGraph(Graph& graph);
  Vertex& obtainVertex(Graph& graph, size_t id);
  Vertex* findVertex(Graph& graph, size_t id);
  void addMeeting(Graph& graph, size_t first, size_t second, size_t duration);

}

#endif
