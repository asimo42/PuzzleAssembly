#include "stdafx.h"
#using <System.dll>
#include <string>
#include <stack>
#include <process.h>
#include <stdio.h>
#include <Windows.h>
#include "PuzzlePiece.h"
#include "GameBoard.h"

#ifndef FILE_D
#define FILE_D

/*   This class serves to share flags globally to allow communication between the GUI and the VTK interactor.  
It is only a thin layer of protection against the heavy risks of sharing global data.  Treat it as such!

A single instance of this class is created, and the handle ofthat instance is given to any function that needs to
access the flags.  Flag states can be read freely, but changes must be processed by this instance.  Functions can 
only change values one at a time, thanks to a system of mutex locks.  This way no two parts of the program can try to
change something at once (or so the internet tells me).  

Also, this is just a convenient way to keep all the flags organized and in one place.  
*/
public ref class HandleFlags
{

public: 

	bool PAUSE_GAME;
	bool START_GAME;
	bool END_GAME;
	System::String^ PIECE_PLACED;
	int VTK_NODE_CHANGED;
	void InitializeFlags();
	HandleFlags^ returnHandle() {return this;}


	System::String^ JunkLine;
	void setVTKNodeChanged(int index);
	void setPiecePlaced(System::String^ pieceName);
	void setPiecePlaced(std::string pieceName);


private:
	PuzzlePiece^ puzzleClass;
	HANDLE myMutex;
};

#endif