#ifndef AADS_EXAM_TOP_IT_COMMANDS_HPP
#define AADS_EXAM_TOP_IT_COMMANDS_HPP
#include <iosfwd>
#include <person.hpp>
#include <darray.hpp>
#include "meeting.hpp"

namespace kuznetsov {

  namespace detail {
    struct meetingRecord {
      size_t id, time;
    };

    void sort(darray< size_t >&);
    void sort(darray< meetingRecord >&);
    size_t findPersonIdx(darray< Person >& pers, size_t id);
    darray< meetingRecord > collectMeetings(darray< Meeting >& mts, size_t id);
    darray< meetingRecord > filterMeetings(darray< meetingRecord >& src, size_t threshold, bool greater);
    darray< size_t > partnerIds(darray< Meeting >& mts, size_t id);
    void printMeetings(std::ostream& out, darray< meetingRecord >& arr);
  }

  void anons(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void deanon(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void redesc(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void desc(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void meets(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void commons(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void less(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void greater(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);
  void out_persons(std::istream&, std::ostream&, darray< Meeting >&, darray< Person >&);

}

#endif
