#include "meeting.hpp"
#include <iostream>

kuznetsov::Meeting kuznetsov::readMeeting(std::istream& in, bool& success, darray< Person >& p)
{
  size_t id1 = 0, id2 = 0, time = 0;
  in >> id1 >> id2 >> time;
  if (!in) {
    success = false;
    return Meeting{0, 0, 0};
  }
  success = true;
  Person pr1{id1, ""};
  if (!containsDarray(p, pr1, equalPersons)) {
    pushBackDarray(p, pr1);
  }
  Person pr2{id2, ""};
  if (!containsDarray(p, pr2, equalPersons)) {
    pushBackDarray(p, pr2);
  }
  return Meeting{id1, id2, time};
}

kuznetsov::darray< kuznetsov::Meeting > kuznetsov::readArrayMeets(std::istream& in, darray< Person >& p, bool& ok)
{
  darray< Meeting > meets = makeDarray< Meeting >(8);
  ok = true;
  in >> std::ws;
  while (!in.eof()) {
    bool success = false;
    Meeting m = readMeeting(in, success, p);
    if (!success) {
      ok = false;
      break;
    }
    if (m.id1 != m.id2) {
      pushBackDarray(meets, m);
    }
    in >> std::ws;
  }
  return meets;
}
