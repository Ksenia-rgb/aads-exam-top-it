#ifndef AADS_EXAM_TOP_IT_MEETING_HPP
#define AADS_EXAM_TOP_IT_MEETING_HPP
#include <cstddef>
#include <iosfwd>
#include <darray.hpp>
#include <person.hpp>

namespace kuznetsov {

  struct Meeting {
    size_t id1, id2;
    size_t time;
  };

  Meeting readMeeting(std::istream& in, bool& success, darray< Person >& p);
  darray< Meeting > readArrayMeets(std::istream& in, darray< Person >& p, bool& ok);

}

#endif
