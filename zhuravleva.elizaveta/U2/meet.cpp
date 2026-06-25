#include "meet.hpp"

bool zhuravleva::parseArgs(int, char *[], Args &)
{
  return false;
}

bool zhuravleva::readMeet(const std::string &, Meet &)
{
  return false;
}

void zhuravleva::readMeets(std::istream &, DynamicArray< Meet > &)
{}

void zhuravleva::addAnonymous(
    DynamicArray< Person > &,
    const DynamicArray< Meet > &)
{}
