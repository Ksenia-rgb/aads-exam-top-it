#ifndef COMMAND_MANAGER
#define COMMAND_MANAGER
#include <iostream>
#include <sstream>

#include "../common/htable.hpp"


namespace volkovich {
  class CommandManager {
    using Handler = void (CommandManager::*)(std::istream&, std::ostream&);
    HashTable< std::string, Handler, SipHash, std::equal_to< std::string > > commands_;

    void handleAnons(std::istream&, std::ostream&);
    void handleDeanon(std::istream&, std::ostream&);
    void handleRedesc(std::istream&, std::ostream&);
    void handleDesc(std::istream&, std::ostream&);
    void handleMeets(std::istream&, std::ostream&);
    void handleCommons(std::istream&, std::ostream&);
    void handleLess(std::istream&, std::ostream&);
    void handleGreater(std::istream&, std::ostream&);
    void handleOutPersons(std::istream&, std::ostream&);

    using GraphTable =
        volkovich::Graphs< std::string, volkovich::SipHash, std::equal_to< std::string > >;
    GraphTable& gr;

   public:
    CommandManager(GraphTable& gr);
    void readCommand(const std::string& command, std::ostream& output);
  };
}
#endif
