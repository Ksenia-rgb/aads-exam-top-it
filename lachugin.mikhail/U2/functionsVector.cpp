#include "functionsVector.hpp"
#include "fstream"
namespace lachugin
{
  bool readMeeting(std::istream& in, Meeting& meeting)
  {
    in >> meeting.firstId >> meeting.secondId >> meeting.time;

    if (!in)
    {
      return false;
    }

    return true;
  }

  bool containsPerson(const Vector< Person >& persons, size_t id)
  {
    for (size_t i = 0; i < persons.size; i++)
    {
      if (persons.data[i].id == id)
      {
        return true;
      }
    }

    return false;
  }

  Person* findPerson(Vector< Person >& persons, size_t id)
  {
    for (size_t i = 0; i < persons.size; i++)
    {
      if (persons.data[i].id == id)
      {
        return &persons.data[i];
      }
    }

    return nullptr;
  }

  const Person* findPerson(const Vector< Person >& persons, size_t id)
  {
    for (size_t i = 0; i < persons.size; i++)
    {
      if (persons.data[i].id == id)
      {
        return &persons.data[i];
      }
    }

    return nullptr;
  }

  void addPerson(Vector< Person >& persons, size_t id)
  {
    if (containsPerson(persons, id))
    {
      return;
    }

    Person person;
    person.id = id;
    person.info = "";
    pushBack(persons, person);
  }

  void readPersons(std::istream& in, Vector< Person >& persons, size_t& success, size_t& ignored)
  {
    std::string line;
    while (std::getline(in, line))
    {
      if (line.empty())
      {
        continue;
      }

      Person person;
      if (!parseLine(line, person))
      {
        ignored++;
        continue;
      }

      if (containsPerson(persons, person.id))
      {
        ignored++;
        continue;
      }

      pushBack(persons, person);
      success++;
    }
  }

  void desc(const Vector< Person >& persons, size_t id)
  {
    const Person* person = findPerson(persons, id);

    if (person == nullptr)
    {
      std::cout << "INVALID COMMAND\n";
      return;
    }

    if (person->info.empty())
    {
      std::cout << "<ANON>\n";
    }
    else
    {
      std::cout << person->info << '\n';
    }
  }

  void redesc(Vector< Person >& persons, size_t id, const std::string& info)
  {
    Person* person = findPerson(persons, id);
    if (person == nullptr)
    {
      std::cout << "INVALID COMMAND\n";
      return;
    }

    person->info = info;
  }

  void anons(const Vector< Person >& persons)
  {
    Vector< size_t > ids;
    initVector(ids);
    for (size_t i = 0; i < persons.size; i++)
    {
      if (persons.data[i].info.empty())
      {
        pushBack(ids, persons.data[i].id);
      }
    }

    for (size_t i = 0; i < ids.size; i++)
    {
      for (size_t j = i + 1; j < ids.size; j++)
      {
        if (ids.data[j] < ids.data[i])
        {
          size_t temp = ids.data[i]; ids.data[i] = ids.data[j]; ids.data[j] = temp;
        }
      }
    }

    for (size_t i = 0; i < ids.size; i++)
    {
      std::cout << ids.data[i] << '\n';
    }

    clearVector(ids);
  }

  void outPersons(const Vector< Person >& persons, const std::string& filename)
  {
    std::ofstream out(filename);

    if (!out)
    {
      std::cout << "INVALID COMMAND\n";
      return;
    }
    for (size_t i = 0; i < persons.size; i++)
    {
      if (!persons.data[i].info.empty())
      {
        out << persons.data[i].id << ' ' << persons.data[i].info << '\n';
      }
    }
  }

  void addMeeting(Vector< Meeting >& meetings, size_t firstId, size_t secondId, size_t time)
  {
    if (firstId == secondId)
    {
      return;
    }

    Meeting meeting;
    meeting.firstId = firstId;
    meeting.secondId = secondId;
    meeting.time = time;

    pushBack(meetings, meeting);
  }

  void meets(const Vector< Meeting >& meetings, size_t id)
  {
    Vector< MeetInfo > result;
    initVector(result);

    for (size_t i = 0; i < meetings.size; i++)
    {
      if (meetings.data[i].firstId == id)
      {
        MeetInfo info;
        info.id = meetings.data[i].secondId;
        info.time = meetings.data[i].time;
        pushBack(result, info);
      }
      else if (meetings.data[i].secondId == id)
      {
        MeetInfo info;
        info.id = meetings.data[i].firstId;
        info.time = meetings.data[i].time;
        pushBack(result, info);
      }
    }

    sortMeetInfos(result);

    for (size_t i = 0; i < result.size; i++)
    {
      std::cout << result.data[i].id << ' ' << result.data[i].time << '\n';
    }

    clearVector(result);
  }

  void sortMeetInfos(Vector< MeetInfo >& infos)
  {
    for (size_t i = 0; i < infos.size; i++)
    {
      for (size_t j = i + 1; j < infos.size; j++)
      {
        if (infos.data[j].id < infos.data[i].id)
        {
          MeetInfo temp = infos.data[i];
          infos.data[i] = infos.data[j];
          infos.data[j] = temp;
        }
        else if (infos.data[j].id == infos.data[i].id && infos.data[j].time < infos.data[i].time)
        {
          MeetInfo temp = infos.data[i];
          infos.data[i] = infos.data[j];
          infos.data[j] = temp;
        }
      }
    }
  }

  void less(const Vector< Meeting >& meetings, size_t time, size_t id)
  {
    Vector< MeetInfo > result;
    initVector(result);

    for (size_t i = 0; i < meetings.size; i++)
    {
      if (meetings.data[i].time >= time)
      {
        continue;
      }

      if (meetings.data[i].firstId == id)
      {
        MeetInfo info;
        info.id = meetings.data[i].secondId;
        info.time = meetings.data[i].time;
        pushBack(result, info);
      }
      else if (meetings.data[i].secondId == id)
      {
        MeetInfo info;
        info.id = meetings.data[i].firstId;
        info.time = meetings.data[i].time;
        pushBack(result, info);
      }
    }

    sortMeetInfos(result);
    sortMeetInfos(result);

    for (size_t i = 0; i < result.size; i++)
    {
      std::cout << result.data[i].id << ' ' << result.data[i].time << '\n';
    }

    clearVector(result);
  }



}
