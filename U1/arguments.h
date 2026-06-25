#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <string>

namespace smirnova {

    struct Arguments {
        std::string inputFile;
        std::string outputFile;
        bool inputSet;
        bool outputSet;
    };

    bool parseArguments(int argc, char* argv[], Arguments& args);

}  // namespace smirnova

#endif  // ARGUMENTS_H_