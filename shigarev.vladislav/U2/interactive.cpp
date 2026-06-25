#include "interactive.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <cstddef>
#include <cctype>
#include "personio.hpp"

namespace {
  void printInvalidCommand()
  {
    std::cout << "<INVALID COMMAND>\n";
  }

  shigarev::Person* findPerson(shigarev::DynArray< shigarev::Person >& persons,
      size_t id)
  {
    for (size_t i = 0; i < persons.size_; ++i) {
      if (persons.data_[i].id == id) {
        return &persons.data_[i];
      }
    }
    return nullptr;
  }

  const shigarev::Person* findPersonConst(
      const shigarev::DynArray< shigarev::Person >& persons,
      size_t id)
  {
    for (size_t i = 0; i < persons.size_; ++i) {
      if (persons.data_[i].id == id) {
        return &persons.data_[i];
      }
    }
    return nullptr;
  }

  void addPersonSorted(shigarev::DynArray< shigarev::Person >& persons,
      size_t id, const std::string& info)
  {
    if (findPerson(persons, id) != nullptr) {
      return;
    }
    size_t pos = persons.size_;
    for (size_t i = 0; i < persons.size_; ++i) {
      if (persons.data_[i].id > id) {
        pos = i;
        break;
      }
    }
    shigarev::pushBack(persons, shigarev::Person{0, ""});
    for (size_t i = persons.size_ - 1; i > pos; --i) {
      persons.data_[i] = persons.data_[i - 1];
    }
    persons.data_[pos].id = id;
    persons.data_[pos].info = info;
  }

  void commandAnons(const shigarev::DynArray< shigarev::Person >& persons)
  {
    for (size_t i = 0; i < persons.size_; ++i) {
      if (persons.data_[i].info.empty()) {
        std::cout << persons.data_[i].id << "\n";
      }
    }
  }

  void commandDesc(const shigarev::DynArray< shigarev::Person >& persons,
      size_t id)
  {
    const shigarev::Person* p = findPersonConst(persons, id);
    if (p == nullptr || p->info.empty()) {
      std::cout << "<ANON>\n";
    } else {
      std::cout << p->info << "\n";
    }
  }

  void commandRedesc(shigarev::DynArray< shigarev::Person >& persons,
      size_t id, const std::string& desc)
  {
    shigarev::Person* p = findPerson(persons, id);
    if (p == nullptr) {
      addPersonSorted(persons, id, desc);
    } else {
      p->info = desc;
    }
  }

  void commandMeets(const shigarev::DynArray< shigarev::Person >& persons,
      const shigarev::DynArray< shigarev::Meeting >& meetings,
      size_t id)
  {
    shigarev::DynArray< shigarev::Meeting > filtered =
        shigarev::createDynArray< shigarev::Meeting >(16);
    for (size_t i = 0; i < meetings.size_; ++i) {
      const shigarev::Meeting& m = meetings.data_[i];
      if (m.id1 == id || m.id2 == id) {
        shigarev::pushBack(filtered, m);
      }
    }
    for (size_t i = 0; i < filtered.size_; ++i) {
      for (size_t j = i + 1; j < filtered.size_; ++j) {
        size_t other1 = (filtered.data_[i].id1 == id) ?
            filtered.data_[i].id2 : filtered.data_[i].id1;
        size_t other2 = (filtered.data_[j].id1 == id) ?
            filtered.data_[j].id2 : filtered.data_[j].id1;
        bool swap = false;
        if (other1 > other2) {
          swap = true;
        } else if (other1 == other2) {
          if (filtered.data_[i].duration > filtered.data_[j].duration) {
            swap = true;
          }
        }
        if (swap) {
          shigarev::Meeting tmp = filtered.data_[i];
          filtered.data_[i] = filtered.data_[j];
          filtered.data_[j] = tmp;
        }
      }
    }
    for (size_t i = 0; i < filtered.size_; ++i) {
      const shigarev::Meeting& m = filtered.data_[i];
      size_t other = (m.id1 == id) ? m.id2 : m.id1;
      std::cout << other << " " << m.duration << "\n";
    }
    shigarev::destroyDynArray(filtered);
  }

  void commandCommons(const shigarev::DynArray< shigarev::Person >& persons,
      const shigarev::DynArray< shigarev::Meeting >& meetings,
      size_t id1, size_t id2)
  {
    shigarev::DynArray< size_t > set1 = shigarev::createDynArray< size_t >(16);
    shigarev::DynArray< size_t > set2 = shigarev::createDynArray< size_t >(16);
    for (size_t i = 0; i < meetings.size_; ++i) {
      const shigarev::Meeting& m = meetings.data_[i];
      if (m.id1 == id1 && m.id2 != id1) {
        shigarev::pushBack(set1, m.id2);
      } else if (m.id2 == id1 && m.id1 != id1) {
        shigarev::pushBack(set1, m.id1);
      }
      if (m.id1 == id2 && m.id2 != id2) {
        shigarev::pushBack(set2, m.id2);
      } else if (m.id2 == id2 && m.id1 != id2) {
        shigarev::pushBack(set2, m.id1);
      }
    }
    shigarev::DynArray< size_t > common = shigarev::createDynArray< size_t >(16);
    for (size_t i = 0; i < set1.size_; ++i) {
      size_t val = set1.data_[i];
      bool found = false;
      for (size_t j = 0; j < set2.size_; ++j) {
        if (set2.data_[j] == val) {
          found = true;
          break;
        }
      }
      if (found) {
        bool dup = false;
        for (size_t k = 0; k < common.size_; ++k) {
          if (common.data_[k] == val) {
            dup = true;
            break;
          }
        }
        if (!dup) {
          shigarev::pushBack(common, val);
        }
      }
    }
    for (size_t i = 0; i < common.size_; ++i) {
      for (size_t j = i + 1; j < common.size_; ++j) {
        if (common.data_[i] > common.data_[j]) {
          size_t tmp = common.data_[i];
          common.data_[i] = common.data_[j];
          common.data_[j] = tmp;
        }
      }
    }
    for (size_t i = 0; i < common.size_; ++i) {
      std::cout << common.data_[i] << "\n";
    }
    shigarev::destroyDynArray(set1);
    shigarev::destroyDynArray(set2);
    shigarev::destroyDynArray(common);
  }

  void commandLess(const shigarev::DynArray< shigarev::Person >& persons,
      const shigarev::DynArray< shigarev::Meeting >& meetings,
      size_t time, size_t id)
  {
    shigarev::DynArray< shigarev::Meeting > filtered =
        shigarev::createDynArray< shigarev::Meeting >(16);
    for (size_t i = 0; i < meetings.size_; ++i) {
      const shigarev::Meeting& m = meetings.data_[i];
      if ((m.id1 == id || m.id2 == id) && m.duration < time) {
        shigarev::pushBack(filtered, m);
      }
    }
    for (size_t i = 0; i < filtered.size_; ++i) {
      for (size_t j = i + 1; j < filtered.size_; ++j) {
        size_t other1 = (filtered.data_[i].id1 == id) ?
            filtered.data_[i].id2 : filtered.data_[i].id1;
        size_t other2 = (filtered.data_[j].id1 == id) ?
            filtered.data_[j].id2 : filtered.data_[j].id1;
        bool swap = false;
        if (other1 > other2) {
          swap = true;
        } else if (other1 == other2) {
          if (filtered.data_[i].duration > filtered.data_[j].duration) {
            swap = true;
          }
        }
        if (swap) {
          shigarev::Meeting tmp = filtered.data_[i];
          filtered.data_[i] = filtered.data_[j];
          filtered.data_[j] = tmp;
        }
      }
    }
    for (size_t i = 0; i < filtered.size_; ++i) {
      const shigarev::Meeting& m = filtered.data_[i];
      size_t other = (m.id1 == id) ? m.id2 : m.id1;
      std::cout << other << " " << m.duration << "\n";
    }
    shigarev::destroyDynArray(filtered);
  }

  void commandGreater(const shigarev::DynArray< shigarev::Person >& persons,
      const shigarev::DynArray< shigarev::Meeting >& meetings,
      size_t time, size_t id)
  {
    shigarev::DynArray< shigarev::Meeting > filtered =
        shigarev::createDynArray< shigarev::Meeting >(16);
    for (size_t i = 0; i < meetings.size_; ++i) {
      const shigarev::Meeting& m = meetings.data_[i];
      if ((m.id1 == id || m.id2 == id) && m.duration > time) {
        shigarev::pushBack(filtered, m);
      }
    }
    for (size_t i = 0; i < filtered.size_; ++i) {
      for (size_t j = i + 1; j < filtered.size_; ++j) {
        size_t other1 = (filtered.data_[i].id1 == id) ?
            filtered.data_[i].id2 : filtered.data_[i].id1;
        size_t other2 = (filtered.data_[j].id1 == id) ?
            filtered.data_[j].id2 : filtered.data_[j].id1;
        bool swap = false;
        if (other1 > other2) {
          swap = true;
        } else if (other1 == other2) {
          if (filtered.data_[i].duration > filtered.data_[j].duration) {
            swap = true;
          }
        }
        if (swap) {
          shigarev::Meeting tmp = filtered.data_[i];
          filtered.data_[i] = filtered.data_[j];
          filtered.data_[j] = tmp;
        }
      }
    }
    for (size_t i = 0; i < filtered.size_; ++i) {
      const shigarev::Meeting& m = filtered.data_[i];
      size_t other = (m.id1 == id) ? m.id2 : m.id1;
      std::cout << other << " " << m.duration << "\n";
    }
    shigarev::destroyDynArray(filtered);
  }

  void commandDeanonymize(shigarev::DynArray< shigarev::Person >& persons,
      shigarev::DynArray< shigarev::Meeting >& meetings,
      size_t anonId, size_t realId)
  {
    shigarev::Person* anon = findPerson(persons, anonId);
    shigarev::Person* real = findPerson(persons, realId);
    if (anon == nullptr || real == nullptr) {
      printInvalidCommand();
      return;
    }
    if (!anon->info.empty() || real->info.empty()) {
      printInvalidCommand();
      return;
    }
    for (size_t i = 0; i < meetings.size_; ++i) {
      shigarev::Meeting& m = meetings.data_[i];
      if (m.id1 == anonId) {
        m.id1 = realId;
      }
      if (m.id2 == anonId) {
        m.id2 = realId;
      }
    }
    size_t write = 0;
    for (size_t i = 0; i < meetings.size_; ++i) {
      if (meetings.data_[i].id1 != meetings.data_[i].id2) {
        meetings.data_[write] = meetings.data_[i];
        ++write;
      }
    }
    meetings.size_ = write;

    size_t pos = persons.size_;
    for (size_t i = 0; i < persons.size_; ++i) {
      if (persons.data_[i].id == anonId) {
        pos = i;
        break;
      }
    }
    if (pos < persons.size_) {
      for (size_t i = pos; i < persons.size_ - 1; ++i) {
        persons.data_[i] = persons.data_[i + 1];
      }
      --persons.size_;
    }
  }

  bool parseCommand(const std::string& line,
      shigarev::DynArray< shigarev::Person >& persons,
      shigarev::DynArray< shigarev::Meeting >& meetings)
  {
    size_t pos = 0;
    while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
      ++pos;
    }
    if (pos >= line.size()) {
      return true;
    }
    size_t start = pos;
    while (pos < line.size() && !std::isspace(static_cast<unsigned char>(line[pos]))) {
      ++pos;
    }
    std::string cmd = line.substr(start, pos - start);
    while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
      ++pos;
    }

    if (cmd == "anons") {
      if (pos != line.size()) {
        printInvalidCommand();
        return true;
      }
      commandAnons(persons);
      return true;
    }

    if (cmd == "desc") {
      size_t id = 0;
      bool ok = false;
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id = id * 10 + (line[pos] - '0');
        ++pos;
        ok = true;
      }
      if (!ok || pos != line.size()) {
        printInvalidCommand();
        return true;
      }
      commandDesc(persons, id);
      return true;
    }

    if (cmd == "redesc") {
      size_t id = 0;
      bool ok = false;
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id = id * 10 + (line[pos] - '0');
        ++pos;
        ok = true;
      }
      if (!ok) {
        printInvalidCommand();
        return true;
      }
      while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
        ++pos;
      }
      if (pos >= line.size() || line[pos] != '\"') {
        printInvalidCommand();
        return true;
      }
      ++pos;
      size_t descStart = pos;
      while (pos < line.size() && line[pos] != '\"') {
        ++pos;
      }
      if (pos >= line.size()) {
        printInvalidCommand();
        return true;
      }
      std::string desc = line.substr(descStart, pos - descStart);
      ++pos;
      commandRedesc(persons, id, desc);
      return true;
    }

    if (cmd == "deanon") {
      size_t id1 = 0, id2 = 0;
      bool ok1 = false, ok2 = false;
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id1 = id1 * 10 + (line[pos] - '0');
        ++pos;
        ok1 = true;
      }
      if (!ok1) {
        printInvalidCommand();
        return true;
      }
      while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
        ++pos;
      }
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id2 = id2 * 10 + (line[pos] - '0');
        ++pos;
        ok2 = true;
      }
      if (!ok2 || pos != line.size()) {
        printInvalidCommand();
        return true;
      }
      commandDeanonymize(persons, meetings, id1, id2);
      return true;
    }

    if (cmd == "meets") {
      size_t id = 0;
      bool ok = false;
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id = id * 10 + (line[pos] - '0');
        ++pos;
        ok = true;
      }
      if (!ok || pos != line.size()) {
        printInvalidCommand();
        return true;
      }
      commandMeets(persons, meetings, id);
      return true;
    }

    if (cmd == "commons") {
      size_t id1 = 0, id2 = 0;
      bool ok1 = false, ok2 = false;
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id1 = id1 * 10 + (line[pos] - '0');
        ++pos;
        ok1 = true;
      }
      if (!ok1) {
        printInvalidCommand();
        return true;
      }
      while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
        ++pos;
      }
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id2 = id2 * 10 + (line[pos] - '0');
        ++pos;
        ok2 = true;
      }
      if (!ok2 || pos != line.size()) {
        printInvalidCommand();
        return true;
      }
      commandCommons(persons, meetings, id1, id2);
      return true;
    }

    if (cmd == "less" || cmd == "greater") {
      size_t time = 0, id = 0;
      bool ok1 = false, ok2 = false;
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        time = time * 10 + (line[pos] - '0');
        ++pos;
        ok1 = true;
      }
      if (!ok1) {
        printInvalidCommand();
        return true;
      }
      while (pos < line.size() && std::isspace(static_cast<unsigned char>(line[pos]))) {
        ++pos;
      }
      while (pos < line.size() && std::isdigit(static_cast<unsigned char>(line[pos]))) {
        id = id * 10 + (line[pos] - '0');
        ++pos;
        ok2 = true;
      }
      if (!ok2 || pos != line.size()) {
        printInvalidCommand();
        return true;
      }
      if (cmd == "less") {
        commandLess(persons, meetings, time, id);
      } else {
        commandGreater(persons, meetings, time, id);
      }
      return true;
    }

    if (cmd == "out-persons") {
      size_t start = pos;
      while (pos < line.size() && !std::isspace(static_cast<unsigned char>(line[pos]))) {
        ++pos;
      }
      if (start == pos || pos != line.size()) {
        printInvalidCommand();
        return true;
      }
      std::string filename = line.substr(start, pos - start);
      std::ofstream out(filename.c_str());
      if (!out.is_open()) {
        std::cerr << "Cannot open output file\n";
        return false;
      }
      shigarev::writePersons(out, persons);
      out.close();
      return true;
    }

    printInvalidCommand();
    return true;
  }
}

void shigarev::ensurePersonExists(DynArray< Person >& persons,
    size_t id)
{
  if (findPerson(persons, id) == nullptr) {
    addPersonSorted(persons, id, "");
  }
}

void shigarev::runInteractive(DynArray< Person >& persons,
    DynArray< Meeting >& meetings)
{
  std::string line;
  while (std::getline(std::cin, line)) {
    if (!parseCommand(line, persons, meetings)) {
      std::cerr << "Cannot open output file\n";
      return;
    }
  }
}
