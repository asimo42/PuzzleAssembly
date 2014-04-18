/*
These classes record and compile the performance data for each session (i.e. users, games, times pieces were placed)
It also controls file IO for saving performance data. 
*/

#pragma once
#include "stdafx.h"
#include "GameBoard.h"

#ifndef FILE_G
#define FILE_G

using namespace System;
using namespace System::Collections::Generic;


// GamePlayedData and GamePlayed are circularly dependent, so declare them both beforehand
ref class GamePlayedData;
ref class GamePlayed;

// Keeps stats of a single game. Is compiled into a GamePlayedData instance, and then is no longer used. 
ref class GamePlayed
{
public:

	GamePlayed();
	~GamePlayed();
	GamePlayed(KnobPuzzle^ Puzzle);

	void setGame(KnobPuzzle^ Puzzle);
	void setPlayer(System::String^ name) { this->player = name; }
	bool NOT_COMPLETED;

	System::String^ getType() { return this->gameType; }
	System::String^ getName() { return this->gameName; }
	System::String^ getPlayer() { return this->player; }
	GamePlayedData^ getGameData() { return this->gameData; }
	KnobPuzzle^ getGame() { return this->game; }
	int getLevelOfDifficulty() { return this->levelOfDifficulty; }
	
	// tell GamePlayed to pull the current date/time to record as start or end time
	void setStartTimeToNow(); // tell GamePlayed to pull the current date/time to record as start time
	void setTimeCompletedToNow();

	void gameEndedEarly();

	int getTimeForCompletion() { return this->timeForCompletion; }

	// functions for compiling data
	int compileData(); // pull information from puzzle pieces to fill arrays. Can only do this once
	double getAverageTimeBetweenPieces() { return this->avgTimeBetweenPieces; }
	DateTime getTimeStarted() { return this->timeStarted; }
	List<int>^ getTimesOfPlacement() { return this->timesOfPlacement; }
	List<int>^ getTimesBetweenPlacements() { return this->timeBetweenPlacements; }
	List<System::String^>^ getOrderOfPiecesPlayed() { return this->orderOfPiecesPlayed; }

private:

	KnobPuzzle^ game;		   // class holding all the puzzle data. ONLY HAS KNOBPUZZLE RIGHT NOW
	System::String^ gameType;  // type of game, e.g. knobpuzzle, blockpuzzle, snake...
	System::String^ gameName;  // name of the game. e.g. KNOBPUZZLE1
	System::String^ player;    // this is the name of the player
	int levelOfDifficulty;

	GamePlayedData^ gameData;
	bool ALREADY_COMPILED;

	DateTime timeStarted; // datetime object with time that the puzzle was started
	DateTime timeCompleted; // datetime object with time that the puzzle was ended

	int timeForCompletion; // time between start and end of game in seconds
	double avgTimeBetweenPieces;

	// please note that these three arrays are like a separated dictionary - 
	// each entry in OrderOfPiecesPlayed should correspond to the matching index in the other two arrays. 
	// BE VERY CAREFUL WITH THIS
	List<int>^ timesOfPlacement; // actual times of placement (minus start time) in seconds
	List<int>^ timeBetweenPlacements; // time it took to place each piece in seconds
	List<System::String^>^ orderOfPiecesPlayed; // names of pieces, from first placed to last placed

	void Initialize();
};

//----------------------------------------------------------------------------------------------------------//-------------------------------------------------------------------------

// a simplified class that holds the data for a given game. This controls how file output appears, and scoring data is displayed.
ref class GamePlayedData {

public: 
	GamePlayedData();
	~GamePlayedData() {}
	GamePlayedData(GamePlayed^ inputGame);
	void Initialize();

	bool isSet; // can only be set once; once isSet is true (data compiled), shouldn't be able to change anything
	bool NOT_COMPLETED; // set if the game was ended prematurely

	System::String^ playerName;
	System::String^ gameName;

	int levelOfDifficulty;
	int averageTimeBetweenPieces;
	int timeForCompletion;

	List<int>^ timesOfPlacement; // actual times of placement (minus start time) in seconds
	List<int>^ timeBetweenPlacements; // time it took to place each piece in seconds
	List<System::String^>^ orderOfPiecesPlayed; // from first placed to last placed

	// the following refer to the time the game was started
	System::String^ month;
	System::String^ day;
	System::String^ year;
	System::String^ seconds;
	System::String^ minutes;
	System::String^ hours;

	System::String^ writeOut(); // returns a string of the data
	System::String^ buildFileName();

	int Save(); // writes the data to a file

};


//----------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------

// Keeps running stats of the whole session ( >= 1 game). Stores data via GamePlayedData^ objects
public ref class ScoreKeeping 
{
public:
	HANDLE myMutex;
	List<GamePlayedData^>^ individualGamesList;

	ScoreKeeping();
	void AddNewGame(GamePlayedData^ newGame) { this->individualGamesList->Add(newGame); }
	System::String^ showFinalResults();  

private:
	//GamePlayed^ calculateAverageForGame(System::String^ gameName);
};

#endif