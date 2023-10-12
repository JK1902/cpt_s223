#ifndef GAME_OPTIONS_HPP
#define GAME_OPTIONS_HPP
#include "root.hpp"

// **************************************************************************************
// DEFINE A CONCRETE CLASS FOR A PLAYER'S GAME RECORD:
// **************************************************************************************
class Player {
 protected:
  std::string pName;
  int points;

 public:
  // CONSTRUCTOR: (IMPLICIT DESTRUCTOR)
  Player() {
    pName = "";
    points = 0;
  }
  void hardRESETpoints();
  void setPlayerInfo();
  void givePlayerPoint();
  void takePlayerPoint();
  std::string getPlayerName() const;
  int getPlayerPts() const;
};

// **************************************************************************************
// DEFINE A CONCRETE CLASS FOR A MATCHING INSTANCE DURING GAME:
// **************************************************************************************
class MatchInstance {
 public:
  std::vector<std::string> cmdTable;
  std::vector<int> choiceTable;

  MatchInstance() {
    cmdTable = {"", "", "", ""};
    choiceTable = {0, 0, 0, 0};
  }
};

// **************************************************************************************
// MENU OPTION FUNCTIONS:
// **************************************************************************************
void printGameRules();
void playGame(std::vector<Data> &, List<Node<Data>> &, Player &);
void loadPreviousGame(std::vector<Data> &, List<Node<Data>> &, Player &);
void addCommand(List<Node<Data>> &, std::vector<Data> &);
void removeCommand(List<Node<Data>> &/*, std::vector<Data> &*/);

// **************************************************************************************
// OTHER USEFUL FUNCTIONS:
// **************************************************************************************
void generateRandomQuiz();
#endif