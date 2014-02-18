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
	GameBase()									   { puzzleName = ""; puzzleType = ""; LevelOfDifficulty = 0;} // holder
	virtual void setName(System::String^ Name)     { this->puzzleName = Name; }
	System::String^ getName()				   { return puzzleName; }
	void setType(System::String^ type) { this->puzzleType = type; }
	System::String^ getType()				   { return puzzleType; }
	void setLevelOfDifficulty(int level)	       {this->LevelOfDifficulty = level; }
	int getLevelOfDifficulty()					   {return this->LevelOfDifficulty;}

protected:

	bool Error;
	System::String^ puzzleName;
	System::String^ puzzleType;
	int LevelOfDifficulty; // level of difficulty not currently in use

	//virtual void setLevelOfDifficulty(int level) { this->LevelOfDifficulty = level; }
};


//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------


// Class specific to Knob Puzzle; initializes and manages list of puzzle pieces
ref class KnobPuzzle : public GameBase
{

public:

	KnobPuzzle(void);
	KnobPuzzle(System::String^ code); 
	~KnobPuzzle(void);
	int getNumPieces()		   { return this->numPieces; }
	void setNumPieces(int num) { this->numPieces = num; }
	List<PuzzlePiece^>^ getPieceList()        { return this->pieceList; }
	int setGame(System::String^ code);
	KnobPuzzle^ returnHandle()		 {return this;}
	int SaveCalibrationSettings() { 
				int success = this->WriteSettingsToFile(); 
				return success;
	}

protected:
	HANDLE myMutex;
	int numPieces;
	void LookUpGame(System::String^ code);
	List<PuzzlePiece^>^ pieceList;
	int WriteSettingsToFile();
	//List<PuzzlePiece^>^ orderPlaced;
};

#endif