#include "model.hpp"

namespace sedov
{
  namespace detail
  {
    void clearVertex(Vertex & vertex) noexcept;
    void clearAdjacency(Adjacency * node) noexcept;
  }
}

void sedov::detail::clearAdjacency(Adjacency * node) noexcept
{
  if (node == nullptr)
  {
    return;
  }
  clearAdjacency(node->left);
  clearAdjacency(node->right);
  clearList(node->value);
  delete node;
}

void sedov::detail::clearVertex(Vertex & vertex) noexcept
{
  clearAdjacency(vertex.meetings);
  vertex.meetings = nullptr;
}

sedov::Graph * sedov::obtainVertex(Graph *& root, size_t id)
{
  Graph * found = findBst(root, id);
  if (found != nullptr)
  {
    return found;
  }
  Vertex empty{ std::string(), false, nullptr };
  return insertBst(root, id, empty);
}

void sedov::addMeeting(Graph *& root, size_t first, size_t second, size_t duration)
{
  if (first == second)
  {
    return;
  }
  Graph * left = obtainVertex(root, first);
  Graph * right = obtainVertex(root, second);
  ListNode< size_t > * dummy = nullptr;
  Adjacency * leftEdge = insertBst(left->value.meetings, second, dummy);
  insertSorted(leftEdge->value, duration);
  Adjacency * rightEdge = insertBst(right->value.meetings, first, dummy);
  insertSorted(rightEdge->value, duration);
}

void sedov::clearGraph(Graph * root) noexcept
{
  if (root == nullptr)
  {
    return;
  }
  clearGraph(root->left);
  clearGraph(root->right);
  detail::clearVertex(root->value);
  delete root;
}
