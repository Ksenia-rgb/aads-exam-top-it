#include "commands.hpp"
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>

void kuznetsov::detail::sort(darray< size_t >& arr)
{
  for (size_t i = 0; i < arr.size; ++i) {
    size_t min = i;
    for (size_t j = i + 1; j < arr.size; ++j) {
      if (arr.data[j] < arr.data[min]) {
        min = j;
      }
    }
    if (min != i) {
      std::swap(arr.data[min], arr.data[i]);
    }
  }
}

size_t kuznetsov::detail::findPersonIdx(darray< Person >& pers, size_t id)
{
  for (size_t i = 0; i < pers.size; ++i) {
    if (pers.data[i].id == id) {
      return i;
    }
  }
  return pers.cap;
}

void kuznetsov::anons(std::istream&, std::ostream& out, darray< Meeting >&, darray< Person >& pers)
{
  darray< size_t > ids = makeDarray< size_t >(8);
  for (size_t i = 0; i < pers.size; ++i) {
    if (pers.data[i].info == "") {
      pushBackDarray(ids, pers.data[i].id);
    }
  }
  detail::sort(ids);
  for (size_t i = 0; i < ids.size; ++i) {
    if (i != 0) {
      out << '\n';
    }
    out << ids.data[i];
  }
}

void kuznetsov::deanon(std::istream& in, std::ostream&, darray< Meeting >& mts, darray< Person >& prs)
{
  size_t anonId, id;
  in >> anonId >> id;
  if (in.fail()) {
    throw std::logic_error("Smth go bad");
  }
  if (prs.data[detail::findPersonIdx(prs, anonId)].info != "") {
    throw std::logic_error("Bad anon");
  }
  if (prs.data[detail::findPersonIdx(prs, id)].info == "") {
    throw std::logic_error("Bad id");
  }

  for (size_t i = 0; i < mts.size; ++i) {
    if (mts.data[i].id1 == anonId) {
      mts.data[i].id1 = id;
    }
    if (mts.data[i].id2 == anonId) {
      mts.data[i].id2 = id;
    }
  }
  size_t i = 0;
  while (i < mts.size) {
    if (mts.data[i].id1 == mts.data[i].id2) {
      removeDarray(mts, i);
      i -= 2;
    }
    i += 1;
  }
}

void kuznetsov::detail::sort(darray< meetingRecord >& arr)
{
  for (size_t i = 0; i < arr.size; ++i) {
    size_t min = i;
    for (size_t j = i + 1; j < arr.size; ++j) {
      bool less = arr.data[j].id < arr.data[min].id;
      bool sameLess = arr.data[j].id == arr.data[min].id && arr.data[j].time < arr.data[min].time;
      if (less || sameLess) {
        min = j;
      }
    }
    if (min != i) {
      std::swap(arr.data[min], arr.data[i]);
    }
  }
}

kuznetsov::darray< kuznetsov::detail::meetingRecord > kuznetsov::detail::collectMeetings(darray< Meeting >& mts, size_t id)
{
  darray< meetingRecord > res = makeDarray< meetingRecord >(8);
  try {
    for (size_t i = 0; i < mts.size; ++i) {
      meetingRecord r{0, 0};
      if (mts.data[i].id1 == id) {
        r.id = mts.data[i].id2;
        r.time = mts.data[i].time;
      } else if (mts.data[i].id2 == id) {
        r.id = mts.data[i].id1;
        r.time = mts.data[i].time;
      } else {
        continue;
      }
      pushBackDarray(res, r);
    }
  } catch (...) {
    clearDarray(res);
    throw;
  }
  return res;
}

kuznetsov::darray< kuznetsov::detail::meetingRecord > kuznetsov::detail::filterMeetings(darray< meetingRecord >& src, size_t threshold, bool greater)
{
  darray< meetingRecord > res = makeDarray< meetingRecord >(8);
  try {
    for (size_t i = 0; i < src.size; ++i) {
      bool ok = greater ? (src.data[i].time > threshold) : (src.data[i].time < threshold);
      if (ok) {
        meetingRecord r = src.data[i];
        pushBackDarray(res, r);
      }
    }
  } catch (...) {
    clearDarray(res);
    throw;
  }
  return res;
}

kuznetsov::darray< size_t > kuznetsov::detail::partnerIds(darray< Meeting >& mts, size_t id)
{
  darray< size_t > res = makeDarray< size_t >(8);
  try {
    for (size_t i = 0; i < mts.size; ++i) {
      size_t other = 0;
      if (mts.data[i].id1 == id) {
        other = mts.data[i].id2;
      } else if (mts.data[i].id2 == id) {
        other = mts.data[i].id1;
      } else {
        continue;
      }
      bool found = false;
      for (size_t j = 0; j < res.size; ++j) {
        if (res.data[j] == other) {
          found = true;
          break;
        }
      }
      if (!found) {
        pushBackDarray(res, other);
      }
    }
  } catch (...) {
    clearDarray(res);
    throw;
  }
  sort(res);
  return res;
}

void kuznetsov::detail::printMeetings(std::ostream& out, darray< meetingRecord >& arr)
{
  for (size_t i = 0; i < arr.size; ++i) {
    if (i != 0) {
      out << '\n';
    }
    out << arr.data[i].id << ' ' << arr.data[i].time;
  }
}

void kuznetsov::redesc(std::istream& in, std::ostream&, darray< Meeting >&, darray< Person >& pers)
{
  size_t id = 0;
  std::string desc;
  if (!(in >> id) || !(in >> std::quoted(desc))) {
    throw std::logic_error("redesc");
  }
  size_t idx = detail::findPersonIdx(pers, id);
  if (idx == pers.cap) {
    throw std::logic_error("redesc");
  }
  pers.data[idx].info = desc;
}

void kuznetsov::desc(std::istream& in, std::ostream& out, darray< Meeting >&, darray< Person >& pers)
{
  size_t id = 0;
  if (!(in >> id)) {
    throw std::logic_error("desc");
  }
  size_t idx = detail::findPersonIdx(pers, id);
  if (idx == pers.cap) {
    throw std::logic_error("desc");
  }
  if (pers.data[idx].info == "") {
    out << "<ANON>";
  } else {
    out << pers.data[idx].info;
  }
}

void kuznetsov::meets(std::istream& in, std::ostream& out, darray< Meeting >& mts, darray< Person >& pers)
{
  size_t id = 0;
  if (!(in >> id)) {
    throw std::logic_error("meets");
  }
  if (detail::findPersonIdx(pers, id) == pers.cap) {
    throw std::logic_error("meets");
  }
  darray< detail::meetingRecord > rec = detail::collectMeetings(mts, id);
  detail::sort(rec);
  detail::printMeetings(out, rec);
  clearDarray(rec);
}

void kuznetsov::commons(std::istream& in, std::ostream& out, darray< Meeting >& mts, darray< Person >& pers)
{
  size_t id1 = 0, id2 = 0;
  if (!(in >> id1 >> id2)) {
    throw std::logic_error("commons");
  }
  if (detail::findPersonIdx(pers, id1) == pers.cap || detail::findPersonIdx(pers, id2) == pers.cap) {
    throw std::logic_error("commons");
  }
  darray< size_t > p1 = detail::partnerIds(mts, id1);
  darray< size_t > p2;
  try {
    p2 = detail::partnerIds(mts, id2);
  } catch (...) {
    clearDarray(p1);
    throw;
  }
  size_t i = 0, j = 0;
  bool first = true;
  while (i < p1.size && j < p2.size) {
    if (p1.data[i] == p2.data[j]) {
      if (!first) {
        out << '\n';
      }
      out << p1.data[i];
      first = false;
      ++i;
      ++j;
    } else if (p1.data[i] < p2.data[j]) {
      ++i;
    } else {
      ++j;
    }
  }
  clearDarray(p1);
  clearDarray(p2);
}

void kuznetsov::less(std::istream& in, std::ostream& out, darray< Meeting >& mts, darray< Person >& pers)
{
  size_t time = 0, id = 0;
  if (!(in >> time >> id)) {
    throw std::logic_error("less");
  }
  if (detail::findPersonIdx(pers, id) == pers.cap) {
    throw std::logic_error("less");
  }
  darray< detail::meetingRecord > all = detail::collectMeetings(mts, id);
  darray< detail::meetingRecord > filtered;
  try {
    filtered = detail::filterMeetings(all, time, false);
  } catch (...) {
    clearDarray(all);
    throw;
  }
  clearDarray(all);
  detail::sort(filtered);
  detail::printMeetings(out, filtered);
  clearDarray(filtered);
}

void kuznetsov::greater(std::istream& in, std::ostream& out, darray< Meeting >& mts, darray< Person >& pers)
{
  size_t time = 0, id = 0;
  if (!(in >> time >> id)) {
    throw std::logic_error("greater");
  }
  if (detail::findPersonIdx(pers, id) == pers.cap) {
    throw std::logic_error("greater");
  }
  darray< detail::meetingRecord > all = detail::collectMeetings(mts, id);
  darray< detail::meetingRecord > filtered;
  try {
    filtered = detail::filterMeetings(all, time, true);
  } catch (...) {
    clearDarray(all);
    throw;
  }
  clearDarray(all);
  detail::sort(filtered);
  detail::printMeetings(out, filtered);
  clearDarray(filtered);
}

void kuznetsov::out_persons(std::istream& in, std::ostream&, darray< Meeting >&, darray< Person >& pers)
{
  std::string path;
  if (!(in >> path)) {
    throw std::logic_error("out-persons");
  }
  std::ofstream ofile(path);
  if (!ofile) {
    throw std::logic_error("out-persons");
  }
  for (size_t i = 0; i < pers.size; ++i) {
    if (pers.data[i].info != "") {
      ofile << pers.data[i].id << ' ' << pers.data[i].info << '\n';
    }
  }
}

