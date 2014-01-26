#pragma once
#include <string>
#include <Windows.h>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include "PuzzlePiece.h"


#ifndef FILE_H
#define FILE_H

using namespace System;
//using namespace cv;
using namespace System::Collections::Generic;

ref class GameBase {
public:
	System::String^ puzzleName;
	System::String^ puzzleType;

	GameBase() { puzzleName = ""; } // holder
	virtual void SetName(System::String^ Name) { this->puzzleName = Name; }
	System::String^ GetName() { return puzzleName; }
	System::String^ GetType() { return puzzleType; }
	double getTimeTaken() {return this->TimeTaken;}
	int getLevelOfDifficulty() {return this->LevelOfDifficulty;}
	virtual bool CheckCompleted() {
		if (Completed || Cancelled) {return true;}
		else {return false;}
	}
	virtual void setStart() { this->Started = true; }
	virtual void setCompleted() { this->Completed = true; }
	virtual void setCancelled() { this->Cancelled = true; }

protected:

	int gameID;
	bool Started;
	bool Completed;
	bool Cancelled;
	bool Error;
	double TimeTaken;
	int LevelOfDifficulty;

	virtual void setTimeTaken( double timeTaken) {this->TimeTaken = timeTaken; }
	virtual void setLevelOfDifficulty(int level) { this->LevelOfDifficulty = level; }
};


// this class should create the puzzle piece classes
ref class KnobPuzzle : public GameBase
{

public:
	int numPieces;

	KnobPuzzle(void);
	KnobPuzzle(System::String^ code); 
	~KnobPuzzle(void);


protected:
	HANDLE myMutex;
	List<PuzzlePiece^>^ pieceList;
	void LookUpGame(System::String^ code);

};

#endif