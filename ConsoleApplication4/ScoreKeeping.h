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

// a simplified class that holds the data for a given game. This controls how file output appears, and scoring data is displayed.
ref class GamePlayedData {

public: 
	GamePlayedData();
	~GamePlayedData() {};
	GamePlayedData(GamePlayed^ inputGame);
	void Initialize();

	bool isSet;
	bool NOT_COMPLETED;

	System::String^ playerName;
	System::String^ gameName;

	int levelOfDifficulty;
	int averageTimeBetweenPieces;
	int timeForCompletion;

	List<int>^ timesOfPlacement; // actual times of placement (minus start time) in seconds
	List<int>^ timeBetweenPlacements; // time it took to place each piece in seconds
	List<System::String^>^ orderOfPiecesPlayed; // names of pieces, from first placed to last placed

	// the following refer to the time the game was started
	System::String^ month;
	System::String^ day;
	System::String^ year;
	System::String^ seconds;
	System::String^ minutes;
	System::String^ hours;

	System::String^ writeOut();
	System::String^ buildFileName();

	int Save();

};

// Keeps stats of a single game. Can only be compiled once, then becomes essentially read-only
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
	GamePlayedData^ getGameData();
	

	void setStartTimeToNow(); // tell GamePlayed to pull the current date/time to record as start time
	void setTimeCompletedToNow(); // tell GamePlayed to pull the current date/time to record as end time
	void gameEndedEarly();

	int getTimeForCompletion() { return this->timeForCompletion; }

	double getAverageTimeBetweenPieces() { return this->avgTimeBetweenPieces; }
	DateTime getTimeStarted() { return this->timeStarted; }
	List<int>^ getTimesOfPlacement() { return this->timesOfPlacement; }
	List<int>^ getTimesBetweenPlacements() { return this->timeBetweenPlacements; }
	List<System::String^>^ getOrderOfPiecesPlayed() { return this->orderOfPiecesPlayed; }
	int getLevelOfDifficulty() { return this->levelOfDifficulty; }

	int compileData(); // pull information from puzzle pieces to fill arrays. Can only do this once


	KnobPuzzle^ getGame() { return this->game; }

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
//----------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------//-------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------//--------------------------------------------------------------------------------------

// Keeps running stats of the whole session ( >= 1 game) or possibly over multiple sessions (future addition)
// Stores data via GamePlayedData^ objects
// MOST OF THIS IS DEPRECATED - moving towards renovation or removal
ref class ScoreKeeping 
{
public:
	HANDLE myMutex;
	List<GamePlayedData^>^ individualGamesList;

	ScoreKeeping();
	ScoreKeeping^ returnHandle() { return this; }
	void AddNewGame(GamePlayedData^ newGame) { this->individualGamesList->Add(newGame); }
	System::String^ showFinalResults();  
	//int saveSessionResultsToFile(System::String^ fileName);
	//int loadSessionResultsFromFile(System::String^ fileName);
	//System::String^ printGamePlayedData(GamePlayed^ gamePlayed);

private:
	//GamePlayed^ calculateAverageForGame(System::String^ gameName);

};

#endif