#include "EventManager.hpp"
#include "Test.hpp"

// ADVANTAGES/DISADVANTAGES LINKED LIST:

// ADVANTAGES/DISADVANTAGES ARRAY:

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