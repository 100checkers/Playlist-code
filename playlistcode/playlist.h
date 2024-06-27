//playlist.h

#ifndef __PLAYLIST__
#define __PLAYLIST__
#include "SongNode.h"
using namespace std;

class Playlist {
public:
	//Default and only constructor
	Playlist();

	//Destructor
	~Playlist();

	int getNodeCount();

	//Add a SongNode to the front of the list
	void insertFront(SongNode* songNode);

	//Removes a SongNode from the list; if the value doesn't exist in the list return false;
	//   otherwise search for the SongNode, adjust pointers, and return true.
	bool remove(string id);

	void changeSongPosition(int songPosition, int newPosition);

	// insertAfter ... inserts newNode after prevNode
	void insertAfter(SongNode* prevNode, SongNode* newNode);

	// Calculates total time in seconds in playlist
	int getTotalTime();

	// Prints out all nodes in the list
	void printPlaylist();

	// Prints out all nodes in the list
	void printByArtist(string artist);

	// Searches to see if list contains a duplicate uniqueID
	bool contains(const string& id);

	// Clears the list -- remove all nodes
	void clearList();

private:
	// Sets up linked list starting values
	void init();

	// Deletes allocated objects
	void eraseList(SongNode* head);

	// Prints headings for playlist table
	void printTableHeadings();

	// Prints song list in table format
	void printTableRow(SongNode* song, int position);

	SongNode* head = nullptr;
	int nodeCount = 0;
};
#endif

