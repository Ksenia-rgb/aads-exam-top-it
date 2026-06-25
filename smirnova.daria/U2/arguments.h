#ifndef ARGUMENTS_H_
#define ARGUMENTS_H_

#include <string>

namespace smirnova {

    struct Arguments {
        std::string dataFile;
        std::string inFile;
    };

    bool parseArguments(int argc, char* argv[], Arguments& args);

}

#endif