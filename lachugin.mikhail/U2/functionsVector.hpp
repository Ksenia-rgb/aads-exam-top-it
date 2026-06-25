#ifndef FUNCTIONS_VECTOR_HPP
#define FUNCTIONS_VECTOR_HPP
#include "Vector.hpp"
#include "Meeting.hpp"
#include "Person.hpp"
#include <iostream>
#include "../U1/functions.hpp"

namespace lachugin
{
  void readPersons(std::istream& in, Vector< Person >& persons, size_t& success, size_t& ignored);
  bool readMeeting(std::istream& in, Meeting& meeting);
  bool containsPerson(const Vector< Person >& persons, size_t id);
  Person* findPerson(Vector< Person >& persons, size_t id);
  const Person* findPerson(const Vector< Person >& persons, size_t id);
  void addPerson(Vector< Person >& persons, size_t id);

  void desc(const Vector< Person >& persons, size_t id);

}


#endif

