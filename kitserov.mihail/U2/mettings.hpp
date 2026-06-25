#ifndef METTINGS_HPP
#define METTINGS_HPP

#include <string>
#include <cstddef>
#include <algorithm>
namespace kitserov
{
  using Neighbor = std::pair< size_t, int >;
  struct Meeting {
    size_t id1_;
    size_t id2_;
    int duration_;
  };
  struct MeetingsContainer {
    Meeting* data_;
    size_t size_;
    size_t capacity_;
  };
  void addMeeting(MeetingsContainer& c, std::size_t id1, std::size_t id2, int dur) {
    if (c.size_ == c.capacity_) {
      std::size_t new_cap = (c.capacity_ == 0) ? 8 : c.capacity_ * 2;
      Meeting* new_data = new Meeting[new_cap];
      try {
        for (std::size_t i = 0; i < c.size_; ++i) {
          new_data[i] = c.data_[i];
        }
        new_data[c.size_] = Meeting{id1, id2, dur};
      } catch (...) {
        delete[] new_data;
        throw;
      }
      delete[] c.data_;
      c.data_ = new_data;
      c.capacity_ = new_cap;
    } else {
      c.data_[c.size_] = Meeting{id1, id2, dur};
    }
    ++c.size_;
  }
  void removeSelfMeetings(MeetingsContainer& c) {
    size_t write = 0;
    for (size_t i = 0; i < c.size_; ++i) {
      if (c.data_[i].id1_ != c.data_[i].id2_) {
        c.data_[write++] = c.data_[i];
      }
    }
    c.size_ = write;
  }
  void replaceIdInMeetings(MeetingsContainer& c, std::size_t oldId, std::size_t newId) {
    for (std::size_t i = 0; i < c.size_; ++i) {
      if (c.data_[i].id1_ == oldId) {
        c.data_[i].id1_ = newId;
      }
      if (c.data_[i].id2_ == oldId) {
        c.data_[i].id2_ = newId;
      }
    }
    removeSelfMeetings(c);
  }
  Neighbor* getMeetingsForId(const MeetingsContainer& c, size_t id, size_t& count)
  {
    count = 0;
    for (size_t i = 0; i < c.size_; ++i) {
      if (c.data_[i].id1_ == id || c.data_[i].id2_ == id) {
        ++count;
      }
    }
    if (count == 0) {
      return nullptr;
    }
    Neighbor* arr = new Neighbor[count];
    size_t idx = 0;
    for (size_t i = 0; i < c.size_; ++i) {
        if (c.data_[i].id1_ == id) {
            arr[idx++] = Neighbor{c.data_[i].id2_, c.data_[i].duration_};
        } else if (c.data_[i].id2_ == id) {
            arr[idx++] = Neighbor{c.data_[i].id1_, c.data_[i].duration_};
        }
    }
    return arr;
  }
  void sortNeighborPairs(Neighbor* arr, size_t count) {
    std::sort(arr, arr + count, [](const Neighbor& a, const Neighbor& b) {
      if (a.first != b.first) {
        return a.first < b.first;
      }
      return a.second < b.second;
    });
  }
  
}


#endif
