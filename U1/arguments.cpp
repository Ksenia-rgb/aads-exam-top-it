#include "arguments.h"

namespace smirnova
{
    bool parseArguments(
            int argc,
            char *argv[],
            Arguments &args
    )
    {
        args.inputSet = false;
        args.outputSet = false;
        args.inputFile.clear();
        args.outputFile.clear();

        if (argc > 3)
        {
            return false;
        }

        for (int i = 1; i < argc; ++i)
        {
            const std::string arg = argv[i];

            if (arg.find("in:") == 0)
            {
                if (args.inputSet)
                {
                    return false;
                }

                args.inputFile = arg.substr(3);

                if (args.inputFile.empty())
                {
                    return false;
                }

                args.inputSet = true;
            }
            else if (arg.find("out:") == 0)
            {
                if (args.outputSet)
                {
                    return false;
                }

                args.outputFile = arg.substr(4);

                if (args.outputFile.empty())
                {
                    return false;
                }

                args.outputSet = true;
            }
            else
            {
                return false;
            }
        }

        return true;
    }
}