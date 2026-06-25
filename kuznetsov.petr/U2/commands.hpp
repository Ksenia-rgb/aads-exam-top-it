#ifndef AADS_EXAM_TOP_IT_COMMANDS_HPP
#define AADS_EXAM_TOP_IT_COMMANDS_HPP
#include <iosfwd>
#include <person.hpp>
#include <darray.hpp>

namespace kuznetsov {

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
