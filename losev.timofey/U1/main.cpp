#include <iostream>
#include <string>

namespace losev
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct Node
  {
    Person data;
    Node* next;
  };

  Node* createNode(const Person& person)
  {
    Node* node = new Node;
    node->data = person;
    node->next = nullptr;
    return node;
  }

  void pushBack(Node*& head, const Person& person)
  {
    Node* newNode = createNode(person);

    if (head == nullptr)
    {
      head = newNode;
      return;
    }

    Node* current = head;
    while (current->next != nullptr)
    {
      current = current->next;
    }
    current->next = newNode;
  }

  bool findId(const Node* head, size_t id)
  {
    const Node* current = head;
    while (current != nullptr)
    {
      if (current->data.id == id)
      {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  void clearList(Node*& head)
  {
    while (head != nullptr)
    {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  size_t getSize(const Node* head)
  {
    size_t count = 0;
    const Node* current = head;
    while (current != nullptr)
    {
      ++count;
      current = current->next;
    }
    return count;
  }
}

int main()
{
  return 0;
}
