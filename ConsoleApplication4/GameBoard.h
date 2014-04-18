/* These classes hold the data for each individual gameboard. There is a GameBase class which has all the basic information in it,
and classes for individual game types can derive from it. Only the KnobPuzzle has been developed this year. An instance of the KnobPuzzle
class contains all information as to the name, shape, location, placement, etc. of each puzzle piece for a given board. 
This instance will be passed all around through the program, to be used by tracking, scorekeeping, and the GUI
*/

#pragma once
#include <Windows.h>
#using <System.dll>

#ifndef FILE_H
#define FILE_H

using namespace System;
using namespace System::Collections::Generic;

// generic game class, with stop/start info etc. Different types of games can inherit from this class
public ref class GameBase {
public:

	GameBase()	{ puzzleName = ""; puzzleType = ""; LevelOfDifficulty = 0; END_GAME = false;} 

	// basic gets and sets
	virtual void setName(System::String^ Name) { this->puzzleName = Name; }
	System::String^ getName()			   { return puzzleName; }
	void setType(System::String^ type)     { this->puzzleType = type; }
	System::String^ getType()			   { return puzzleType; }
	void setLevelOfDifficulty(int level)   { this->LevelOfDifficulty = level; }
	int getLevelOfDifficulty()			   { return this->LevelOfDifficulty; }

	// set or reset END_GAME. This is a communication link between the main GUI and the RunTracking class
	void setEndGame()				{ this->END_GAME = true; }
	void resetEndGame()				{ this->END_GAME = false; }

	// check if the game is over, or if there has been an error
	bool isEndGame()			    { return this->END_GAME; }
	void setError()					{ this->Error = true; }
	bool checkIfError()				{ return this->Error; }

protected:

	HANDLE myMutex;
	bool Error;
	bool END_GAME;
	System::String^ puzzleName;
	System::String^ puzzleType;
	int LevelOfDifficulty; 

};


//------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------


// Class specific to Knob Puzzle; Inherits from GameBase. initializes and manages list of puzzle pieces for a knob puzzle
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
	bool checkIsInitialized(System::String^ code, int level);   // game with given name and level of difficulty has been loaded

	List<PuzzlePiece^>^ getPieceList() { return this->pieceList; }

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