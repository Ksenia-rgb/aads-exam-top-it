#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <utils.hpp>

namespace kondrat
{
  struct Person
  {
    size_t id;
    std::string info;
    bool described;
  };

  struct Meeting
  {
    size_t first;
    size_t second;
    size_t time;
  };

  template< class T >
  struct Storage
  {
    T * data;
    size_t size;
    size_t capacity;
  };

  using PersonStorage = Storage< Person >;
  using MeetingStorage = Storage< Meeting >;

  struct ProgramArgs
  {
    const char * input;
    const char * data;
  };

  bool parseArgs(int argc, char ** argv, ProgramArgs & args);
  template< class T >
  void initStorage(Storage< T > & storage);
  template< class T >
  void destroyStorage(Storage< T > & storage);
  template< class T >
  void reserve(Storage< T > & storage, size_t capacity);
  template< class T >
  void pushBack(Storage< T > & storage, const T & value);
}

bool kondrat::parseArgs(int argc, char ** argv, ProgramArgs & args)
{
  args.input = nullptr;
  args.data = nullptr;
  if (argc < 2 || argc > 3)
  {
    return false;
  }

  for (int i = 1; i < argc; ++i)
  {
    if (startsWith(argv[i], "in:"))
    {
      if (args.input != nullptr || argv[i][3] == '\0')
      {
        return false;
      }
      args.input = argv[i] + 3;
    }
    else if (startsWith(argv[i], "data:"))
    {
      if (args.data != nullptr || argv[i][5] == '\0')
      {
        return false;
      }
      args.data = argv[i] + 5;
    }
    else
    {
      return false;
    }
  }

  return args.data != nullptr;
}

template< class T >
void kondrat::initStorage(Storage< T > & storage)
{
  storage.data = nullptr;
  storage.size = 0;
  storage.capacity = 0;
}

template< class T >
void kondrat::destroyStorage(Storage< T > & storage)
{
  delete[] storage.data;
  initStorage(storage);
}

template< class T >
void kondrat::reserve(Storage< T > & storage, size_t capacity)
{
  if (capacity <= storage.capacity)
  {
    return;
  }

  T * newData = new T[capacity];
  try
  {
    for (size_t i = 0; i < storage.size; ++i)
    {
      newData[i] = storage.data[i];
    }
  }
  catch (...)
  {
    delete[] newData;
    throw;
  }

  delete[] storage.data;
  storage.data = newData;
  storage.capacity = capacity;
}

template< class T >
void kondrat::pushBack(Storage< T > & storage, const T & value)
{
  if (storage.size == storage.capacity)
  {
    reserve(storage, nextCapacity(storage.capacity));
  }

  storage.data[storage.size] = value;
  ++storage.size;
}

int main(int argc, char ** argv)
{}
