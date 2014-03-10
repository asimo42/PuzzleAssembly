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

	// basic gets and sets
	virtual void setName(System::String^ Name) { this->puzzleName = Name; }
	System::String^ getName()			   { return puzzleName; }
	void setType(System::String^ type)     { this->puzzleType = type; }
	System::String^ getType()			   { return puzzleType; }
	void setLevelOfDifficulty(int level)   { this->LevelOfDifficulty = level; }
	int getLevelOfDifficulty()			   { return this->LevelOfDifficulty; }
	System::String^ getErrorString()       { return this->errorString; }

	// set or reset END_GAME. This is a disguised global variable to communicate with RunTracking class
	void setEndGame()				{ this->END_GAME = true; }
	void resetEndGame()				{ this->END_GAME = false; }

	// check if the game is over, or if there has been an error
	bool isEndGame()			    { return this->END_GAME; }
	bool checkIfError()				{ return this->Error; }

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
	~KnobPuzzle(void); // make sure mutex gets released

	// access class data from outside
	int setGame(System::String^ code);

	// check if puzzle has been initialized. Overloaded.
	bool checkIsInitialized();   // any game loaded
	bool checkIsInitialized(System::String^ code);   // game with given name has been loaded
	//bool checkIsInitialized(System::String^ code, int level);   // game with given name and level of difficulty has been loaded


	List<PuzzlePiece^>^ getPieceList() { return this->pieceList; }

	// manipulate class
	KnobPuzzle^ returnHandle()		 {return this;}   // return this (KnobPuzzle) as a (KnobPuzzle^)

	// write out current class data to file (normally newly calibrated values)
	int SaveCalibrationSettings();

protected:

private:
	// individual piece information
	List<PuzzlePiece^>^ pieceList;

	void Initialize();
	void LookUpGame(System::String^ code);
	int ParseShapeInformation(array<System::String^>^ tokens, PuzzlePiece^ piece);
	int WriteSettingsToFile();


};

#endif