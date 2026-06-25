#include "helpedFunc.hpp"

void donkeev::pushBack(PersonList& list, Person* person)
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

bool donkeev::isUniqueId(const PersonList& list, size_t id)
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

bool donkeev::isNumber(const std::string& str)
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

std::string donkeev::nextWord(const std::string& str, size_t& pos)
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

void donkeev::readingPersons(std::istream& input, PersonList& list, size_t& ignored)
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

void donkeev::pushMeeting(MeetingList& list, size_t id1, size_t id2, size_t duration)
{
  if (id1 > id2)
  {
    std::swap(id1, id2);
  }
        
  MeetingNode* newNode = new MeetingNode;
  newNode->ids = std::make_pair(id1, id2);
  newNode->duration = duration;
  newNode->next_ = nullptr;
  newNode->prev_ = nullptr;
  
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

void donkeev::clearMeetingList(MeetingList& list)
{
  MeetingNode* current = list.head_;
  while (current)
  {
    MeetingNode* next = current->next_;
    delete current;
    current = next;
  }
  list.head_ = nullptr;
  list.tail_ = nullptr;
  list.size_ = 0;
}