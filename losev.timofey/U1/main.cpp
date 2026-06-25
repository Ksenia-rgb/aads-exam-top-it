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
  Person parseLine(const std::string& line)
  {
    Person result;
    result.id = 0;
    result.info = "";
    if (line.empty())
    {
      return result;
    }
    size_t pos = 0;
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t'))
    {
      ++pos;
    }
    if (pos >= line.length())
    {
      return result;
    }
    std::string numStr = "";
    while (pos < line.length() && line[pos] >= '0' && line[pos] <= '9')
    {
      numStr += line[pos];
      ++pos;
    }
    if (numStr.empty())
    {
      return result;
    }
    result.id = std::stoull(numStr);
    while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t'))
    {
      ++pos;
    }
    if (pos >= line.length())
    {
      result.info = "";
      return result;
    }
    result.info = line.substr(pos);
    return result;
  }
  void processInput(std::istream& in, Node*& people,
                    size_t& successCount, size_t& ignoredCount)
  {
    std::string line;
    while (std::getline(in, line))
    {
      Person p = parseLine(line);
      if (p.id == 0 && p.info.empty())
      {
        ++ignoredCount;
        continue;
      }
      if (p.info.empty())
      {
        ++ignoredCount;
        continue;
      }
      if (findId(people, p.id))
      {
        ++ignoredCount;
        continue;
      }
      pushBack(people, p);
      ++successCount;
    }
  }
}

int main()
{
  return 0;
}
