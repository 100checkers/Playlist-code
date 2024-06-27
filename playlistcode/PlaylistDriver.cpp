//Playlist Driver

#include <iostream>
#include <limits>
#include "Playlist.h"

using namespace std;

char getMenuChoice();
void processMenuChoice(char, Playlist&);
int getInteger();
bool isInteger(const string& s);

int main() {
	Playlist playlist;
	char choice = ' ';

	choice = getMenuChoice();

	while (choice != 'q') {
		processMenuChoice(choice, playlist);
		choice = getMenuChoice();
	}

	cout << "\n>>> Exiting Playlist <<<" << endl;

	return 0;
}

char getMenuChoice() {
	// Output menu option, prompt users for valid selection
	string menuOptions = "adpstocq";
	char choice = ' ';

	do {
		cout << "\n ************** PLAYLIST MENU **************************" << endl;

		cout << "\ta - Add song" << endl;
		cout << "\td - Remove song" << endl;
		cout << "\tp - Change position of song" << endl;
		cout << "\ts - Output songs by specific artist" << endl;
		cout << "\tt - Output total time of playlist (in seconds)" << endl;
		cout << "\to - Output full playlist" << endl;
		cout << "\tc - Clear playlist" << endl;
		cout << "\tq - Quit" << endl << endl;

		cout << "\tChoose option: ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << " *******************************************************" << endl;

	} while (menuOptions.find(choice) == string::npos);

	return choice;
}

void processMenuChoice(char choice, Playlist& playlist) {
	// Declaration of local variables needed for this function
	SongNode* songNode = nullptr;
	string uniqueID;
	string songName;
	string artistName;
	int songLength = 0;

	int nodeCount = 0;
	int currPosition = 0;
	int newPosition = 0;

	// Corresponding menu action 
	switch (choice) {
	case 'a':
		// Add song to playlist...	Prompt user for song unique id
		//							if the playlist already contains this id, print message and break
		//							else if, prompt for the rest of the song information
		//							create a new SongNode
		//							insert at the front of the playlist
		//							print the playlist
		cout << endl;
		cout << "\tAdd Song - Enter song's unique ID: ";
		//cin.ignore();
		getline(cin, uniqueID);

		if (playlist.contains(uniqueID)) {
			cout << endl;
			cout << "\t<<< Duplicate unique ID - not added! >>>" << endl;
			break;
		}
		cout << "\t\tEnter song's name: ";
		//cin.ignore();
		getline(cin, songName);

		cout << "\t\tEnter artist's name: ";
		//cin.ignore();
		getline(cin, artistName);

		cout << "\t\tEnter song's length (in seconds): ";
		//cin >> songLength;
		songLength = getInteger();
		songNode = new SongNode(uniqueID, songName, artistName, songLength, nullptr);
		playlist.insertFront(songNode);
		playlist.printPlaylist();

		break;

	case 'd':
		// Remove song from playlist...		Prompt user for song unique id
		//									call remove
		//									print appropriate message based on results from remove
		//									print the playlist
		cout << endl;
		cout << "\tDelete Song - Enter song's unique ID: ";
		//cin.ignore();
		getline(cin, uniqueID);


		if (playlist.contains(uniqueID)) {
			cout << endl;
			cout << "\t<<< Successfully deleted song with unique ID " << uniqueID << " >>>" << endl;
			playlist.remove(uniqueID);
			playlist.printPlaylist();
			break;
		}
		else {
			cout << endl;
			cout << "\t<<< Song with unique ID ";
			cout << uniqueID << " not in playlist >>>" << endl;
		}
		playlist.printPlaylist();
		break;

	case 'p':
		// Change song position in playlist...  count the number of songs in the list
		//										if the count < = 1,     print appropriate message
		//										else if, ask user for valid current position -- use getInteger() to get value
		//										if entry invalid break with appropriate message
		//										ask user for valid new position -- use getInteger() to get value
		//										if entry invalid break with appropriate message
		cout << endl;
		cout << "\tChange Song's Playlist Position - " << endl;
		nodeCount = playlist.getNodeCount();

		if (nodeCount <= 1) {
			cout << "\t\t>>> Insufficent playlist length! <<<" << endl;
			break;
		}

		cout << "\t\tCurrent Position (1 through " << nodeCount << " ): ";
		currPosition = getInteger();
		if (currPosition < 1 || currPosition > nodeCount) {
			cout << "\n\t\t>>> Invalid current position! <<<" << endl;
			break;
		}

		cout << "\t\tNew position (1 through " << nodeCount << " ): ";
		newPosition = getInteger();
		if (newPosition == currPosition || newPosition < 1 || newPosition > nodeCount) {
			cout << "\n\t\t>>> Invalid new position! <<<" << endl;
			break;
		}
		//
		//										call changeSongPosition
		//										print out message
		//										print playlist
		playlist.changeSongPosition(currPosition, newPosition);
		cout << "\n\t>>> Song moved from position " << currPosition << " to position " << newPosition << " <<<\n";
		playlist.printPlaylist();
		break;

	case 's':
		// output songs by specific artist..	prompt the user for the artist's name
		//										Output playlist for specific artist
		cout << endl;
		cout << "\tSearch Playlist - Enter artist's name: ";
		//cin.ignore();
		getline(cin, artistName);
		playlist.printByArtist(artistName);
		break;

	case 't':
		// Output playlist total time
		cout << endl;
		cout << "\tPlaylist Total Time - ";
		cout << playlist.getTotalTime();
		cout << endl;
		break;

	case 'o':
		// Print the playlist
		playlist.printPlaylist();
		break;

	case 'c':
		// Clear the playlist
		cout << endl;
		cout << "\t>>> Playlist has been cleared! <<<" << endl;
		playlist.clearList();
		break;
	}
}


// getInteger() uses isInteger()
int getInteger() {
	string str = "";
	getline(cin, str);

	while (!(isInteger(str))) {
		cout << "\t\t\t>>> Invalid integer - please enter an integer: ";
		getline(cin, str);
	}

	// convert str to an int
	return stoi(str);
}

bool isInteger(const std::string& s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char* p; //stores the first location of non-integer character

	// The C library function long int strtol(const char *str, char **endptr, int base)
	//		converts the initial part of the string in str to a long int value according
	//		to the given base, which must be between 2 and 36 inclusive, or be the special value 0.
	strtol(s.c_str(), &p, 10);

	return (*p == 0); // will be true if s contains an integer
}

