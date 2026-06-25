#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include "../U1/person.hpp"
#include "hashtable.hpp"

namespace strelnikov
{

  struct Meeting
  {
    size_t partner_id;
    size_t duration;
    Meeting *next;
  };

  struct PersonData
  {
    std::string info;
    Meeting *meetings_head;
  };

  struct Context
  {
    HashTable< size_t, PersonData > persons;
  };

  void context_init(Context &ctx)
  {
    hash_init(ctx.persons, 1024);
  }

  void context_destroy(Context &ctx)
  {
    for (size_t i = 0; i < ctx.persons.capacity; ++i) {
      HashNode< size_t, PersonData > *current = ctx.persons.buckets[i];
      while (current != nullptr) {
        Meeting *m_curr = current->value.meetings_head;
        while (m_curr != nullptr) {
          Meeting *m_next = m_curr->next;
          delete m_curr;
          m_curr = m_next;
        }
        current = current->next;
      }
    }
    hash_destroy(ctx.persons);
  }

  PersonData *context_find_person(Context &ctx, size_t id)
  {
    return hash_find(ctx.persons, id, default_hash_size_t, default_eq_size_t);
  }

  void context_ensure_person(Context &ctx, size_t id)
  {
    if (context_find_person(ctx, id) == nullptr) {
      PersonData data;
      data.info = "";
      data.meetings_head = nullptr;
      hash_insert(ctx.persons, id, data, default_hash_size_t, default_eq_size_t);
    }
  }

  void context_add_meeting(Context &ctx, size_t id1, size_t id2, size_t duration)
  {
    if (id1 == id2)
      return;

    context_ensure_person(ctx, id1);
    context_ensure_person(ctx, id2);

    PersonData *p1 = context_find_person(ctx, id1);
    Meeting *m1 = new Meeting{id2, duration, p1->meetings_head};
    p1->meetings_head = m1;

    PersonData *p2 = context_find_person(ctx, id2);
    Meeting *m2 = new Meeting{id1, duration, p2->meetings_head};
    p2->meetings_head = m2;
  }

  void context_remove_person(Context &ctx, size_t id)
  {
    HashNode< size_t, PersonData > *node = hash_find_node(ctx.persons, id, default_hash_size_t, default_eq_size_t);
    if (node != nullptr) {
      Meeting *m = node->value.meetings_head;
      while (m != nullptr) {
        Meeting *next = m->next;
        delete m;
        m = next;
      }
      node->value.meetings_head = nullptr;
      hash_remove(ctx.persons, id, default_hash_size_t, default_eq_size_t);
    }
  }
}
#endif
