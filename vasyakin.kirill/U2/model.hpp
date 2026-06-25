#ifndef MODEL_HPP
#define MODEL_HPP

#include <cstddef>
#include <string>
#include "bstree.hpp"
#include "sorted_list.hpp"

namespace vasyakin
{

  using Adjacency = BstNode< size_t, ListNode< size_t >* >;

  struct Vertex
  {
    std::string description;
    bool described;
    Adjacency* meetings;
  };

  using Graph = BstNode< size_t, Vertex >;

  Graph* obtainVertex(Graph*& root, std::size_t id);
  void addMeeting(Graph*& root, std::size_t first, size_t second, size_t duration);
  void clearGraph(Graph* root) noexcept;
}

#endif
