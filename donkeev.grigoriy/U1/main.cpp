#include <iostream>
#include <exception>

namespace donkeev
{
  struct Person
  {
      size_t id;
      std::string info;
  };

  struct PersonNode
  {
    Person* data;
    PersonNode* next_;
    PersonNode* prev_;
  };

  struct PersonList
  {
    PersonNode* head_;
    PersonNode* tail_;
    size_t size_;
  };

  void pushBack(PersonList& list, Person* person)
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
      if (current->data->id == id)
      {
        return false;
      }
      current = current->next_;
    }
    return true;
  }

  bool isNumber(const std::string& str)
  {
    if (str.empty())
    {
      return false;
    }
    for (char ch : str)
    {
      if (!std::isdigit(static_cast<unsigned char>(ch)))
      {
        return false;
      }
    }
    return true;
  }

  std::string nextWord(const std::string& str, size_t& pos)
  {
    while (pos < str.length() && (str[pos] == ' ' || str[pos] == '\t'))
    {
      ++pos;
    }
    
    if (pos >= str.length())
    {
      return "";
    }
    
    size_t start = pos;
    while (pos < str.length() && str[pos] != ' ' && str[pos] != '\t')
    {
      ++pos;
    }
    
    return str.substr(start, pos - start);
  }

  void readingPersons(std::istream& input, PersonList& list, size_t& ignored)
  {
    std::string line;
    while (std::getline(input, line))
    {
      size_t pos = 0;   
      std::string idStr = nextWord(line, pos);
      if (!isNumber(idStr))
      {
        ++ignored;
        continue;
      }
      size_t id = std::stoull(idStr);

      std::string description = nextWord(line, pos);
      if (description.empty())
      {
        ++ignored;
        continue;
      }

      if (!isUniqueId(list, id))
      {
        ++ignored;
        continue;
      }
      Person* pers = new Person;
      pers->id = id;
      pers->info = description;

      pushBack(list, pers);
    }
  }
}

int main()
{

}
