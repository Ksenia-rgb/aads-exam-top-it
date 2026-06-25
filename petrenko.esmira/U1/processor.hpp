#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <iostream>
#include <fstream>
#include <string>

namespace petrenko {

struct Person {
  size_t id;
  std::string info;
};

struct Node {
  Person data;
  Node* next;
};

class DataProcessor {
private:
  Node* head;
  Node* tail;
  size_t validCount;
  size_t ignoredCount;

  bool isDuplicate(size_t id) {
    Node* current = head;
    while (current) {
      if (current->data.id == id) {
        return true;
      }
      current = current->next;
    }
    return false;
  }

  void addRecord(const Person& person) {
    Node* newNode = new Node{person, nullptr};
    if (!head) {
      head = newNode;
      tail = newNode;
    } else {
      tail->next = newNode;
      tail = newNode;
    }
    validCount++;
  }

public:
  DataProcessor() : head(nullptr), tail(nullptr), validCount(0), ignoredCount(0) {}

  ~DataProcessor() {
    Node* current = head;
    while (current) {
      Node* next = current->next;
      delete current;
      current = next;
    }
  }
};

}

#endif
