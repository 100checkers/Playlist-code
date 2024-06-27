// Playlist.cpp

#include <iostream>
#include <iomanip>
#include "Playlist.h"
using namespace std;

//Default and only constructor -- calls private function init
Playlist::Playlist() {
	init();
}

//Destructor -- calls private function eraseList with head
Playlist::~Playlist() {
	eraseList(head);
	cout << "\n>>> Playlist destructor Called >>>";
}

//Uses variable nodeCount to count how many nodes exist until there's no more left
int Playlist::getNodeCount() {
	SongNode* currNode = head;
	nodeCount = 0;
	while (currNode != nullptr) {
		nodeCount++;
		currNode = currNode->getNext();
	}
	return nodeCount;
}

//Adds a SongNode to the front of the list
void Playlist::insertFront(SongNode* songNode) {
	if (head == nullptr) {
		head = songNode;
	}
	else {
		songNode->setNext(head);
		head = songNode;
	}
}

//Remove a SongNode from the list; if the value doesn't exist in the list return false;
//   otherwise, searches for the SongNode, adjusts pointers, and return true.
bool Playlist::remove(string id) {
	SongNode* currNode = head;
	SongNode* prevNode = head;

	while (id != currNode->getUniqueID()) {
		prevNode = currNode;
		currNode = currNode->getNext();
	}

	if (currNode == head) {
		head = currNode->getNext();
		delete currNode;
	}
	else {
		prevNode->setNext(currNode->getNext());
		delete currNode;
	}
	return true;
}

//   songPosition and newPosition values have been validated in main before this function is called
void Playlist::changeSongPosition(int songPosition, int newPosition) {
	SongNode* currNode = head;
	SongNode* prevNode = nullptr;
	int count = 1;

	// STEP 1: Find songNode that is at songPosition
	while (count != songPosition) {
		prevNode = currNode;
		currNode = currNode->getNext();
		count++;
	}


	//STEP 2: Removes songNode from the list and adjusts prevNode to next node
	if (songPosition == 1) {	//song is at head
		head = currNode->getNext();
	}
	else {
		prevNode->setNext(currNode->getNext());
	}


	// STEP 3: Inserts song at new position
	insertFront(currNode);
		if (newPosition == 1) {
			insertFront(currNode);
		}
				else {
					prevNode = head;
					count = 1;
					while (count != newPosition - 1) {
						prevNode = prevNode->getNext();
						count++;
					}
					insertAfter(prevNode, currNode);
					}


}

// Inserts newNode after prevNode
void Playlist::insertAfter(SongNode* prevNode, SongNode* newNode) {

	if (prevNode != nullptr) {
		// Create newNode based on data parameter
		//newNode = new SongNode(string uniqueID, string songName, string artistName, int songLength, nullptr);

		// Set next of newNode as next of prevNode
		newNode->setNext(prevNode->getNext());
		// Set next of prevNode to newNode
		prevNode->setNext(newNode);
	}
}

// calculates playlist's total time (in seconds)
int Playlist::getTotalTime() {
	SongNode* currNode = head;
	int totalLength = 0;

	while (currNode != nullptr) {
		totalLength += currNode->getSongLength();
		currNode = currNode->getNext();
	}
	return totalLength;
}

// Prints out all nodes in the list

void Playlist::printPlaylist() {
	SongNode* currNode = head;
	printTableHeadings();

	if (currNode == nullptr) {
		cout << endl;
		cout << "\t>>> Playlist is empty! <<<" << endl;
	}
	else {
		currNode = head;
		int pos = 1;

		while (currNode != nullptr) {
			printTableRow(currNode, pos);
			//currNode->setNext(next) << " ";
			pos++;
			currNode = currNode->getNext();
		}
	}
}

// Prints out all nodes in the list with an artist's name
void Playlist::printByArtist(string artist) {
	SongNode* currNode = head;
	int pos = 1;
	printTableHeadings();
	while (currNode != nullptr) {
		if (currNode->getArtistName() == artist) {
			printTableRow(currNode, pos);
		}
		currNode = currNode->getNext();
		pos++;
	}

}

// Searches to see if list contains the uniqueID
bool Playlist::contains(const string& id) {
	SongNode* currNode = head;

	while (currNode != nullptr) {
		if (currNode->getUniqueID() == id) {
			return true;
		}
		else {
			currNode = currNode->getNext();
		}
	}
	return false;
}

// Clears the list -- removes all nodes 
void Playlist::clearList() {
	SongNode* currNode = head;
	SongNode* next;

	eraseList(head);
	init();
}

// Sets up linked list starting values
void Playlist::init() {
	head = nullptr;
	nodeCount = 0;
}

// Deletes all allocated objects
void Playlist::eraseList(SongNode* head) {
	SongNode* currNode = head;
	SongNode* next;

	while (currNode != nullptr) {
		next = currNode->getNext();
		delete currNode;
		currNode = next;
	}
}


// Prints headings for playlist table
void Playlist::printTableHeadings() {
	cout << "\n\t------------------------- PLAYLIST ------------------------------" << endl;
	cout << "\t" << setw(5) << left << "Pos  ";
	cout << setw(12) << left << "Unique Id";
	cout << setw(20) << left << "Song";
	cout << setw(20) << left << "Artist";
	cout << setw(4) << left << "Time" << endl;
}


void Playlist::printTableRow(SongNode* song, int position) {
	cout << "\t" << setw(5) << left << position;
	cout << setw(12) << left << song->getUniqueID();
	cout << setw(20) << left << song->getSongName();
	cout << setw(20) << left << song->getArtistName();
	cout << setw(4) << right << song->getSongLength() << endl;
}
