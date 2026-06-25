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

    void doLess(std::istream &in, std::ostream &out, const Database &db)
    {
      std::size_t limit = 0, id = 0;
      if (!(in >> limit >> id))
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
      printMeets(out, db, id, limit, true, false);
    }

    void doGreater(std::istream &in, std::ostream &out, const Database &db)
    {
      std::size_t limit = 0, id = 0;
      if (!(in >> limit >> id))
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
      printMeets(out, db, id, limit, false, true);
    }

    void doAnons(std::ostream &out, const Database &db)
    {
      Vector<std::size_t> ids;
      init(ids);
      for (std::size_t i = 0; i < db.persons.size_; ++i)
      {
        if (db.persons.data_[i].info.empty())
        {
          pushBack(ids, db.persons.data_[i].id);
        }
      }
      std::sort(ids.data_, ids.data_ + ids.size_);
      for (std::size_t i = 0; i < ids.size_; ++i)
      {
        out << ids.data_[i] << '\n';
      }
      destroy(ids);
    }

    void doCommons(std::istream &in, std::ostream &out, const Database &db)
    {
      std::size_t id1 = 0, id2 = 0;
      if (!(in >> id1 >> id2))
      {
        skipLine(in);
        invalidCmd(out);
        return;
      }
      if (findPerson(db, id1) == nullptr || findPerson(db, id2) == nullptr)
      {
        invalidCmd(out);
        return;
      }
      Vector<std::size_t> set1, set2;
      init(set1);
      init(set2);
      for (std::size_t i = 0; i < db.meetings.size_; ++i)
      {
        const Meeting &m = db.meetings.data_[i];
        if (m.a == id1)
        {
          pushBack(set1, m.b);
        }
        else if (m.b == id1)
        {
          pushBack(set1, m.a);
        }
        if (m.a == id2)
        {
          pushBack(set2, m.b);
        }
        else if (m.b == id2)
        {
          pushBack(set2, m.a);
        }
      }
      Vector<std::size_t> result;
      init(result);
      for (std::size_t i = 0; i < set1.size_; ++i)
      {
        std::size_t x = set1.data_[i];
        bool inSet2 = false;
        for (std::size_t j = 0; j < set2.size_; ++j)
        {
          if (set2.data_[j] == x)
          {
            inSet2 = true;
            break;
          }
        }
        if (!inSet2)
        {
          continue;
        }
        bool alreadyIn = false;
        for (std::size_t j = 0; j < result.size_; ++j)
        {
          if (result.data_[j] == x)
          {
            alreadyIn = true;
            break;
          }
        }
        if (!alreadyIn)
        {
          pushBack(result, x);
        }
      }
      std::sort(result.data_, result.data_ + result.size_);
      for (std::size_t i = 0; i < result.size_; ++i)
      {
        out << result.data_[i] << '\n';
      }
      destroy(set1);
      destroy(set2);
      destroy(result);
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
      else if (cmd == "less")
      {
        doLess(in, out, db);
      }
      else if (cmd == "greater")
      {
        doGreater(in, out, db);
      }
      else if (cmd == "anons")
      {
        doAnons(out, db);
      }
      else if (cmd == "commons")
      {
        doCommons(in, out, db);
      }
      else
      {
        skipLine(in);
        invalidCmd(out);
      }
    }
  }
}
