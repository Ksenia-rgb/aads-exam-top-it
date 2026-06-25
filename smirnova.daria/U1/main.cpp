#include <iostream>
#include <fstream>
#include <string>

#include "person.h"
#include "arguments.h"

int main(int argc, char* argv[]) {
    smirnova::Arguments args;

    if (!smirnova::parseArguments(argc, argv, args)) {
        std::cerr << "Invalid arguments\n";
        return 1;
    }

    std::ifstream inputFile;
    std::ofstream outputFile;

    std::istream* in = &std::cin;
    std::ostream* out = &std::cout;

    if (args.inputSet) {
        inputFile.open(args.inputFile.c_str());
        if (!inputFile.is_open()) {
            std::cerr << "Cannot open input file: " << args.inputFile << '\n';
            return 2;
        }
        in = &inputFile;
    }

    if (args.outputSet) {
        outputFile.open(args.outputFile.c_str());
        if (!outputFile.is_open()) {
            if (args.inputSet) {
                inputFile.close();
            }
            std::cerr << "Cannot open output file: " << args.outputFile << '\n';
            return 2;
        }
        out = &outputFile;
    }

    const size_t MAX_PERSONS = 1000;
    smirnova::Person persons[MAX_PERSONS];
    size_t count = 0;
    size_t ignored = 0;

    std::string line;
    while (std::getline(*in, line)) {
        if (line.empty()) {
            ++ignored;
            continue;
        }

        smirnova::Person person;
        if (!smirnova::parsePerson(line, person)) {
            ++ignored;
            continue;
        }

        if (smirnova::isDuplicate(persons, count, person)) {
            ++ignored;
            continue;
        }
        if (count >= MAX_PERSONS)
        {
            ++ignored;
            continue;
        }
        persons[count] = person;
        ++count;
    }

    for (size_t i = 0; i < count; ++i) {
        smirnova::printPerson(persons[i], *out);
    }

    std::cerr << count << ' ' << ignored << '\n';

    if (args.inputSet) {
        inputFile.close();
    }
    if (args.outputSet) {
        outputFile.close();
    }

    return 0;
}
