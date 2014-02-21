#pragma once
#include <Windows.h>
#using <System.dll>

#ifndef FILE_H
#define FILE_H

using namespace System;
using namespace System::Collections::Generic;

public ref class GameBase {
public:
	GameBase()								   { puzzleName = ""; puzzleType = ""; LevelOfDifficulty = 0;} // holder
	virtual void setName(System::String^ Name) { this->puzzleName = Name; }
	System::String^ getName()				   { return puzzleName; }
	void setType(System::String^ type)         { this->puzzleType = type; }
	System::String^ getType()				   { return puzzleType; }
	void setLevelOfDifficulty(int level)	   {this->LevelOfDifficulty = level; }
	int getLevelOfDifficulty()				   {return this->LevelOfDifficulty;}

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
public ref class KnobPuzzle : public GameBase
{

public:

	KnobPuzzle(void);
	KnobPuzzle(System::String^ code); 
	~KnobPuzzle(void);
	int getNumPieces()		      { return this->numPieces; }
	void setNumPieces(int num)    { this->numPieces = num; }
	int setGame(System::String^ code);
	KnobPuzzle^ returnHandle()		 {return this;}
	virtual List<PuzzlePiece^>^ getPieceList() { return this->pieceList; }
	int SaveCalibrationSettings() { 
				int success = this->WriteSettingsToFile(); 
				return success;
	}

protected:
	HANDLE myMutex;
	int numPieces;
	void LookUpGame(System::String^ code);
	int ParseShapeInformation(array<System::String^>^ tokens, PuzzlePiece^ piece);
	int WriteSettingsToFile();
	//List<PuzzlePiece^>^ orderPlaced;
	List<PuzzlePiece^>^ pieceList;
};

#endif