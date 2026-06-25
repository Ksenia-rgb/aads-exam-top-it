#include <fstream>
#include <iostream>
#include "logic.hpp"

int main(const int argc, char *argv[])
{
  const pozdnyakov::AppArgs args = pozdnyakov::parseArguments(argc, argv);
  
  pozdnyakov::DynamicArray< pozdnyakov::Person > persons;
  pozdnyakov::initArray(persons);

  pozdnyakov::ProcessStats stats;
  stats.successCount = 0;
  stats.ignoredCount = 0;

  pozdnyakov::destroyArray(persons);

  return 0;
}
