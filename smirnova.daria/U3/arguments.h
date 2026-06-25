#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <string>
#include <vector>

namespace smirnova {

    struct Arguments {
        std::vector<std::string> dataFiles;
        std::string inFile;
    };

    bool parseArguments(int argc, char* argv[], Arguments& args);

}

#endif  // ARGUMENTS_H_