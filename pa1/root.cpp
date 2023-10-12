#include "root.hpp"

// **************************************************************************************
// <Data> CLASS MEMBER FUNCTIONS:
// **************************************************************************************
// SETTER FUNCTION:
void Data::setCmdName(std::string &in) { cmdName = in; }
void Data::setCmdInfo(std::string &in) { cmdInfo = in; }
// GETTER FUNCTION:
std::string Data::getCmdName() const { return cmdName; }
std::string Data::getCmdInfo() const { return cmdInfo; }
// OPERATOR = OVERLOADING FOR ASSIGNING A DATA UNIT:
void Data::operator=(const Data &right) {
  cmdName = right.getCmdName();
  cmdInfo = right.getCmdInfo();
}
// OPERATOR == OVERLOADING FOR COMPARING TWO DATA UNITS:
bool Data::operator==(Data &right) const {
  if (cmdName.compare(right.cmdName) != 0) {
    return false;
  } else
    return true;
}

// **************************************************************************************
// FILE OPERATION: CHECK WHETHER THE FILE IS OPENED SUCCESSFULLY FOR READING.
// **************************************************************************************
bool openFileIn(std::fstream &file, std::string fName) {
  file.open(fName, std::ios::in);

  if (file.fail())
    return false;
  else
    return true;
}

// **************************************************************************************
// BUFFER VECTOR: POPULATE BUFFER VECTOR WITH DATA FROM CSV FILE.
// **************************************************************************************
// WRAPPER FUNCTION: OPEN FILE AND ENCAPSULATE THE CHILD-FUNCTION BELOW.
void populateBufferVector(std::vector<Data> &bufferVec) {
  std::fstream dataFile;

  if (openFileIn(dataFile, "data/commands.csv")) {
    std::cout << "File opened successfully for READING." << std::endl;
    cpyContentToBuffer(dataFile, bufferVec);
    dataFile.close();
    std::cout << "Content copied to buffer." << std::endl;
  }

  else
    std::cout << "File open error!" << std::endl;
}

// CHILD-FUNCTION: COPY CONTENT OF OPENED FILE INTO TO A UNIT OF TEMP DATA.
void cpyContentToBuffer(std::fstream &file, std::vector<Data> &cmdVec) {
  std::string input;
  std::string tok = "";

  // create temp buffer with size of one Data unit:
  Data *tempData = nullptr;
  tempData = new Data;

  std::string delimiter01 = ", \"";
  std::string delimiter02 = ".\"";

  // continue to grab line and copy data until the end of the file:
  while (!file.eof()) {
    // grab the command's name:
    std::getline(file, input, '\n');
    tok = input.substr(0, input.find(delimiter01));
    tempData->setCmdName(tok);
    // trim the name from the input string:
    tok += delimiter01;
    input.erase(0, tok.size());
    tok = "";
    // grab the description:
    tok = input.substr(0, input.find_last_of(delimiter02));
    tempData->setCmdInfo(tok);

    cmdVec.push_back(*tempData);
  }

  delete tempData;
}

// **************************************************************************************
// LIST: POPULATE LIST WITH DATA FROM BUFFER VECTOR.
// **************************************************************************************
void populateList(List<Node<Data>> &ourList, std::vector<Data> &bufferVec) {
  for (int i = 0; i < int(bufferVec.size()); ++i) {
    Data *tempDat = nullptr;
    tempDat = new Data();
    *tempDat = bufferVec[i];

    Node<Data> *tempNode = nullptr;
    tempNode = new Node<Data>;
    tempNode->unitNodeData = tempDat;

    ourList.appendNode(*tempNode);
  }
}

// **************************************************************************************
// GAME MENU FUNCTIONS:
// **************************************************************************************
// PRINT MENU OPTIONS:
// **************************************************************************************
void printMenu() {
  std::cout << std::endl;
  std::cout << "MAIN MENU. PLEASE SELECT AN OPTION: ";
  std::cout << "1 >> READ GAME RULES" << std::endl;
  std::cout << "                                    ";
  std::cout << "2 >> PLAY GAME" << std::endl;
  std::cout << "                                    ";
  std::cout << "3 >> LOAD PREVIOUS GAME" << std::endl;
  std::cout << "                                    ";
  std::cout << "4 >> ADD COMMAND" << std::endl;
  std::cout << "                                    ";
  std::cout << "5 >> REMOVE COMMAND" << std::endl;
  std::cout << "                                    ";
  std::cout << "6 >> EXIT" << std::endl << std::endl;
}
// ENTER A MENU OPTION: (will check for input error.)
// **************************************************************************************
int getMenuOption() {
  char uInput[1];

  while (!(uInput[0] > 48 && uInput[0] < 55)) {
    uInput[0] = 0;
    std::cout << "CHOOSE YOUR OPTION: ";
    std::cin >> uInput[0];
    if (!(uInput[0] > 48 && uInput[0] < 55)) {
      std::cout << "INVALID INPUT. PLEASE ENTER THE CORRECT NUMBER. ";
      continue;
    }
  }

  return static_cast<int>(uInput[0]) - 48;
}
