This program uses multiple files (two .cpp and two .h files) for improved navigation and readability. 
The program outputs various options for a user to select from and the option selected will call different functions; a switch statement filters 
the options based on user input that's read. 
Each node has a unique ID, song name, artist name, song length, and a pointer to the next node. 
This data is collected by information read from the user after the user selects the option to "Add song". 
This is achieved by using this-> to access the private variables in SongNode.h. 
Meanwhile, the playlist.h file stores function prototypes that are responsible for performing important tasks like rearranging song order, deleting a song, 
and printing songs by a specific artist. 
The Playlist.cpp file contains the functions that the switch calls. 

The pointer variables head, currNode, and prevNode were created for traversing through the list and changing positions.
