#include "Commands.hpp"

#include <ostream>
#include <fstream>
#include <string>
#include <utility>
#include "../common/Array.hpp"
#include "../common/Sort.hpp"

namespace yalovsky
{
  namespace detail
  {
    using Pair = std::pair< size_t, size_t >;

    bool lessSize(const size_t& left, const size_t& right)
    {
      return left < right;
    }

    bool lessPair(const Pair& left, const Pair& right)
    {
      if (left.first != right.first)
      {
        return left.first < right.first;
      }
      return left.second < right.second;
    }

    bool touches(const Meeting& meeting, size_t id, size_t& partner)
    {
      if (meeting.a == id)
      {
        partner = meeting.b;
        return true;
      }
      if (meeting.b == id)
      {
        partner = meeting.a;
        return true;
      }
      return false;
    }

    void collectMeetings(const Database& db, size_t id, Array< Pair >& out)
    {
      for (size_t i = 0; i < db.meetings.size; ++i)
      {
        size_t partner = 0;
        if (touches(db.meetings.data[i], id, partner))
        {
          const Pair entry{partner, db.meetings.data[i].duration};
          pushBack(out, entry);
        }
      }
    }

    void collectPartners(const Database& db, size_t id, Array< size_t >& out)
    {
      for (size_t i = 0; i < db.meetings.size; ++i)
      {
        size_t partner = 0;
        if (touches(db.meetings.data[i], id, partner))
        {
          pushBack(out, partner);
        }
      }
      sortArray(out, lessSize);
    }

    void printMeetings(std::ostream& out, const Array< Pair >& meetings)
    {
      if (meetings.size == 0)
      {
        out << '\n';
        return;
      }
      for (size_t i = 0; i < meetings.size; ++i)
      {
        out << meetings.data[i].first << ' ' << meetings.data[i].second << '\n';
      }
    }
  }

  void cmdAnons(std::ostream& out, const Database& db)
  {
    Array< size_t > ids = makeArray< size_t >();
    try
    {
      for (size_t i = 0; i < db.persons.size; ++i)
      {
        if (db.persons.data[i].info.empty())
        {
          pushBack(ids, db.persons.data[i].id);
        }
      }
      sortArray(ids, detail::lessSize);
      if (ids.size == 0)
      {
        out << '\n';
      }
      for (size_t i = 0; i < ids.size; ++i)
      {
        out << ids.data[i] << '\n';
      }
    }
    catch (...)
    {
      freeArray(ids);
      throw;
    }
    freeArray(ids);
  }

  bool cmdDesc(std::ostream& out, const Database& db, size_t id)
  {
    size_t index = 0;
    if (!findPerson(db, id, index))
    {
      return false;
    }
    if (db.persons.data[index].info.empty())
    {
      out << "<ANON>" << '\n';
    }
    else
    {
      out << db.persons.data[index].info << '\n';
    }
    return true;
  }

  bool cmdRedesc(Database& db, size_t id, const std::string& info)
  {
    size_t index = 0;
    if (!findPerson(db, id, index))
    {
      return false;
    }
    db.persons.data[index].info = info;
    return true;
  }

  bool cmdMeets(std::ostream& out, const Database& db, size_t id)
  {
    size_t index = 0;
    if (!findPerson(db, id, index))
    {
      return false;
    }
    Array< detail::Pair > meetings = makeArray< detail::Pair >();
    try
    {
      detail::collectMeetings(db, id, meetings);
      sortArray(meetings, detail::lessPair);
      detail::printMeetings(out, meetings);
    }
    catch (...)
    {
      freeArray(meetings);
      throw;
    }
    freeArray(meetings);
    return true;
  }

  bool cmdCommons(std::ostream& out, const Database& db, size_t first, size_t second)
  {
    size_t index = 0;
    if (!findPerson(db, first, index) || !findPerson(db, second, index))
    {
      return false;
    }
    Array< size_t > left = makeArray< size_t >();
    Array< size_t > right = makeArray< size_t >();
    try
    {
      detail::collectPartners(db, first, left);
      detail::collectPartners(db, second, right);
      size_t i = 0;
      size_t j = 0;
      size_t lastPrinted = 0;
      bool hasPrinted = false;
      while (i < left.size && j < right.size)
      {
        if (left.data[i] < right.data[j])
        {
          ++i;
        }
        else if (right.data[j] < left.data[i])
        {
          ++j;
        }
        else
        {
          const size_t value = left.data[i];
          if (!hasPrinted || value != lastPrinted)
          {
            out << value << '\n';
            lastPrinted = value;
            hasPrinted = true;
          }
          ++i;
          ++j;
        }
      }
      if (!hasPrinted)
      {
        out << '\n';
      }
    }
    catch (...)
    {
      freeArray(left);
      freeArray(right);
      throw;
    }
    freeArray(left);
    freeArray(right);
    return true;
  }

  bool cmdBounded(std::ostream& out, const Database& db, size_t id, size_t time, bool greater)
  {
    size_t index = 0;
    if (!findPerson(db, id, index))
    {
      return false;
    }
    Array< detail::Pair > meetings = makeArray< detail::Pair >();
    try
    {
      detail::collectMeetings(db, id, meetings);
      sortArray(meetings, detail::lessPair);
      bool printed = false;
      for (size_t i = 0; i < meetings.size; ++i)
      {
        const size_t duration = meetings.data[i].second;
        const bool keep = greater ? (duration > time) : (duration < time);
        if (keep)
        {
          out << meetings.data[i].first << ' ' << duration << '\n';
          printed = true;
        }
      }
      if (!printed)
      {
        out << '\n';
      }
    }
    catch (...)
    {
      freeArray(meetings);
      throw;
    }
    freeArray(meetings);
    return true;
  }

  bool cmdOutPersons(const Database& db, const std::string& filename)
  {
    std::ofstream out(filename, std::ios::app);
    if (!out.is_open())
    {
      return false;
    }
    bool printed = false;
    for (size_t i = 0; i < db.persons.size; ++i)
    {
      if (!db.persons.data[i].info.empty())
      {
        out << db.persons.data[i].id << ' ' << db.persons.data[i].info << '\n';
        printed = true;
      }
    }
    if (!printed)
    {
      out << '\n';
    }
    return true;
  }
}
