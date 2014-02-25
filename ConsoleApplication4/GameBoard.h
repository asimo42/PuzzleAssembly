#pragma once
#include <Windows.h>
#using <System.dll>

#ifndef FILE_H
#define FILE_H

using namespace System;
using namespace System::Collections::Generic;

public ref class GameBase {
public:
	GameBase()							   { puzzleName = ""; puzzleType = ""; errorString = ""; LevelOfDifficulty = 0; END_GAME = false;} 
	virtual void setName(System::String^ Name) { this->puzzleName = Name; }
	System::String^ getName()			   { return puzzleName; }
	void setType(System::String^ type)     { this->puzzleType = type; }
	System::String^ getType()			   { return puzzleType; }
	void setLevelOfDifficulty(int level)   { this->LevelOfDifficulty = level; }
	int getLevelOfDifficulty()			   { return this->LevelOfDifficulty; }
	System::String^ getErrorString()       { return this->errorString; }
	void setEndGame()				{ this->END_GAME = true; }
	void resetEndGame()				{ this->END_GAME = false; }
	bool isEndGame()			    { return this->END_GAME; }

protected:

	HANDLE myMutex;

	bool Error;
	bool END_GAME;
	System::String^ puzzleName;
	System::String^ puzzleType;
	System::String^ errorString;
	int LevelOfDifficulty; // level of difficulty not currently in use

};


//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------


// Class specific to Knob Puzzle; initializes and manages list of puzzle pieces
public ref class KnobPuzzle : public GameBase
{

public:

	// constructors
	KnobPuzzle(void);
	KnobPuzzle(System::String^ code);
	KnobPuzzle(const KnobPuzzle^) {} // copy constructor 1 : pass in KnobPuzzle^
	KnobPuzzle(const KnobPuzzle%) {} // copy constructor 2 : pass in KnobPuzzle
	~KnobPuzzle(void);

	// access class data from outside
	int setGame(System::String^ code);
	bool checkIsInitialized(System::String^ code);   //check if the given game (input string) has already been loaded
	List<PuzzlePiece^>^ getPieceList() { return this->pieceList; }

	// manipulate class
	KnobPuzzle^ returnHandle()		 {return this;}   // return this (KnobPuzzle) as a (KnobPuzzle^)

	// write out current class data to file (normally newly calibrated values)
	int SaveCalibrationSettings();

protected:

	// individual piece information
	List<PuzzlePiece^>^ pieceList;

	void Initialize();
	void LookUpGame(System::String^ code);
	int ParseShapeInformation(array<System::String^>^ tokens, PuzzlePiece^ piece);
	int WriteSettingsToFile();

private:

};

#endif