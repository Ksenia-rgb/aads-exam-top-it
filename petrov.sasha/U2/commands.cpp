#include "commands.hpp"

#include <iostream>

namespace
{
  void sortMeetings(petrov::Meeting* data, std::size_t size)
  {
    for (std::size_t i = 0; i < size; ++i)
    {
      for (std::size_t j = 0; j + 1 < size; ++j)
      {
        bool needSwap = false;

        if (data[j].first > data[j + 1].first)
        {
          needSwap = true;
        }
        else if (data[j].first == data[j + 1].first)
        {
          if (data[j].time > data[j + 1].time)
          {
            needSwap = true;
          }
        }
        if (needSwap)
        {
          petrov::Meeting tmp = data[j];
          data[j] = data[j + 1];
          data[j + 1] = tmp;
        }
      }
    }
  }

  bool findPersonIndex(const petrov::DataBase& db, std::size_t id, std::size_t& index)
  {
    for (std::size_t i = 0; i < db.persons.size; ++i)
    {
      if (db.persons.data[i].id == id)
      {
        index = i;
        return true;
      }
    }
    return false;
  }

  void commandDesc(petrov::DataBase& db)
  {
    std::size_t id = 0;
    if (!(std::cin >> id))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    std::size_t index = 0;
    if (!findPersonIndex(db, id, index))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    if (db.persons.data[index].hasInfo)
    {
      std::cout << db.persons.data[index].info << '\n';
    }
    else
    {
      std::cout << "<ANON>\n";
    }
  }

  void commandAnons(petrov::DataBase & db)
  {
    std::size_t count = 0;
    for (std::size_t i = 0; i < db.persons.size; ++i)
    {
      if (!db.persons.data[i].hasInfo)
      {
        ++count;
      }
    }
    std::size_t * temp = new std::size_t[count];
    std::size_t index = 0;
    for (std::size_t i = 0; i < db.persons.size; ++i)
    {
      if (!db.persons.data[i].hasInfo)
      {
        temp[index++] = db.persons.data[i].id;
      }
    }
    for (std::size_t i = 0; i < count; ++i)
    {
      for (std::size_t j = 0; j + 1 < count; ++j)
      {
        if (temp[j] > temp[j + 1])
        {
          std::size_t t = temp[j];
          temp[j] = temp[j + 1];
          temp[j + 1] = t;
        }
      }
    }
    for (std::size_t i = 0; i < count; ++i)
    {
      std::cout << temp[i] << '\n';
    }
    delete[] temp;
  }

  void commandMeets(petrov::DataBase& db)
  {
    std::size_t id = 0;
    if (!(std::cin >> id))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    std::size_t index = 0;
    if (!findPersonIndex(db, id, index))
    {
      std::cout << "<INVALID COMMAND>\n";
      return;
    }
    petrov::Meeting* temp = new petrov::Meeting[db.meetings.size];
    std::size_t count = 0;
    for (std::size_t i = 0; i < db.meetings.size; ++i)
    {
      petrov::Meeting m = db.meetings.data[i];
      if (m.first == id)
      {
        m.first = m.second;
        temp[count++] = m;
      }
      else if (m.second == id)
      {
        temp[count++] = m;
      }
    }
    sortMeetings(temp, count);
    for (std::size_t i = 0; i < count; ++i)
    {
      std::cout << temp[i].first << ' ' << temp[i].time << '\n';
    }

    delete[] temp;
  }
}

void petrov::commandLoop(DataBase& db)
{
  std::string command = "";
  while (std::cin >> command)
  {
    if (command == "desc")
    {
      commandDesc(db);
    }
    else if (command == "anons")
    {
      commandAnons(db);
    }
    else if (command == "meets")
    {
      commandMeets(db);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
