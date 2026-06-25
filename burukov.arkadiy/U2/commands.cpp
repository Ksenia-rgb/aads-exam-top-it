#include "commands.hpp"

#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <utility>

#include "array.hpp"
#include "array_sort.hpp"
#include "model.hpp"

namespace burukov
{

  namespace
  {

    bool edgeLess(const Edge& a, const Edge& b)
    {
      if (a.partner != b.partner)
      {
        return a.partner < b.partner;
      }
      return a.duration < b.duration;
    }

    bool sizeLess(const size_t& a, const size_t& b)
    {
      return a < b;
    }

    darray< size_t > sortedIds(Graph& graph, bool wantDescribed)
    {
      darray< size_t > ids = makeArray< size_t >(graph.vertices.size);
      try
      {
        for (size_t i = 0; i < graph.vertices.size; ++i)
        {
          if (graph.vertices.data[i].described == wantDescribed)
          {
            pushBackArray(ids, std::move(graph.vertices.data[i].id));
          }
        }
        sortArray(ids, sizeLess);
      }
      catch (...)
      {
        clearArray(ids);
        throw;
      }
      return ids;
    }

    darray< Edge > sortedEdges(const Vertex& vertex)
    {
      darray< Edge > sorted = copyArray(vertex.edges, vertex.edges.size);
      try
      {
        sortArray(sorted, edgeLess);
      }
      catch (...)
      {
        clearArray(sorted);
        throw;
      }
      return sorted;
    }

    void printEdges(std::ostream& out, const Vertex& vertex, size_t bound, bool useLess, bool useGreater)
    {
      darray< Edge > sorted = sortedEdges(vertex);
      try
      {
        for (size_t i = 0; i < sorted.size; ++i)
        {
          const Edge& edge = sorted.data[i];
          if (useLess && !(edge.duration < bound))
          {
            continue;
          }
          if (useGreater && !(bound < edge.duration))
          {
            continue;
          }
          out << edge.partner << " " << edge.duration << "\n";
        }
      }
      catch (...)
      {
        clearArray(sorted);
        throw;
      }
      clearArray(sorted);
    }

    bool readQuoted(std::istream& in, std::string& result)
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
      return ch == '"';
    }

    void cmdAnons(std::ostream& out, Graph& graph)
    {
      darray< size_t > ids = sortedIds(graph, false);
      try
      {
        for (size_t i = 0; i < ids.size; ++i)
        {
          out << ids.data[i] << "\n";
        }
      }
      catch (...)
      {
        clearArray(ids);
        throw;
      }
      clearArray(ids);
    }

    void cmdDesc(std::istream& in, std::ostream& out, Graph& graph)
    {
      size_t id = 0;
      if (!(in >> id))
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      Vertex* vertex = findVertex(graph, id);
      if (!vertex)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      if (!vertex->described)
      {
        out << "<ANON>\n";
        return;
      }
      out << vertex->description << "\n";
    }

    void cmdRedesc(std::istream& in, std::ostream& out, Graph& graph)
    {
      size_t id = 0;
      std::string description;
      if (!(in >> id) || !readQuoted(in, description) || description.empty())
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      Vertex* vertex = findVertex(graph, id);
      if (!vertex)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      vertex->description = description;
      vertex->described = true;
    }

    void cmdMeets(std::istream& in, std::ostream& out, Graph& graph)
    {
      size_t id = 0;
      if (!(in >> id))
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      Vertex* vertex = findVertex(graph, id);
      if (!vertex)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      printEdges(out, *vertex, 0, false, false);
    }

    void cmdCommons(std::istream& in, std::ostream& out, Graph& graph)
    {
      size_t first = 0;
      size_t second = 0;
      if (!(in >> first >> second))
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      Vertex* firstVertex = findVertex(graph, first);
      Vertex* secondVertex = findVertex(graph, second);
      if (!firstVertex || !secondVertex)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      darray< Edge > sorted = sortedEdges(*firstVertex);
      try
      {
        size_t last = 0;
        bool hasLast = false;
        for (size_t i = 0; i < sorted.size; ++i)
        {
          size_t partner = sorted.data[i].partner;
          if (hasLast && partner == last)
          {
            continue;
          }
          bool present = false;
          for (size_t j = 0; j < secondVertex->edges.size; ++j)
          {
            if (secondVertex->edges.data[j].partner == partner)
            {
              present = true;
              break;
            }
          }
          if (present)
          {
            out << partner << "\n";
          }
          last = partner;
          hasLast = true;
        }
      }
      catch (...)
      {
        clearArray(sorted);
        throw;
      }
      clearArray(sorted);
    }

    void cmdBound(std::istream& in, std::ostream& out, Graph& graph, bool greater)
    {
      size_t time = 0;
      size_t id = 0;
      if (!(in >> time >> id))
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      Vertex* vertex = findVertex(graph, id);
      if (!vertex)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      printEdges(out, *vertex, time, !greater, greater);
    }

    void removeEdgesTo(Vertex& vertex, size_t partner)
    {
      size_t write = 0;
      for (size_t read = 0; read < vertex.edges.size; ++read)
      {
        if (vertex.edges.data[read].partner != partner)
        {
          vertex.edges.data[write] = std::move(vertex.edges.data[read]);
          ++write;
        }
      }
      vertex.edges.size = write;
    }

    void cmdDeanon(std::ostream& out, Graph& graph, size_t anon, size_t target)
    {
      Vertex* anonVertex = findVertex(graph, anon);
      Vertex* targetVertex = findVertex(graph, target);
      if (!anonVertex || !targetVertex)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      if (anonVertex->described || !targetVertex->described)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      for (size_t i = 0; i < anonVertex->edges.size; ++i)
      {
        size_t partner = anonVertex->edges.data[i].partner;
        size_t duration = anonVertex->edges.data[i].duration;
        Vertex* other = findVertex(graph, partner);
        if (other)
        {
          removeEdgesTo(*other, anon);
        }
        addMeeting(graph, target, partner, duration);
      }
      anonVertex->edges.size = 0;
      Vertex* freshTarget = findVertex(graph, target);
      removeEdgesTo(*freshTarget, target);
      anonVertex->described = true;
    }

    void cmdOutPersons(std::istream& in, std::ostream& out, Graph& graph)
    {
      std::string filename;
      if (!(in >> filename))
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      std::ofstream file(filename.c_str());
      if (!file)
      {
        out << "<INVALID COMMAND>\n";
        return;
      }
      darray< size_t > ids = sortedIds(graph, true);
      try
      {
        for (size_t i = 0; i < ids.size; ++i)
        {
          Vertex* vertex = findVertex(graph, ids.data[i]);
          file << vertex->id << " " << vertex->description << "\n";
        }
      }
      catch (...)
      {
        clearArray(ids);
        throw;
      }
      clearArray(ids);
    }

  }

  void runCommands(std::istream& in, std::ostream& out, Graph& graph)
  {
    std::string command;
    while (in >> command)
    {
      if (command == "anons")
      {
        cmdAnons(out, graph);
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
          cmdDeanon(out, graph, anon, target);
        }
      }
      else if (command == "redesc")
      {
        cmdRedesc(in, out, graph);
      }
      else if (command == "desc")
      {
        cmdDesc(in, out, graph);
      }
      else if (command == "meets")
      {
        cmdMeets(in, out, graph);
      }
      else if (command == "commons")
      {
        cmdCommons(in, out, graph);
      }
      else if (command == "less")
      {
        cmdBound(in, out, graph, false);
      }
      else if (command == "greater")
      {
        cmdBound(in, out, graph, true);
      }
      else if (command == "out-persons")
      {
        cmdOutPersons(in, out, graph);
      }
      else
      {
        out << "<INVALID COMMAND>\n";
      }
    }
  }

}
