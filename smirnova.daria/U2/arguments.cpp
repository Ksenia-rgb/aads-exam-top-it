#include "arguments.h"

namespace smirnova {

    bool parseArguments(int argc, char* argv[], Arguments& args) {
        bool hasData = false;

        for (int i = 1; i < argc; ++i) {
            std::string a = argv[i];

            if (a.find("data:") == 0) {
                args.dataFile = a.substr(5);
                hasData = true;
            }
            else if (a.find("in:") == 0) {
                args.inFile = a.substr(3);
            }
            else {
                return false;
            }
        }

        return hasData;
    }

}