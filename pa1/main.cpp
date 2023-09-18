#include "EventManager.hpp"
#include "Test.hpp"

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

// Initialize the global variables
LinkedList<Data> commands;
profile profiles[11];
int currentPlayer;
int totalFileIndex = 0;

int main (int argc, char **argv)
{
    // Run a test before start to ensure things are working
    int errorCode = 0;
    if (!testProgram(errorCode))
    {
        std::cout << "ERROR CODE: " << errorCode << std::endl;
        return errorCode;
    }

    // Captures user's choice
    int selection = 0;

    // File containing cmds and definitions
    std::fstream commandFile("commands.csv");
    // File containing user info
    std::fstream userFile("profiles.csv");

    // Load the cmds into the linked list
    while (!commandFile.eof())
    {
        Data newData;
        commandFile >> newData;
        commands.insertBack(newData);
    }
    commandFile.close();

    // Load profiles into the profile array (max of 10)
    while (totalFileIndex < 10 && !userFile.eof())
    {
        // Catches info from stream
        std::string name, score;
        std::getline(userFile, name, ',');
        std::getline(userFile, score, '\n');

        // Save the position of the index
        int returnIndex = totalFileIndex++;

        // Move all profiles down one space
        while (returnIndex != 0)
        {
            profiles[returnIndex].userName = profiles[returnIndex - 1].userName;
            profiles[returnIndex].userScore = profiles[returnIndex - 1].userScore;
            returnIndex--;
        }

        // Assign the new data
        profiles[returnIndex].userName = name;
        profiles[returnIndex].userScore = std::stoi(score);
    }
    userFile.close();

    // Set the profile to the no entry profile
    currentPlayer = totalFileIndex;

    // Main Game Loop
    while (displayMenu(selection))
        // Controls user selection paths
        switch (selection)
        {
            // Game Rules
            case 1:
                displayRules();
                break;
            
            // New Game
            // Load Game
            case 2:
            case 3:
                getUserDetails();
                playGame();
                break;

            // Add Command
            case 4:
                addCommand();
                break;

            // Remove Command
            case 5:
                remCommand();
                break;

            // Display Commands
            case 6:
                dispCommands();
                break;
        }
    
    // Save both the list of commands and the
    saveAll();
    return 0;
}