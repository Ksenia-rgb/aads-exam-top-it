#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "structs.hpp"

namespace donkeev
{
  void handleAnons(const donkeev::CommandList& args);
  void handleDeanon(const donkeev::CommandList& args);
  void handleRedesc(const donkeev::CommandList& args);
  void handleDesc(const donkeev::CommandList& args);
  void handleMeets(const donkeev::CommandList& args);
  void handleCommons(const donkeev::CommandList& args);
  void handleLess(const donkeev::CommandList& args);
  void handleGreater(const donkeev::CommandList& args);
  void handleOutPersons(const donkeev::CommandList& args);
}
#endif
