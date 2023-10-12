//Khushi Panchal
// PA: 1 
// Class cpts223 .
// ADVANTAGES/DISADVANTAGES LINKED LIST:
/*ADV:Dynamic memory allocation: Linked lists can grow and shrink dynamically, as needed. This can be useful for applications where the amount of data is not known in advance, or where the data may change frequently.
Efficient insertion and deletion: Inserting and deleting elements from a linked list is relatively efficient, since it does not require shifting other elements around in memory.
Easy to implement: Linked lists are relatively easy to implement in most programming languages.*/
/*DIS: Inefficient access: Accessing an element in a linked list can be inefficient, since it requires traversing the list from the beginning until the desired element is found.
Extra memory usage: Linked lists require extra memory to store the pointers to the next and previous elements in the list.
Complex code: Linked list code can be more complex and difficult to maintain than code for other data structures, such as arrays.*/
// ADVANTAGES/DISADVANTAGES ARRAY:
/*ADV:Efficient access: Arrays provide efficient access to any element in the collection. This is because the elements of an array are stored in contiguous memory locations.
Fast search and sorting: Arrays are ideal for performing searches and sorts. This is because the elements of an array are stored in a specific order.
Memory efficiency: Arrays are a memory-efficient way of storing data. This is because the elements of an array are stored in contiguous memory locations.
Versatility: Arrays can be used to store a wide range of data types, including integers, floating-point numbers, characters, and even complex data structures such as objects and pointers.*/
/*DIS: Fixed size: Arrays have a fixed size. Once an array is created, its size cannot be changed. This can be a problem if the amount of data to be stored is not known in advance.
Inefficient insertion and deletion: Inserting and deleting elements from an array can be inefficient, since it may require shifting other elements around in memory.
Waste of memory: Arrays can waste memory if they are not filled to capacity. This is because the entire array must be allocated in memory, even if only a few of the elements are used.*/

#include "data.cpp"
#include "eventmanager.cpp"
#include "test.cpp"
int main() {
  // TEST CODE:
  std::string a = "Hello!";
  std::cout << std::endl << "THIS IS A TEST: " + a << std::endl << std::endl;

  // CREATE A SEED FOR RANDOMIZATION:
  srand((unsigned int)time(NULL));

  // CREATE A BUFFER TO HOLD ALL COMMANDS:
  std::vector<Data> cmdBuffer;
  populateBufferVector(cmdBuffer);

  // POPULATE A NEW LIST WITH COMMANDS FROM BUFFER:
  List<Node<Data>> activeCmdList;
  populateList(activeCmdList, cmdBuffer);

  // CREATE A PLAYER PROFILE:
  Player activePlayer;
  activePlayer.setPlayerInfo();

  // **************************************************************************************
  // DISPLAY MENU AND LET USER CHOOSE AN OPTION:
  // **************************************************************************************
  int menuChoice = 0;
  while (menuChoice != 6) {
    printMenu();
    menuChoice = getMenuOption();

    switch (menuChoice) {
      case 1:
        std::cout << std::endl << "\tOPTION 1: GAME RULES. . ." << std::endl;
        printGameRules();
        break;
      case 2:
        activePlayer.hardRESETpoints();
        std::cout << std::endl << "\tOPTION 2: STARTING GAME. . ." << std::endl;
        playGame(cmdBuffer, activeCmdList, activePlayer);
        break;
      case 3:
        std::cout << std::endl
                  << "\tOPTION 3: LOADING PREVIOUS GAME. . ." << std::endl;
        loadPreviousGame(cmdBuffer, activeCmdList, activePlayer);
        break;
      case 4:
        std::cout << std::endl << "\tOPTION 4: ADD COMMAND. . ." << std::endl;
        addCommand(activeCmdList, cmdBuffer);
        break;
      case 5:
        std::cout << std::endl
                  << "\tOPTION 5: REMOVE COMMAND. . ." << std::endl;
        removeCommand(activeCmdList /*, cmdBuffer*/);
        break;
      case 6:
        std::cout << std::endl << "\tEXITING. . ." << std::endl << std::endl;

        break;
    }
  }

  writeToCmdFile(activeCmdList);
  writeToProfiles(activePlayer);
  activeCmdList.~List();
  return 0;
}
