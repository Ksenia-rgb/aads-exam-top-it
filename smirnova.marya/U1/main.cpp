#include <iostream>
#include <string>
#include "input_handler.hpp"
#include "person.hpp"
#include "parse_line.hpp"
#include "vector.hpp"

int main(int argc, char* argv[]) {
    if (argc > 2) {
        std::cerr << "Invalid arguments." << std::endl;
        return 1;
    }

    std::string inputFileName;
    std::string outputFileName;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.rfind("in:", 0) == 0) {
            inputFileName = arg.substr(3);
        } else if (arg.rfind("out:", 0) == 0) {
            outputFileName = arg.substr(4);
        }
    }

    smirnova::InputHandler inputHandler(inputFileName);
    smirnova::Vector<smirnova::Person> persons;
    size_t validEntries = 0;
    size_t ignoredEntries = 0;

    smirnova::processInput(inputHandler.getInputStream(), persons, validEntries, ignoredEntries);

    smirnova::printPersons(persons, std::cout);

    std::cerr << validEntries << " " << ignoredEntries << std::endl;

    return 0;
}

