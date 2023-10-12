#ifndef ROOT_H
#define ROOT_H
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "template_classes.hpp"

// **************************************************************************************
// DEFINE A CONCRETE CLASS TO HOLD EACH COMMAND'S DATA (name, "description"):
// **************************************************************************************
class Data {
 protected:
  std::string cmdName;
  std::string cmdInfo;

 public:
  // CONSTRUCTOR: (IMPLICIT DESTRUCTOR)
  Data() { cmdName = cmdInfo = ""; }

  // SETTER & GETTER FUNCTIONS:
  void setCmdName(std::string &);
  void setCmdInfo(std::string &);
  std::string getCmdName() const;
  std::string getCmdInfo() const;

  // OPERATOR = OVERLOADING FOR ASSIGNING A DATA UNIT:
  void operator=(const Data &);
  // OPERATOR == OVERLOADING FOR COMPARING TWO DATA UNITS:
  bool operator==(Data &) const;
};

// **************************************************************************************
// OTHER PREGAME FUNCTIONS:
// **************************************************************************************
bool openFileIn(std::fstream &, std::string);
void populateBufferVector(std::vector<Data> &);
void cpyContentToBuffer(std::fstream &, std::vector<Data> &);
void populateList(List<Node<Data>> &, std::vector<Data> &);

// **************************************************************************************
// MENU FUNCTIONS:
// **************************************************************************************
void printMenu();
int getMenuOption();
#endif
