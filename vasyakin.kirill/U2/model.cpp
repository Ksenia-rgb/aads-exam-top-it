#include "model.hpp"

namespace vasyakin
{
  namespace detail
  {

    void clearVertex(Vertex& vertex) noexcept;
    void clearAdjacency(Adjacency* node) noexcept;

  }
}

void vasyakin::detail::clearAdjacency(Adjacency* node) noexcept
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

void vasyakin::detail::clearVertex(Vertex& vertex) noexcept
{
  clearAdjacency(vertex.meetings);
  vertex.meetings = nullptr;
}

vasyakin::Graph* vasyakin::obtainVertex(Graph*& root, size_t id)
{
  Graph* found = findBst(root, id);
  if (found != nullptr)
  {
    return found;
  }

  Vertex empty{std::string(), false, nullptr};
  return insertBst(root, id, empty);
}

void vasyakin::addMeeting(Graph*& root, size_t first, size_t second, size_t duration)
{
  if (first == second)
  {
    return;
  }

  Graph* left = obtainVertex(root, first);
  Graph* right = obtainVertex(root, second);

  ListNode< size_t >* dummy = nullptr;
  Adjacency* leftEdge = insertBst(left->value.meetings, second, dummy);

  insertSorted(leftEdge->value, duration);

  Adjacency* rightEdge = insertBst(right->value.meetings, first, dummy);

  insertSorted(rightEdge->value, duration);
}

void vasyakin::clearGraph(Graph* root) noexcept
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
