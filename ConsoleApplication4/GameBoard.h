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
using namespace System::Collections::Generic;

ref class GameBase {
public:
	System::String^ puzzleName;
	System::String^ puzzleType;

	GameBase() { puzzleName = ""; puzzleType = ""; LevelOfDifficulty = 0;} // holder
	virtual void SetName(System::String^ Name) { this->puzzleName = Name; }
	System::String^ GetName() { return puzzleName; }
	System::String^ GetType() { return puzzleType; }
	int getLevelOfDifficulty() {return this->LevelOfDifficulty;}

protected:

	bool Error;
	int LevelOfDifficulty;

	virtual void setLevelOfDifficulty(int level) { this->LevelOfDifficulty = level; }
};


// Class specific to Knob Puzzle; initializes and manages list of puzzle pieces
ref class KnobPuzzle : public GameBase
{

public:
	int numPieces;

	KnobPuzzle(void);
	KnobPuzzle(System::String^ code); 
	~KnobPuzzle(void);
	List<PuzzlePiece^>^ pieceList;
	//List<PuzzlePiece^>^ orderPlaced;

protected:
	HANDLE myMutex;
	void LookUpGame(System::String^ code);

};

#endif