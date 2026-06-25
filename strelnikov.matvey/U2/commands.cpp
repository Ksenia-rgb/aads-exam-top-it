#include "commands.hpp"
#include <fstream>

namespace strelnikov
{

  struct MeetingOut
  {
    size_t partner_id;
    size_t duration;
  };

  void swap_meetings(MeetingOut &a, MeetingOut &b)
  {
    MeetingOut temp = a;
    a = b;
    b = temp;
  }

  void quick_sort_meetings(MeetingOut *arr, int low, int high)
  {
    if (low < high) {
      MeetingOut pivot = arr[high];
      int i = low - 1;
      for (int j = low; j < high; ++j) {
        if (arr[j].partner_id < pivot.partner_id
            || (arr[j].partner_id == pivot.partner_id && arr[j].duration < pivot.duration)) {
          ++i;
          swap_meetings(arr[i], arr[j]);
        }
      }
      swap_meetings(arr[i + 1], arr[high]);
      int pi = i + 1;
      quick_sort_meetings(arr, low, pi - 1);
      quick_sort_meetings(arr, pi + 1, high);
    }
  }

  void swap_size_t(size_t &a, size_t &b)
  {
    size_t temp = a;
    a = b;
    b = temp;
  }

  void quick_sort_size_t(size_t *arr, int low, int high)
  {
    if (low < high) {
      size_t pivot = arr[high];
      int i = low - 1;
      for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
          ++i;
          swap_size_t(arr[i], arr[j]);
        }
      }
      swap_size_t(arr[i + 1], arr[high]);
      int pi = i + 1;
      quick_sort_size_t(arr, low, pi - 1);
      quick_sort_size_t(arr, pi + 1, high);
    }
  }

  size_t count_meetings(Meeting *head)
  {
    size_t count = 0;
    while (head != nullptr) {
      ++count;
      head = head->next;
    }
    return count;
  }

  bool cmd_anons(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t count = 0;
    for (size_t i = 0; i < ctx.persons.capacity; ++i) {
      HashNode< size_t, PersonData > *current = ctx.persons.buckets[i];
      while (current != nullptr) {
        if (current->value.info.empty())
          ++count;
        current = current->next;
      }
    }

    if (count == 0)
      return true;

    size_t *anons = new size_t[count];
    size_t idx = 0;

    for (size_t i = 0; i < ctx.persons.capacity; ++i) {
      HashNode< size_t, PersonData > *current = ctx.persons.buckets[i];
      while (current != nullptr) {
        if (current->value.info.empty()) {
          anons[idx++] = current->key;
        }
        current = current->next;
      }
    }

    quick_sort_size_t(anons, 0, count - 1);

    for (size_t i = 0; i < count; ++i) {
      out << anons[i] << "\n";
    }

    delete[] anons;
    return true;
  }

  bool cmd_deanon(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t anon_id, id;
    if (!(in >> anon_id >> id))
      return false;

    if (anon_id == id)
      return false;

    PersonData *p_anon = context_find_person(ctx, anon_id);
    PersonData *p_id = context_find_person(ctx, id);

    if (p_anon == nullptr || p_id == nullptr)
      return false;
    if (!p_anon->info.empty() || p_id->info.empty())
      return false;

    if (p_anon->meetings_head != nullptr) {
      Meeting *tail = p_anon->meetings_head;
      while (tail->next != nullptr) {
        tail = tail->next;
      }
      tail->next = p_id->meetings_head;
      p_id->meetings_head = p_anon->meetings_head;
      p_anon->meetings_head = nullptr;
    }

    Meeting **curr = &p_id->meetings_head;
    while (*curr != nullptr) {
      if ((*curr)->partner_id == id) {
        Meeting *to_delete = *curr;
        *curr = to_delete->next;
        delete to_delete;
      } else {
        curr = &(*curr)->next;
      }
    }

    context_remove_person(ctx, anon_id);
    return true;
  }

  bool cmd_desc(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t id;
    if (!(in >> id))
      return false;

    PersonData *p = context_find_person(ctx, id);
    if (p == nullptr)
      return false;

    if (p->info.empty()) {
      out << "<ANON>\n";
    } else {
      out << p->info << "\n";
    }
    return true;
  }

  bool cmd_redesc(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t id;
    if (!(in >> id))
      return false;

    in >> std::ws;
    if (in.peek() != '"')
      return false;
    in.get();

    std::string desc;
    std::getline(in, desc, '"');

    if (in.fail() || in.peek() != '"')
      return false;
    in.get();

    PersonData *p = context_find_person(ctx, id);
    if (p == nullptr)
      return false;

    p->info = desc;
    return true;
  }

  bool cmd_meets(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t id;
    if (!(in >> id))
      return false;

    PersonData *p = context_find_person(ctx, id);
    if (p == nullptr)
      return false;

    size_t count = count_meetings(p->meetings_head);
    if (count == 0)
      return true;

    MeetingOut *arr = new MeetingOut[count];
    Meeting *m = p->meetings_head;
    for (size_t i = 0; i < count; ++i) {
      arr[i].partner_id = m->partner_id;
      arr[i].duration = m->duration;
      m = m->next;
    }

    quick_sort_meetings(arr, 0, count - 1);

    for (size_t i = 0; i < count; ++i) {
      out << arr[i].partner_id << " " << arr[i].duration << "\n";
    }

    delete[] arr;
    return true;
  }

  bool cmd_commons(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t id1, id2;
    if (!(in >> id1 >> id2))
      return false;

    PersonData *p1 = context_find_person(ctx, id1);
    PersonData *p2 = context_find_person(ctx, id2);
    if (p1 == nullptr || p2 == nullptr)
      return false;

    size_t count1 = count_meetings(p1->meetings_head);
    size_t count2 = count_meetings(p2->meetings_head);

    if (count1 == 0 || count2 == 0)
      return true;

    size_t *arr1 = new size_t[count1];
    size_t *arr2 = new size_t[count2];

    Meeting *m1 = p1->meetings_head;
    for (size_t i = 0; i < count1; ++i) {
      arr1[i] = m1->partner_id;
      m1 = m1->next;
    }

    Meeting *m2 = p2->meetings_head;
    for (size_t i = 0; i < count2; ++i) {
      arr2[i] = m2->partner_id;
      m2 = m2->next;
    }

    quick_sort_size_t(arr1, 0, count1 - 1);
    quick_sort_size_t(arr2, 0, count2 - 1);

    size_t i = 0, j = 0;
    size_t last_printed = 0;
    bool first_print = true;

    while (i < count1 && j < count2) {
      if (arr1[i] < arr2[j]) {
        ++i;
      } else if (arr1[i] > arr2[j]) {
        ++j;
      } else {
        if (first_print || arr1[i] != last_printed) {
          out << arr1[i] << "\n";
          last_printed = arr1[i];
          first_print = false;
        }
        ++i;
        ++j;
      }
    }

    delete[] arr1;
    delete[] arr2;
    return true;
  }

  bool cmd_less(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t time, id;
    if (!(in >> time >> id))
      return false;

    PersonData *p = context_find_person(ctx, id);
    if (p == nullptr)
      return false;

    size_t count = 0;
    Meeting *m = p->meetings_head;
    while (m != nullptr) {
      if (m->duration < time)
        ++count;
      m = m->next;
    }

    if (count == 0)
      return true;

    MeetingOut *arr = new MeetingOut[count];
    m = p->meetings_head;
    size_t idx = 0;
    while (m != nullptr) {
      if (m->duration < time) {
        arr[idx].partner_id = m->partner_id;
        arr[idx].duration = m->duration;
        ++idx;
      }
      m = m->next;
    }

    quick_sort_meetings(arr, 0, count - 1);

    for (size_t i = 0; i < count; ++i) {
      out << arr[i].partner_id << " " << arr[i].duration << "\n";
    }

    delete[] arr;
    return true;
  }

  bool cmd_greater(std::istream &in, std::ostream &out, Context &ctx)
  {
    size_t time, id;
    if (!(in >> time >> id))
      return false;

    PersonData *p = context_find_person(ctx, id);
    if (p == nullptr)
      return false;

    size_t count = 0;
    Meeting *m = p->meetings_head;
    while (m != nullptr) {
      if (m->duration > time)
        ++count;
      m = m->next;
    }

    if (count == 0)
      return true;

    MeetingOut *arr = new MeetingOut[count];
    m = p->meetings_head;
    size_t idx = 0;
    while (m != nullptr) {
      if (m->duration > time) {
        arr[idx].partner_id = m->partner_id;
        arr[idx].duration = m->duration;
        ++idx;
      }
      m = m->next;
    }

    quick_sort_meetings(arr, 0, count - 1);

    for (size_t i = 0; i < count; ++i) {
      out << arr[i].partner_id << " " << arr[i].duration << "\n";
    }

    delete[] arr;
    return true;
  }

  bool cmd_out_persons(std::istream &in, std::ostream &out, Context &ctx)
  {
    std::string filename;
    if (!(in >> filename))
      return false;

    std::ofstream file(filename);
    if (!file.is_open())
      return false;

    size_t count = 0;
    for (size_t i = 0; i < ctx.persons.capacity; ++i) {
      HashNode< size_t, PersonData > *current = ctx.persons.buckets[i];
      while (current != nullptr) {
        if (!current->value.info.empty())
          ++count;
        current = current->next;
      }
    }

    if (count > 0) {
      size_t *ids = new size_t[count];
      size_t idx = 0;

      for (size_t i = 0; i < ctx.persons.capacity; ++i) {
        HashNode< size_t, PersonData > *current = ctx.persons.buckets[i];
        while (current != nullptr) {
          if (!current->value.info.empty()) {
            ids[idx++] = current->key;
          }
          current = current->next;
        }
      }

      quick_sort_size_t(ids, 0, count - 1);

      for (size_t i = 0; i < count; ++i) {
        PersonData *p = context_find_person(ctx, ids[i]);
        file << ids[i] << " " << p->info << "\n";
      }

      delete[] ids;
    }

    file.close();
    return true;
  }

}
