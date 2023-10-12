#include "ingame_functions.hpp"

// **************************************************************************************
// <Player> CLASS MEMBER FUNCTIONS:
// **************************************************************************************
// SETTER FUNCTION:
void Player::setPlayerInfo() {
  std::string name;
  std::cout << "HELLO! WHAT IS YOUR NAME? ";

  std::cin >> name;
  pName = name;
}
void Player::hardRESETpoints() { points = 0; }
void Player::givePlayerPoint() { points += 1; }
void Player::takePlayerPoint() { points -= 1; }
// GETTER FUNCTION:
std::string Player::getPlayerName() const { return pName; }
int Player::getPlayerPts() const { return points; }

// **************************************************************************************
// GAME OPTIONS.
// **************************************************************************************
// OPTION #1: PRINT GAME RULES
// **************************************************************************************
void printGameRules() {
  std::cout << "\tLet's learn some Linux commands today!\n\n";
  std::cout << "\tGAME RULES:\n";
  std::cout
      << "\t------------------------------------------------------------\n";
  std::cout
      << "\tYou will get to learn a few Linux commands by matching their\n"
         "\tnames with the correct description of their functionality.\n\n";
  std::cout
      << "\tA command will be shown along with three other descriptions,\n"
         "\tbut only one of those is correct! You must choose the correct\n"
         "\tdescription!\n\n";
  std::cout << "\tThis will repeat until you have gone through the number of\n"
               "\tcommands you previously selected.\n\n";
  std::cout
      << "\tEach time you make a correct match, you will earn one point!\n\n";
  std::cout << "\tHowever, be careful because you also lose one point if you\n"
            << "\tmake an incorrect match! It's possible to have negative "
               "points!\n\n";
  std::cout << "\tHave fun learning!" << std::endl;
}

// OPTION #2: PLAY GAME
// **************************************************************************************
void playGame(std::vector<Data> &buffVec, List<Node<Data>> &loadedList,
              Player &activeP) {
  // Define the upper bound for the largest possible position# to be generated:
  const int upperBound = loadedList.getListSize();
  // Other local scope parameters:
  int rNum, numCmdsThisGame = 0;
  bool isMatched;

  // ASK PLAYER TO ENTER A NUMBER OF COMMANDS TO MATCH:
  while (numCmdsThisGame < 5 || numCmdsThisGame > upperBound) {
    std::cout << "\tPlease enter the total number of commands to play: ";
    std::cin >> numCmdsThisGame;
  }

  // // DEFINE DATA STRUCTURE FOR THIS GAME INSTANCE:
  std::vector<int> gLength;
  gLength.resize(numCmdsThisGame);

  // GENERATE A TABLE OF QUESTIONS:
  for (int itr = 0; itr < numCmdsThisGame; ++itr) {
    rNum = rand() % upperBound;
    gLength[itr] = rNum;
  }

  // Check for and replace duplicates:
  for (int itr = 0; itr < numCmdsThisGame; ++itr) {
    do {
      isMatched = false;
      rNum = rand() % upperBound;
      for (int i = 0; i < itr; ++i) {
        if (gLength[i] == rNum) {
          isMatched = true;
          break;
        }
      }
    } while (isMatched);
    gLength[itr] = rNum;
  }

  // START GAME:
  Data *testCmdPtr = nullptr;
  testCmdPtr = &buffVec[0];
  std::cout
      << "\n\n*************************************************************\n";
  std::cout << "BELOW IS A TEST PRINT:\n\n";
  std::cout << testCmdPtr->getCmdName() << "\t" << testCmdPtr->getCmdInfo()
            << "\n"
            << std::endl;
  std::cout << "END OF TEST PRINT.";
  std::cout << "*reference: ingame_functions, line 90-100\n";
  std::cout
      << "\n*************************************************************\n\n";
  std::cout << std::endl;

  /*
    A MATCH'S SEQUENCE:
      1. Take one string (in order) from the gLength vector and supply it to
    MatchInstance.cmd
      - Save gLength[i] into prevQ.
      2. Supply the randRow to choiceTable's pos#0.
      3. Supply the description into the choiceTable's pos that is equal to
    randRow, set that pos to 1.
      4. Loop, for range(1, 3):
        - if encounter 1, continue.
        - generate a random number such that it is different from prevQ.
      5. print command at pos equivalent to choiceTable[0], as well as all 3
    descriptions.
      6. ask player to choose among 1,2,3.
      7. check if the number at location choiceTable[i] = 1, it's a match: give
    +1 pt. otherwise it's a miss: give -1 pt.
  */

  for (int itr = 0; itr < numCmdsThisGame; ++itr) {
    // Define a local-scope Match Instance:
    MatchInstance *temp = nullptr;
    temp = new MatchInstance;

    int uInput, row, prevQ = gLength[itr];
    // 1.
    temp->cmdTable[0] = buffVec[prevQ].getCmdName();
    // 2.
    row = rand() % 3 + 1;
    // 3.
    temp->choiceTable[row] = prevQ;
    // 4.
    int x = prevQ;
    for (int k = 1; k < 4; ++k) {
      x = rand() % upperBound;
      if (temp->choiceTable[k] == prevQ) {
        while (x == prevQ) {
          x = rand() % upperBound;
        }
      } else {
        temp->choiceTable[k] = x;
        temp->cmdTable[k] = buffVec[x].getCmdName();
      }
    }
    // 5.
    std::cout << buffVec[prevQ].getCmdName() << ":";
    for (int k = 1; k <= 3; ++k) {
      if (temp->choiceTable[k] == 1) temp->choiceTable[k] = prevQ;
      std::cout << "\t" << k << ". "
                << buffVec[temp->choiceTable[k]].getCmdInfo() << "\n";
    }
    std::cout << "WHAT WILL YOU CHOOSE: ";
    std::cin >> uInput;
    // 6.
    if (uInput == row) {
      std::cout << "CORRECT! YOU EARN 1 POINT!\n" << std::endl;
      activeP.givePlayerPoint();
    } else {
      std::cout << "INCORRECT! YOU LOSE 1 POINT!\n" << std::endl;
      activeP.takePlayerPoint();
    }
    delete temp;
  }

  std::cout << "YOUR TOTAL POINTS: " << activeP.getPlayerPts() << std::endl;
}

// OPTION #3: LOAD PREVIOUS GAME
// **************************************************************************************
void loadPreviousGame(std::vector<Data> &buffVec, List<Node<Data>> &loadedList,
                      Player &activeP) {
  playGame(buffVec, loadedList, activeP);
}

// OPTION #4: ADD COMMAND
// **************************************************************************************
void addCommand(List<Node<Data>> &list, std::vector<Data> &buffVec) {
  std::string uInput;
  Data *temp = nullptr;
  temp = new Data;

  std::cout << "ADDING NEW COMMAND: (DO NOT PRESS 'ENTER' BEFORE YOU FINISH "
               "ADDING EACH ENTRY!)\n";
  std::cout << "Please enter the command's name: ";
  std::cin >> uInput;
  temp->setCmdName(uInput);

  std::cout << "Please enter a description for the command: ";
  std::cin >> uInput;
  temp->setCmdInfo(uInput);

  Node<Data> *newNode = nullptr;
  newNode = new Node<Data>;
  newNode->unitNodeData = temp;

  list.appendNode(*newNode);
  buffVec.push_back(*temp);
}

// OPTION #5: REMOVE COMMAND
// **************************************************************************************
void removeCommand(List<Node<Data>> &list /*, std::vector<Data> &buffVec*/) {
  std::string uInput;
  Data *temp = nullptr;
  temp = new Data;

  std::cout << "REMOVING COMMAND:";
  std::cout << "Please enter the name of the command you want to remove: ";
  std::cin >> uInput;
  temp->setCmdName(uInput);

  Node<Data> *toBeDeleted = nullptr;
  toBeDeleted = new Node<Data>;
  toBeDeleted->unitNodeData = temp;

  list.deleteNode(*toBeDeleted);
}