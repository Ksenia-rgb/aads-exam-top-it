#ifndef BST_HPP
#define BST_HPP

#include <memory>

namespace vasyakin
{
  template< class Key, class Value >
  struct BstNode
  {
    Key key;
    Value value;
    BstNode< Key, Value >* left;
    BstNode< Key, Value >* right;
  };

  template< class Key, class Value >
  void clearBst(BstNode< Key, Value >* node) noexcept
  {
    if (node == nullptr)
    {
      return;
    }

    clearBst(node->left);
    clearBst(node->right);
    delete node;
  }

  template< class Key, class Value >
  BstNode< Key, Value >* findBst(BstNode< Key, Value >* node, const Key& key)
  {
    while (node != nullptr)
    {
      if (key < node->key)
      {
        node = node->left;
      }
      else if (node->key < key)
      {
        node = node->right;
      }
      else
      {
        return node;
      }
    }

    return nullptr;
  }

  template< class Key, class Value >
  BstNode< Key, Value >* insertBst(BstNode< Key, Value >*& root, const Key& key, const Value& value)
  {
    BstNode< Key, Value >** link = std::addressof(root);
    while (*link != nullptr)
    {
      if (key < (*link)->key)
      {
        link = std::addressof((*link)->left);
      }
      else if ((*link)->key < key)
      {
        link = std::addressof((*link)->right);
      }
      else
      {
        return *link;
      }
    }

    BstNode< Key, Value >* created = new BstNode< Key, Value >{ key, value, nullptr, nullptr };
    *link = created;

    return created;
  }

  template< class Key, class Value, class Visitor >
  void inorderBst(BstNode< Key, Value >* node, Visitor& visit)
  {
  if (node == nullptr)
  {
    return;
  }

  inorderBst(node->left, visit);
  visit(node->key, node->value);
  inorderBst(node->right, visit);
  }

}

#endif
