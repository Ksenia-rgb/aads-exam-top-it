#include "functionsVector.hpp"
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

  void addAnonPerson(Vector< Person >& persons, size_t id)
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

}
