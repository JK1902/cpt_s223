#ifndef DATA_HPP
#define DATA_HPP
#include "EventManager.hpp"
#include "Test.hpp"

bool openFileOut(std::fstream &, std::string);
// void exitFunction(Player &, List<Node<Data>> &);
void writeToCmdFile(List<Node<Data>> &list);
void writeToProfiles(Player &pl);
#endif