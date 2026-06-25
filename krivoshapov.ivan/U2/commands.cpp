#include "commands.hpp"

#include "../common/vector.hpp"

#include <algorithm>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>

namespace krivoshapov
{
  namespace
  {
    void invalidCmd(std::ostream &out)
    {
      out << "<INVALID COMMAND>\n";
    }

    void skipLine(std::istream &in)
    {
      in.clear();
      std::string dummy;
      std::getline(in, dummy);
    }

    struct MeetEntry
    {
      std::size_t otherId;
      std::size_t duration;
    };

    bool meetEntryCmp(const MeetEntry &x, const MeetEntry &y)
    {
      if (x.otherId != y.otherId)
      {
        return x.otherId < y.otherId;
      }
      return x.duration < y.duration;
    }

    void printMeets(std::ostream &out, const Database &db, std::size_t id,
                    std::size_t limit, bool useLess, bool useGreater)
    {
      Vector<MeetEntry> entries;
      init(entries);
      for (std::size_t i = 0; i < db.meetings.size_; ++i)
      {
        const Meeting &m = db.meetings.data_[i];
        std::size_t other = 0;
        bool found = false;
        if (m.a == id)
        {
          other = m.b;
          found = true;
        }
        else if (m.b == id)
        {
          other = m.a;
          found = true;
        }
        if (!found)
        {
          continue;
        }
        if (useLess && m.duration >= limit)
        {
          continue;
        }
        if (useGreater && m.duration <= limit)
        {
          continue;
        }
        MeetEntry e = {other, m.duration};
        pushBack(entries, e);
      }
      std::sort(entries.data_, entries.data_ + entries.size_, meetEntryCmp);
      for (std::size_t i = 0; i < entries.size_; ++i)
      {
        out << entries.data_[i].otherId << ' ' << entries.data_[i].duration << '\n';
      }
      destroy(entries);
    }

    void doDesc(std::istream &in, std::ostream &out, const Database &db)
    {
      std::size_t id = 0;
      if (!(in >> id))
      {
        skipLine(in);
        invalidCmd(out);
        return;
      }
      const Person *p = findPerson(db, id);
      if (p == nullptr)
      {
        invalidCmd(out);
        return;
      }
      if (p->info.empty())
      {
        out << "<ANON>\n";
      }
      else
      {
        out << p->info << '\n';
      }
    }

    void doMeets(std::istream &in, std::ostream &out, const Database &db)
    {
      std::size_t id = 0;
      if (!(in >> id))
      {
        skipLine(in);
        invalidCmd(out);
        return;
      }
      if (findPerson(db, id) == nullptr)
      {
        invalidCmd(out);
        return;
      }
      printMeets(out, db, id, 0, false, false);
    }
  }

  void processCommands(std::istream &in, std::ostream &out, Database &db)
  {
    std::string cmd;
    while (in >> cmd)
    {
      if (cmd == "desc")
      {
        doDesc(in, out, db);
      }
      else if (cmd == "meets")
      {
        doMeets(in, out, db);
      }
      else
      {
        skipLine(in);
        invalidCmd(out);
      }
    }
  }
}
