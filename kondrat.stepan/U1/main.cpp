#include <cstddef>
#include <string>

namespace kondrat
{
  struct Person
  {
    size_t id;
    std::string info;
  };

  struct PersonStorage
  {
    Person * data;
    size_t size;
    size_t capacity;
  };

  struct ProgramArgs
  {
    const char * inputName;
    const char * outputName;
  };
}

int main()
{}
