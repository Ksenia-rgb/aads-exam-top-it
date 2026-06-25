#ifndef METTINGS_HPP
#define METTINGS_HPP

#include <string>
#include <cstddef>
namespace kitserov
{
  struct Meeting {
    size_t id1_;
    size_t id2_;
    int duration_;
  };
  struct AnonsContainer {
    size_t* data_;
    size_t size_;
    size_t capacity_;
  };
  struct MeetingsContainer {
    Meeting* data_;
    size_t size_;
    size_t capacity_;
  };
  
}


#endif
