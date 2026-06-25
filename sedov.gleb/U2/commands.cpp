#include "commands.hpp"
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <cstddef>
#include "bstree.hpp"
#include "sorted_list.hpp"

namespace sedov
{
  namespace detail
  {
    struct AnonPrinter
    {
      std::ostream & out;
    };

    void anonVisit(AnonPrinter & printer, size_t id, const Vertex & vertex);

    struct MeetingPrinter
    {
      std::ostream & out;
      size_t low;
      size_t high;
      bool useLow;
      bool useHigh;
    };

    void printEdgeList(std::ostream & out, size_t partner, ListNode< size_t > * head, size_t low, size_t high,
      bool useLow, bool useHigh);
    void meetingVisit(MeetingPrinter & printer, size_t partner, ListNode< size_t > * head);
    bool readQuoted(std::istream & in, std::string & result);
    void printMeetings(std::ostream & out, Graph * vertex, size_t low, size_t high, bool useLow, bool useHigh);
    void printCommons(std::ostream & out, Adjacency * first, Adjacency * second);
    void doDeanon(std::ostream & out, Graph *& root, size_t anon, size_t target);
    void mergeEdges(Graph *& root, size_t target, Adjacency * source);
  }
}

void sedov::detail::anonVisit(AnonPrinter & printer, size_t id, const Vertex & vertex)
{
  if (!vertex.described)
  {
    printer.out << id << '\n';
  }
}

void sedov::detail::printEdgeList(std::ostream & out, size_t partner, ListNode< size_t > * head, size_t low,
  size_t high, bool useLow, bool useHigh)
{
  for (ListNode< size_t > * node = head; node != nullptr; node = node->next)
  {
    if (useLow && !(node->value < low))
    {
      continue;
    }
    if (useHigh && !(high < node->value))
    {
      continue;
    }
    out << partner << ' ' << node->value << '\n';
  }
}

void sedov::detail::meetingVisit(MeetingPrinter & printer, size_t partner, ListNode< size_t > * head)
{
  printEdgeList(printer.out, partner, head, printer.low, printer.high, printer.useLow, printer.useHigh);
}

bool sedov::detail::readQuoted(std::istream & in, std::string & result)
{
  char ch = 0;
  in >> std::ws;
  if (!in.get(ch) || ch != '"')
  {
    return false;
  }
  result.clear();
  while (in.get(ch) && ch != '"')
  {
    result.push_back(ch);
  }
  return in.good() || in.eof();
}

void sedov::detail::printMeetings(std::ostream & out, Graph * vertex, size_t low, size_t high, bool useLow,
  bool useHigh)
{
  MeetingPrinter printer{ out, low, high, useLow, useHigh };
  auto visitor = [&printer](size_t partner, ListNode< size_t > * head)
  {
    meetingVisit(printer, partner, head);
  };
  inorderBst(vertex->value.meetings, visitor);
}

void sedov::detail::printCommons(std::ostream & out, Adjacency * first, Adjacency * second)
{
  auto collector = [&out, second](size_t partner, ListNode< size_t > * head)
  {
    static_cast< void >(head);
    if (findBst(second, partner) != nullptr)
    {
      out << partner << '\n';
    }
  };
  inorderBst(first, collector);
}

void sedov::detail::mergeEdges(Graph *& root, size_t target, Adjacency * source)
{
  auto mover = [&root, target](size_t partner, ListNode< size_t > * head)
  {
    for (ListNode< size_t > * node = head; node != nullptr; node = node->next)
    {
      addMeeting(root, target, partner, node->value);
    }
  };
  inorderBst(source, mover);
}

void sedov::detail::doDeanon(std::ostream & out, Graph *& root, size_t anon, size_t target)
{
  Graph * anonVertex = findBst(root, anon);
  Graph * targetVertex = findBst(root, target);
  if (anonVertex == nullptr || targetVertex == nullptr)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (anonVertex->value.described || !targetVertex->value.described)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  auto eraser = [&root, anon](size_t partner, ListNode< size_t > * head)
  {
    static_cast< void >(head);
    Graph * other = findBst(root, partner);
    if (other == nullptr)
    {
      return;
    }
    Adjacency * back = findBst(other->value.meetings, anon);
    if (back != nullptr)
    {
      clearList(back->value);
      back->value = nullptr;
    }
  };
  inorderBst(anonVertex->value.meetings, eraser);
  mergeEdges(root, target, anonVertex->value.meetings);
  Adjacency * selfLoop = findBst(targetVertex->value.meetings, target);
  if (selfLoop != nullptr)
  {
    clearList(selfLoop->value);
    selfLoop->value = nullptr;
  }
  anonVertex->value.described = true;
}

namespace sedov
{
  namespace detail
  {
    void cmdAnons(std::ostream & out, Graph * root);
    void cmdDesc(std::istream & in, std::ostream & out, Graph * root);
    void cmdRedesc(std::istream & in, std::ostream & out, Graph * root);
    void cmdMeets(std::istream & in, std::ostream & out, Graph * root);
    void cmdCommons(std::istream & in, std::ostream & out, Graph * root);
    void cmdBound(std::istream & in, std::ostream & out, Graph * root, bool greater);
    void cmdOutPersons(std::istream & in, std::ostream & out, Graph * root);
  }
}

void sedov::detail::cmdAnons(std::ostream & out, Graph * root)
{
  AnonPrinter printer{ out };
  auto visitor = [&printer](size_t id, const Vertex & vertex)
  {
    anonVisit(printer, id, vertex);
  };
  inorderBst(root, visitor);
}

void sedov::detail::cmdDesc(std::istream & in, std::ostream & out, Graph * root)
{
  size_t id = 0;
  if (!(in >> id))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph * vertex = findBst(root, id);
  if (vertex == nullptr)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (!vertex->value.described)
  {
    out << "<ANON>\n";
    return;
  }
  out << vertex->value.description << '\n';
}

void sedov::detail::cmdRedesc(std::istream & in, std::ostream & out, Graph * root)
{
  size_t id = 0;
  std::string description;
  if (!(in >> id) || !readQuoted(in, description) || description.empty())
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph * vertex = findBst(root, id);
  if (vertex == nullptr)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  vertex->value.description = description;
  vertex->value.described = true;
}

void sedov::detail::cmdMeets(std::istream & in, std::ostream & out, Graph * root)
{
  size_t id = 0;
  if (!(in >> id))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph * vertex = findBst(root, id);
  if (vertex == nullptr)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  printMeetings(out, vertex, 0, 0, false, false);
}

void sedov::detail::cmdCommons(std::istream & in, std::ostream & out, Graph * root)
{
  size_t first = 0;
  size_t second = 0;
  if (!(in >> first >> second))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph * firstVertex = findBst(root, first);
  Graph * secondVertex = findBst(root, second);
  if (firstVertex == nullptr || secondVertex == nullptr)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  printCommons(out, firstVertex->value.meetings, secondVertex->value.meetings);
}

void sedov::detail::cmdBound(std::istream & in, std::ostream & out, Graph * root, bool greater)
{
  size_t time = 0;
  size_t id = 0;
  if (!(in >> time >> id))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  Graph * vertex = findBst(root, id);
  if (vertex == nullptr)
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  if (greater)
  {
    printMeetings(out, vertex, 0, time, false, true);
  }
  else
  {
    printMeetings(out, vertex, time, 0, true, false);
  }
}

void sedov::detail::cmdOutPersons(std::istream & in, std::ostream & out, Graph * root)
{
  std::string filename;
  if (!(in >> filename))
  {
    out << "<INVALID COMMAND>\n";
    return;
  }
  auto visitor = [&out](size_t id, const Vertex & vertex)
  {
    if (vertex.described)
    {
      out << id << ' ' << vertex.description << '\n';
    }
  };
  inorderBst(root, visitor);
}

void sedov::runCommands(std::istream & in, std::ostream & out, Graph *& root)
{
  std::string command;
  while (in >> command)
  {
    if (command == "anons")
    {
      detail::cmdAnons(out, root);
    }
    else if (command == "deanon")
    {
      size_t anon = 0;
      size_t target = 0;
      if (!(in >> anon >> target))
      {
        out << "<INVALID COMMAND>\n";
      }
      else
      {
        detail::doDeanon(out, root, anon, target);
      }
    }
    else if (command == "redesc")
    {
      detail::cmdRedesc(in, out, root);
    }
    else if (command == "desc")
    {
      detail::cmdDesc(in, out, root);
    }
    else if (command == "meets")
    {
      detail::cmdMeets(in, out, root);
    }
    else if (command == "commons")
    {
      detail::cmdCommons(in, out, root);
    }
    else if (command == "less")
    {
      detail::cmdBound(in, out, root, false);
    }
    else if (command == "greater")
    {
      detail::cmdBound(in, out, root, true);
    }
    else if (command == "out-persons")
    {
      detail::cmdOutPersons(in, out, root);
    }
    else
    {
      out << "<INVALID COMMAND>\n";
    }
  }
}
