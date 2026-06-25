#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <person.hpp>
#include <list.hpp>
#include <hash.hpp>
#include <string_utils.hpp>

namespace vishnyakov
{

struct Date
{
  int day;
  int month;
  int year;
};

struct Meeting
{
  size_t id1;
  size_t id2;
  size_t duration;
  Date date;
};

struct Range
{
  Date start;
  Date end;
  bool empty;
};

bool isDateEmpty(const Date& date)
{
  return date.day == 0 && date.month == 0 && date.year == 0;
}

bool dateLess(const Date& a, const Date& b)
{
  if (a.year != b.year) return a.year < b.year;
  if (a.month != b.month) return a.month < b.month;
  return a.day < b.day;
}

bool dateEqual(const Date& a, const Date& b)
{
  return a.day == b.day && a.month == b.month && a.year == b.year;
}

}

int main(int argc, char* argv[])
{
  using namespace vishnyakov;

  List< std::string > dataFiles;
  std::string inputFile;

  for (int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];

    if (arg.rfind("in:", 0) == 0)
    {
      if (!inputFile.empty())
      {
        std::cerr << "Error: duplicate input file argument\n";
        return 1;
      }
      inputFile = arg.substr(3);
    }
    else if (arg.rfind("data:", 0) == 0)
    {
      dataFiles.pushBack(arg.substr(5));
    }
    else
    {
      std::cerr << "Error: invalid argument\n";
      return 1;
    }
  }

  if (dataFiles.empty())
  {
    std::cerr << "Error: at least one data file is required\n";
    return 1;
  }

  std::istream* in = &std::cin;
  std::ifstream inputStream;

  if (!inputFile.empty())
  {
    inputStream.open(inputFile);
    if (!inputStream.is_open())
    {
      std::cerr << "Error: cannot open input file\n";
      return 2;
    }
    in = &inputStream;
  }

  HashTable< size_t, Person > persons;
  HashSet< size_t > usedIds;
  std::string line;

  if (!inputFile.empty())
  {
    while (std::getline(*in, line))
    {
      std::string trimmed = trim(line);

      if (trimmed.empty())
      {
        continue;
      }

      size_t pos = 0;
      size_t id = 0;

      while (pos < trimmed.length() && std::isdigit(trimmed[pos]))
      {
        id = id * 10 + (trimmed[pos] - '0');
        ++pos;
      }

      if (pos == 0)
      {
        continue;
      }

      while (pos < trimmed.length() && std::isspace(trimmed[pos]))
      {
        ++pos;
      }

      if (pos >= trimmed.length())
      {
        continue;
      }

      std::string info = trimmed.substr(pos);

      if (info.empty())
      {
        continue;
      }

      if (usedIds.has(id))
      {
        continue;
      }

      Person p;
      p.id = id;
      p.info = info;
      persons.add(id, p);
      usedIds.insert(id);
    }
  }

  List< Meeting > meetings;
  Range currentRange;
  currentRange.empty = true;

  for (ListNode< std::string >* fileNode = dataFiles.begin(); fileNode != dataFiles.end(); fileNode = fileNode->next)
  {
    std::ifstream dataStream(fileNode->data);

    if (!dataStream.is_open())
    {
      std::cerr << "Error: cannot open data file\n";
      return 2;
    }

    while (std::getline(dataStream, line))
    {
      std::string trimmed = trim(line);

      if (trimmed.empty())
      {
        continue;
      }

      std::istringstream iss(trimmed);
      int day, month, year;
      iss >> day >> month >> year;

      if (iss.fail())
      {
        std::cerr << "Error: invalid meeting data\n";
        return 3;
      }

      size_t id1, id2;
      size_t duration;
      iss >> id1 >> id2 >> duration;

      if (iss.fail())
      {
        std::cerr << "Error: invalid meeting data\n";
        return 3;
      }

      if (id1 == id2)
      {
        continue;
      }

      Date date;
      date.day = day;
      date.month = month;
      date.year = year;

      if (currentRange.empty)
      {
        currentRange.start = date;
        currentRange.end = date;
        currentRange.empty = false;
      }
      else
      {
        if (dateLess(date, currentRange.start))
        {
          currentRange.start = date;
        }
        if (dateLess(currentRange.end, date))
        {
          currentRange.end = date;
        }
      }

      Meeting m;
      m.id1 = id1;
      m.id2 = id2;
      m.duration = duration;
      m.date = date;
      meetings.pushBack(m);

      if (!persons.has(id1))
      {
        Person p;
        p.id = id1;
        p.info = "";
        persons.add(id1, p);
      }

      if (!persons.has(id2))
      {
        Person p;
        p.id = id2;
        p.info = "";
        persons.add(id2, p);
      }
    }
  }

  List< Range > rangeHistory;

  while (std::getline(std::cin, line))
  {
    std::string trimmed = trim(line);

    if (trimmed.empty())
    {
      continue;
    }

    std::istringstream iss(trimmed);
    std::string command;
    iss >> command;

    if (command == "range")
    {
      if (currentRange.empty)
      {
        std::cout << "<EMPTY>\n";
      }
      else
      {
        std::cout << currentRange.start.day << " " << currentRange.start.month << " " << currentRange.start.year
                  << " : "
                  << currentRange.end.day << " " << currentRange.end.month << " " << currentRange.end.year << "\n";
      }
    }
    else if (command == "after")
    {
      int day, month, year;
      iss >> day >> month >> year;

      if (iss.fail() || currentRange.empty)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      Date date;
      date.day = day;
      date.month = month;
      date.year = year;

      if (dateLess(date, currentRange.end))
      {
        Range prev = currentRange;
        rangeHistory.pushBack(prev);

        Date newStart;
        newStart.day = day;
        newStart.month = month;
        newStart.year = year;

        bool found = false;
        for (ListNode< Meeting >* node = meetings.begin(); node != meetings.end(); node = node->next)
        {
          if (!dateLess(node->data.date, newStart) && !dateLess(node->data.date, currentRange.start))
          {
            if (!found || dateLess(node->data.date, newStart))
            {
              newStart = node->data.date;
              found = true;
            }
          }
        }

        if (found)
        {
          currentRange.start = newStart;
        }
        else
        {
          currentRange.empty = true;
        }
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "before")
    {
      int day, month, year;
      iss >> day >> month >> year;

      if (iss.fail() || currentRange.empty)
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      Date date;
      date.day = day;
      date.month = month;
      date.year = year;

      if (dateLess(currentRange.start, date))
      {
        Range prev = currentRange;
        rangeHistory.pushBack(prev);

        Date newEnd;
        newEnd.day = day;
        newEnd.month = month;
        newEnd.year = year;

        bool found = false;
        for (ListNode< Meeting >* node = meetings.begin(); node != meetings.end(); node = node->next)
        {
          if (dateLess(node->data.date, newEnd) && !dateLess(currentRange.end, node->data.date))
          {
            if (!found || dateLess(newEnd, node->data.date))
            {
              newEnd = node->data.date;
              found = true;
            }
          }
        }

        if (found)
        {
          currentRange.end = newEnd;
        }
        else
        {
          currentRange.empty = true;
        }
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
    else if (command == "pop-range")
    {
      if (rangeHistory.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
        continue;
      }

      currentRange = rangeHistory.back();
      rangeHistory.popBack();
    }
    else
    {
      // Команды из U2
      if (command == "anons")
      {
        List< size_t > anonIds;

        for (ListNode< Person >* node = persons.begin(); node != persons.end(); node = node->next)
        {
          if (node->data.info.empty())
          {
            anonIds.pushBack(node->data.id);
          }
        }

        if (anonIds.empty())
        {
          continue;
        }

        for (ListNode< size_t >* i = anonIds.begin(); i != anonIds.end(); ++i)
        {
          for (ListNode< size_t >* j = i; j != anonIds.end(); ++j)
          {
            if (j->data < i->data)
            {
              size_t tmp = i->data;
              i->data = j->data;
              j->data = tmp;
            }
          }
        }

        for (ListNode< size_t >* node = anonIds.begin(); node != anonIds.end(); node = node->next)
        {
          std::cout << node->data << "\n";
        }
      }
      else if (command == "desc")
      {
        size_t id;
        iss >> id;

        if (iss.fail())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        const Person* p = persons.find(id);

        if (!p)
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        if (p->info.empty())
        {
          std::cout << "<ANON>\n";
        }
        else
        {
          std::cout << p->info << "\n";
        }
      }
      else if (command == "meets")
      {
        size_t id;
        iss >> id;

        if (iss.fail())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        if (!persons.has(id))
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        List< Meeting > filtered;

        for (ListNode< Meeting >* node = meetings.begin(); node != meetings.end(); node = node->next)
        {
          if ((node->data.id1 == id || node->data.id2 == id) &&
              !currentRange.empty &&
              !dateLess(node->data.date, currentRange.start) &&
              !dateLess(currentRange.end, node->data.date))
          {
            filtered.pushBack(node->data);
          }
        }

        if (filtered.empty())
        {
          continue;
        }

        for (ListNode< Meeting >* i = filtered.begin(); i != filtered.end(); ++i)
        {
          for (ListNode< Meeting >* j = i; j != filtered.end(); ++j)
          {
            size_t otherI = (i->data.id1 == id) ? i->data.id2 : i->data.id1;
            size_t otherJ = (j->data.id1 == id) ? j->data.id2 : j->data.id1;

            bool swap = false;

            if (otherI > otherJ)
            {
              swap = true;
            }
            else if (otherI == otherJ && i->data.duration > j->data.duration)
            {
              swap = true;
            }

            if (swap)
            {
              Meeting tmp = i->data;
              i->data = j->data;
              j->data = tmp;
            }
          }
        }

        for (ListNode< Meeting >* node = filtered.begin(); node != filtered.end(); node = node->next)
        {
          size_t otherId = (node->data.id1 == id) ? node->data.id2 : node->data.id1;
          std::cout << otherId << " " << node->data.duration << "\n";
        }
      }
      else if (command == "redesc")
      {
        size_t id;
        std::string newInfo;
        iss >> id;

        if (iss.fail())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        iss >> std::ws;
        std::getline(iss, newInfo);

        if (newInfo.empty())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        if (!persons.has(id))
        {
          Person p;
          p.id = id;
          p.info = newInfo;
          persons.add(id, p);
        }
        else
        {
          Person* p = persons.find(id);
          p->info = newInfo;
        }
      }
      else if (command == "deanon")
      {
        size_t anonId;
        size_t targetId;
        iss >> anonId >> targetId;

        if (iss.fail())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        Person* anon = persons.find(anonId);
        Person* target = persons.find(targetId);

        if (!anon || !target || !anon->info.empty() || target->info.empty())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        for (ListNode< Meeting >* node = meetings.begin(); node != meetings.end(); node = node->next)
        {
          if (node->data.id1 == anonId)
          {
            if (node->data.id2 == targetId)
            {
              continue;
            }
            node->data.id1 = targetId;
          }
          else if (node->data.id2 == anonId)
          {
            if (node->data.id1 == targetId)
            {
              continue;
            }
            node->data.id2 = targetId;
          }
        }

        persons.remove(anonId);
      }
      else if (command == "commons")
      {
        size_t id1;
        size_t id2;
        iss >> id1 >> id2;

        if (iss.fail())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        if (!persons.has(id1) || !persons.has(id2))
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        HashSet< size_t > commonSet;

        for (ListNode< Meeting >* node = meetings.begin(); node != meetings.end(); node = node->next)
        {
          if (!currentRange.empty &&
              (dateLess(node->data.date, currentRange.start) || dateLess(currentRange.end, node->data.date)))
          {
            continue;
          }

          if (node->data.id1 == id1)
          {
            commonSet.insert(node->data.id2);
          }
          else if (node->data.id2 == id1)
          {
            commonSet.insert(node->data.id1);
          }
        }

        List< size_t > result;

        for (ListNode< Meeting >* node = meetings.begin(); node != meetings.end(); node = node->next)
        {
          if (!currentRange.empty &&
              (dateLess(node->data.date, currentRange.start) || dateLess(currentRange.end, node->data.date)))
          {
            continue;
          }

          size_t otherId = 0;

          if (node->data.id1 == id2)
          {
            otherId = node->data.id2;
          }
          else if (node->data.id2 == id2)
          {
            otherId = node->data.id1;
          }

          if (otherId != 0 && commonSet.has(otherId))
          {
            bool exists = false;

            for (ListNode< size_t >* rn = result.begin(); rn != result.end(); rn = rn->next)
            {
              if (rn->data == otherId)
              {
                exists = true;
                break;
              }
            }

            if (!exists)
            {
              result.pushBack(otherId);
            }
          }
        }

        for (ListNode< size_t >* i = result.begin(); i != result.end(); ++i)
        {
          for (ListNode< size_t >* j = i; j != result.end(); ++j)
          {
            if (j->data < i->data)
            {
              size_t tmp = i->data;
              i->data = j->data;
              j->data = tmp;
            }
          }
        }

        for (ListNode< size_t >* node = result.begin(); node != result.end(); node = node->next)
        {
          std::cout << node->data << "\n";
        }
      }
      else if (command == "less" || command == "greater")
      {
        size_t id;
        size_t duration;
        iss >> id >> duration;

        if (iss.fail())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        if (!persons.has(id))
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        bool isLess = (command == "less");
        List< Meeting > filtered;

        for (ListNode< Meeting >* node = meetings.begin(); node != meetings.end(); node = node->next)
        {
          if ((node->data.id1 == id || node->data.id2 == id) &&
              !currentRange.empty &&
              !dateLess(node->data.date, currentRange.start) &&
              !dateLess(currentRange.end, node->data.date))
          {
            bool condition = isLess ? (node->data.duration < duration) : (node->data.duration > duration);

            if (condition)
            {
              filtered.pushBack(node->data);
            }
          }
        }

        if (filtered.empty())
        {
          continue;
        }

        for (ListNode< Meeting >* i = filtered.begin(); i != filtered.end(); ++i)
        {
          for (ListNode< Meeting >* j = i; j != filtered.end(); ++j)
          {
            size_t otherI = (i->data.id1 == id) ? i->data.id2 : i->data.id1;
            size_t otherJ = (j->data.id1 == id) ? j->data.id2 : j->data.id1;

            bool swap = false;

            if (otherI > otherJ)
            {
              swap = true;
            }
            else if (otherI == otherJ && i->data.duration > j->data.duration)
            {
              swap = true;
            }

            if (swap)
            {
              Meeting tmp = i->data;
              i->data = j->data;
              j->data = tmp;
            }
          }
        }

        for (ListNode< Meeting >* node = filtered.begin(); node != filtered.end(); node = node->next)
        {
          size_t otherId = (node->data.id1 == id) ? node->data.id2 : node->data.id1;
          std::cout << otherId << " " << node->data.duration << "\n";
        }
      }
      else if (command == "out-persons")
      {
        std::string outFile;
        iss >> outFile;

        if (outFile.empty())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        std::ofstream outStream(outFile);

        if (!outStream.is_open())
        {
          std::cout << "<INVALID COMMAND>\n";
          continue;
        }

        for (ListNode< Person >* node = persons.begin(); node != persons.end(); node = node->next)
        {
          if (!node->data.info.empty())
          {
            outStream << node->data.id << " " << node->data.info << "\n";
          }
        }
      }
      else
      {
        std::cout << "<INVALID COMMAND>\n";
      }
    }
  }

  return 0;
}

