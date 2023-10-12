#include "endgame_functions.hpp"

// **************************************************************************************
// FILE OPERATION: CHECK WHETHER THE FILE IS OPENED SUCCESSFULLY FOR WRITING.
// **************************************************************************************
bool openFileOut(std::fstream &file, std::string fName) {
  file.open(fName, std::ios::out);

  if (file.fail())
    return false;
  else
    return true;
}

// OPTION #6: SAVE GAME PROFILE AND EXIT PROGRAM
// **************************************************************************************
// void exitFunction(Player &activeP, List<Node<Data>> &list) {
//   writeToCmdFile(list);
//   writeToProfiles(activeP);
// }

void writeToCmdFile(List<Node<Data>> &list) {
  // Declare a file stream to update the csv:
  std::fstream updateCmdFile;
  updateCmdFile.open("data/commands.csv", std::ios::out);
  // Check if file opened succesfully:
  if (updateCmdFile.fail()) {
    perror("FAILED TO OPEN OUTPUT DATABASE.");
    return;
  }

  // Declare a pointer to traverse through the list:
  Node<Data> *nodePtr;

  // grab the list's head:
  nodePtr = list.getListHead();

  std::string nameTok;
  std::string infoTok;
  while (nodePtr != nullptr) {
    // Declare a dummy data unit as medium between list and output file:
    Data *thisNodeData;
    thisNodeData = nodePtr->unitNodeData;
    nameTok = thisNodeData->getCmdName();
    infoTok = thisNodeData->getCmdInfo();

    updateCmdFile << nameTok << ", \"" << infoTok << "\"" << std::endl;
    nodePtr = nodePtr->next;
  }

  updateCmdFile.close();
}

void writeToProfiles(Player &pl) {
  std::fstream proFile;
  std::string tokName = pl.getPlayerName();
  int tokPts = pl.getPlayerPts();

  if (openFileOut(proFile, "data/profiles.csv"))
    std::cout << "File opened successfully for WRITING." << std::endl;
  else
    std::cout << "ERROR. Did not open file successfully." << std::endl;

  proFile << "\"" << tokName << "\""
          << ", " << tokPts << std::endl;

  proFile.close();
}