#ifndef FUNCTIONS_VECTOR_HPP
#define FUNCTIONS_VECTOR_HPP
#include "Vector.hpp"
#include "Meeting.hpp"
#include <iostream>
#include "../common/functions.hpp"

namespace lachugin
{
  void readPersons(std::istream& in, Vector< Person >& persons, size_t& success, size_t& ignored);
  bool readMeeting(std::istream& in, Meeting& meeting);
  bool containsPerson(const Vector< Person >& persons, size_t id);
  Person* findPerson(Vector< Person >& persons, size_t id);
  const Person* findPerson(const Vector< Person >& persons, size_t id);
  void addPerson(Vector< Person >& persons, size_t id);
  void addMeeting(Vector< Meeting >& meetings, size_t firstId, size_t secondId, size_t time);

  void sortMeetInfos(Vector< MeetInfo >& result);

  void desc(const Vector< Person >& persons, size_t id);
  void redesc(Vector< Person >& persons, size_t id, const std::string& info);
  void anons(const Vector< Person >& persons);
  void outPersons(const Vector< Person >& persons, const std::string& filename);
  void meets(const Vector< Meeting >& meetings, size_t id);
  void less(const Vector< Meeting >& meetings, size_t time, size_t id);


}


#endif

