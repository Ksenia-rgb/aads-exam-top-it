#include "meeting_processor.hpp"
#include <cstddef>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <limits>

namespace karpenko
{

  static bool parsePersonLine(const std::string &line, size_t &outId, std::string &outInfo)
  {
    size_t pos = 0;
    while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
    {
      ++pos;
    }
    if (pos == line.size())
    {
      return false;
    }

    size_t start = pos;
    while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos])))
    {
      ++pos;
    }
    std::string idStr = line.substr(start, pos - start);

    size_t id;
    try
    {
      id = static_cast<size_t>(std::stoul(idStr));
    }
    catch (const std::exception &)
    {
      return false;
    }

    while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
    {
      ++pos;
    }
    if (pos == line.size())
    {
      return false;
    }

    std::string info = line.substr(pos);
    while (!info.empty() && std::isspace(static_cast< unsigned char >(info.back())))
    {
      info.pop_back();
    }
    if (info.empty())
    {
      return false;
    }

    outId = id;
    outInfo = info;
    return true;
  }

  bool loadPersons(PersonTable &table, const std::string &filename)
  {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
      return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
      size_t id;
      std::string info;
      if (parsePersonLine(line, id, info))
      {
        PersonData data;
        data.description = info;
        data.hasDescription = true;
        data.meetings = NULL;
        table.insert(id, data);
      }
    }
    file.close();
    return true;
  }

  bool loadMeetings(PersonTable &table, const std::string &filename)
  {
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
      return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
      size_t pos = 0;
      while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      if (pos == line.size())
      {
        return false;
      }
      size_t start = pos;
      while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      std::string num1 = line.substr(start, pos - start);
      size_t id1;
      try
      {
        id1 = static_cast<size_t>(std::stoul(num1));
      }
      catch (...)
      {
        return false;
      }

      while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      if (pos == line.size())
      {
        return false;
      }
      start = pos;
      while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      std::string num2 = line.substr(start, pos - start);
      size_t id2;
      try
      {
        id2 = static_cast<size_t>(std::stoul(num2));
      }
      catch (...)
      {
        return false;
      }

      while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      if (pos == line.size())
      {
        return false;
      }
      start = pos;
      while (pos < line.size() && !std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      std::string num3 = line.substr(start, pos - start);
      size_t time;
      try
      {
        time = static_cast<size_t>(std::stoul(num3));
      }
      catch (...)
      {
        return false;
      }

      while (pos < line.size() && std::isspace(static_cast< unsigned char >(line[pos])))
      {
        ++pos;
      }
      if (pos != line.size())
      {
        return false;
      }

      if (id1 == id2)
      {
        continue;
      }

      PersonData *data1 = table.find(id1);
      if (data1 == NULL)
      {
        PersonData empty;
        empty.description = "";
        empty.hasDescription = false;
        empty.meetings = NULL;
        table.insert(id1, empty);
        data1 = table.find(id1);
      }
      MeetingInfo m1;
      m1.otherId = id2;
      m1.time = time;
      listPushFront(data1->meetings, m1);

      PersonData *data2 = table.find(id2);
      if (data2 == NULL)
      {
        PersonData empty;
        empty.description = "";
        empty.hasDescription = false;
        empty.meetings = NULL;
        table.insert(id2, empty);
        data2 = table.find(id2);
      }
      MeetingInfo m2;
      m2.otherId = id1;
      m2.time = time;
      listPushFront(data2->meetings, m2);
    }
    file.close();
    return true;
  }

}
