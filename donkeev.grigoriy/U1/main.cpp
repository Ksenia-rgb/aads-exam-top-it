#include <iostream>
#include <exception>
#include <fstream>

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

      while (pos < line.length() && (line[pos] == ' ' || line[pos] == '\t'))
      {
        ++pos;
      }

      if (pos >= line.length())
      {
        ++ignored;
        continue;
      }

      size_t end = line.length();
      while (end > pos && (line[end - 1] == ' ' || line[end - 1] == '\t'))
      {
        --end;
      }

      if (end <= pos)
      {
        ++ignored;
        continue;
      }

      std::string description = line.substr(pos, end - pos);
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

  void printResult(std::ostream& out, donkeev::PersonList& list)
  {
      donkeev::PersonNode* current = list.head_;
      while (current)
      {
        out << current->data->id << " " << current->data->info << "\n";
        current = current->next_;
      }
  }

  void clearList(PersonList& list)
  {
    PersonNode* current = list.head_;
    while (current)
    {
      PersonNode* next = current->next_;
      delete current->data;
      delete current;
      current = next;
    }
    list.head_ = nullptr;
    list.tail_ = nullptr;
    list.size_ = 0;
  }
}

int main(int argc, char* argv[])
{
  std::istream* in = &std::cin;
  std::ostream* out = &std::cout;

  std::ifstream inFile;
  std::ofstream outFile;

  if (argc > 3)
  {
    std::cerr << "Bad parametrs\n";
    return 1;
  }

  int inCount = 0;
  int outCount = 0;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg.rfind("in:", 0) == 0)
    {
      ++inCount;
      if (inCount > 1)
      {
        std::cerr << "Invalid arguments: multiple input files specified\n";
        return 1;
      }

      std::string filename = arg.substr(3);
      if (filename.empty())
      {
        std::cerr << "Invalid arguments: empty filename for input\n";
        return 1;
      }

      inFile.open(filename);
      if (!inFile.is_open())
      {
        std::cerr << "Failed to open input file: " << filename << "\n";
        return 2;
      }
      in = &inFile;
    }
    else if (arg.rfind("out:", 0) == 0)
    {
      ++outCount;
      if (outCount > 1)
      {
        std::cerr << "Invalid arguments: multiple output files specified\n";
        return 1;
      }

      std::string filename = arg.substr(4);
      if (filename.empty())
      {
        std::cerr << "Invalid arguments: empty filename for output\n";
        return 1;
      }

      outFile.open(filename);
      if (!outFile.is_open())
      {
        std::cerr << "Failed to open output file: " << filename << "\n";
        return 2;
      }
      out = &outFile;
    }
    else
    {
      std::cerr << "Invalid arguments: unknown argument '" << arg << "'\n";
      return 1;
    }
  }

  donkeev::PersonList list;
  list.head_ = nullptr;
  list.tail_ = nullptr;
  list.size_ = 0;

  size_t ignoredCount = 0;

  donkeev::readingPersons(*in, list, ignoredCount);

  donkeev::printResult(*out, list);
  std::cerr << list.size_ << " " << ignoredCount << "\n";

  donkeev::clearList(list);
  return 0;
}
