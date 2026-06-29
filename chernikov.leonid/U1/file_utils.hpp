#ifndef CHERNIKOV_FILE_UTILS_HPP
#define CHERNIKOV_FILE_UTILS_HPP

#include <string>
#include <iosfwd>

namespace chernikov
{

  struct FileConfig
  {
    std::string inputFile;
    std::string outputFile;
    bool useStdin;
    bool useStdout;
  };

  bool parseArguments(int argc, char *argv[], FileConfig &config, std::ostream &errorOutput);

  bool openFiles(
      const FileConfig &config,
      std::ifstream &inputFile,
      std::ofstream &outputFile,
      std::istream *&input,
      std::ostream *&output);

  void closeFiles(std::ifstream &inputFile, std::ofstream &outputFile);

}

#endif
