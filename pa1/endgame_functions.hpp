#ifndef ENDGAME_FUNCTIONS_HPP
#define ENDGAME_FUNCTIONS_HPP
#include "ingame_functions.hpp"
#include "root.hpp"

bool openFileOut(std::fstream &, std::string);
// void exitFunction(Player &, List<Node<Data>> &);
void writeToCmdFile(List<Node<Data>> &list);
void writeToProfiles(Player &pl);
#endif