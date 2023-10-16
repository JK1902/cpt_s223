#include <map>
#include "TwitterData.cpp"
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    // Schema: UserName,Last,First,Email,NumTweets,MostViewedCategory
    string raw_data[5][6] = {{"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"}};
    TwitterData *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }
	
	 std::map<string,class TwitterData> Map;

    // Insert data into the map
    for (int i = 0; i < 5; ++i)
    {
        Map[twitter_data[i].getUserName()] = twitter_data[i];
    }
	cout<<endl;
    // Iterate through the map and print the key-value pairs
    for(const auto& pair : Map) {
        cout << "Username: " << pair.first << ", Data: " << pair.second.getActualName() << ", " << pair.second.getEmail() << ", " << pair.second.getNumTweets() << ", " << pair.second.getCategory() << endl;
    }

    // Find the person with username "savage1" and print out the entire record
    auto it = Map.find("savage1");
	cout<<endl;
    if (it != Map.end()) {
        cout << "Found user with username savage1:" << endl;
        cout << "Username: " << it->first << ", Data: " << it->second.getActualName() << ", " << it->second.getEmail() << ", " << it->second.getNumTweets() << ", " << it->second.getCategory() << endl;
    } else {
        cout << "User with username savage1 not found." << endl;
    }

    // Remove the person with username "savage1" from the map
    Map.erase("savage1");

    // Print the map after removal
    cout << "\nMap after removing savage1:" << endl;
    for(const auto& pair : Map)
	 {
        cout << "Username: " << pair.first << ", Data: " << pair.second.getActualName() << ", " << pair.second.getEmail() << ", " << pair.second.getNumTweets() << ", " << pair.second.getCategory() << endl;
    }
	cout<<endl;

	std::map<string, class TwitterData> twitterMapByEmail;

    // Insert data into the map
    for (int i = 0; i < 5; ++i)
    {
        twitterMapByEmail[twitter_data[i].getEmail()] = twitter_data[i];
    }

    // Iterate through the map and print the key-value pairs
    for(const auto& pair : twitterMapByEmail) {
        cout << "Email: " << pair.first << ", Data: " << pair.second.getActualName() << ", " << pair.second.getUserName() << ", " << pair.second.getNumTweets() << ", " << pair.second.getCategory() << endl;
    }

    // Find the person with email "kat@gmail.com" and print out the entire record
     auto itByEmail = twitterMapByEmail.find("kat@gmail.com");
	 cout<<endl;
    if (itByEmail != twitterMapByEmail.end()) {
        cout << "Found user with email kat@gmail.com:" << endl;
        cout << "Email: " << itByEmail->first << ", Data: " << itByEmail->second.getActualName() << ", " << itByEmail->second.getUserName() << ", " << itByEmail->second.getNumTweets() << ", " << itByEmail->second.getCategory() << endl;
    } else {
        cout << "User with email kat@gmail.com not found." << endl;
    }

    // Remove the person with email "kat@gmail.com" from the map
    twitterMapByEmail.erase("kat@gmail.com");

    // Print the map after removal
    cout << "\nMap after removing kat@gmail.com:" << endl;
    for(const auto& pair : twitterMapByEmail) {
      cout << "Email: " << pair.first << ", Data: " << pair.second.getActualName() << ", " << pair.second.getUserName() << ", " << pair.second.getNumTweets() << ", " << pair.second.getCategory() << endl;
    }

    delete[] twitter_data;  //Free memory allocation.
    return 0;
}
