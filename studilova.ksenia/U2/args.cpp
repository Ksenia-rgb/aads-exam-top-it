#include "args.hpp"

namespace
{
  bool hasPrefix(const std::string &text, const std::string &prefix)
  {
    if (text.size() < prefix.size())
    {
      return false;
    }

    for (std::size_t i = 0; i < prefix.size(); ++i)
    {
      if (text[i] != prefix[i])
      {
        return false;
      }
    }

    return true;
  }

  std::string removePrefix(const std::string &text, const std::string &prefix)
  {
    std::string result;

    for (std::size_t i = prefix.size(); i < text.size(); ++i)
    {
      result += text[i];
    }

    return result;
  }
}
