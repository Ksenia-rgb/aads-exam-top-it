#include <iostream>

namespace donkeev
{
  struct Person
  {
      size_t id;
      std::string info;
  };

  struct PersonNode
  {
    Person data;
    PersonNode* next_;
    PersonNode* prev_;
  };

  struct PersonList
  {
    PersonNode* head_;
    PersonNode* tail_;
    size_t size_;
  };

  void pushBack(PersonList& list, const Person& person)
  {
    PersonNode* newNode = new PersonNode{person, nullptr, nullptr};
    
    if (!list.head_)
    {
      list.head_ = newNode;
      list.tail_ = newNode;
    }
    else
    {
      list.tail_->next_ = newNode;
      newNode->prev_ = list.tail_;
      list.tail_ = newNode;
    }
    
    ++list.size_;
  }

  bool isUniqueId(const PersonList& list, size_t id)
  {
    PersonNode* current = list.head_;
    while (current)
    {
      if (current->data.id == id)
      {
        return false;
      }
      current = current->next_;
    }
    return true;
  }

  
}

int main()
{

}
