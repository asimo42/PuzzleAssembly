#include "stdafx.h"
#include <string>
#include <stack>
#include <process.h>
#include <stdio.h>
#include <Windows.h>
#using <System.dll>
#include "GameBoard.h"

#ifndef FILE_J
#define FILE_J

using namespace System::Collections::Generic;
/*  This class serves to share game data globally.  
It is only a thin layer of protection against the heavy risks of sharing global data.  Treat it as such!

A single instance of this class is created, and the handle ofthat instance is given to any function that needs to
access the element data.  Thus all changes are processed by this instance.  Functions can only change values one at a 
time, thanks to a system of mutex locks.  This way no two parts of the program can try to change something at once.  
Also, as all variables are always kept in one place, there 'should' be no duplicate or alternate versions of the same data; all parts 
of the program are using the same thing if handled properly.  
*/
ref class HandleVariables
{
public: 
	// some variables:
	// need for audio or visual hint (maybe should trigger a callback when this is hit)
	bool PAUSE_GAME;
	bool START_GAME;
	bool END_GAME;
	bool GAME_OVER;
	System::String^ PIECE_PLACED;
	void InitializeFlags();

	System::String^ JunkLine;
	void setVTKNodeChanged(int index);
	void setPiecePlaced(System::String^ pieceName);
	void setPiecePlaced(std::string pieceName);
	void setGameOver();
	void resetGameOver();

	// retrieving/ viewing the variables
	HandleVariables^ returnHandle() {return this;}

private:
	PuzzlePiece^ puzzleClass;
	HANDLE myMutex;

};

#endif