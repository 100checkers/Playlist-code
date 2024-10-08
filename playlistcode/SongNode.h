//SongNode.h

#ifndef __SONGNODE__
#define __SONGNODE__

#include <string>
using namespace std;

class SongNode {
public:
	SongNode(string uniqueID, string songName, string artistName, int songLength, SongNode* next) {
		this->uniqueID = uniqueID;
		this->songName = songName;
		this->artistName = artistName;
		this->songLength = songLength;
		this->next = next;
		return;
	}

	~SongNode() {}


	string getUniqueID() const {
		return this->uniqueID;
	}

	string getSongName() const {
		return this->songName;
	}

	string getArtistName() const {
		return this->artistName;
	}

	int getSongLength() const {
		return this->songLength;
	}

	void setNext(SongNode* nodePtr) {
		this->next = nodePtr;
		return;
	}

	SongNode* getNext() {
		return this->next;
	}

private:
	string uniqueID;
	string songName;
	string artistName;
	int songLength;
	SongNode* next;
};

#endif
