#include "stdafx.h"
#include "GameBoard.h"

#ifndef FILE_G
#define FILE_G

using namespace System;
using namespace System::Collections::Generic;


// Keeps stats of a single game. Can only be compiled once, then becomes essentially read-only
ref class GamePlayed
{
public:

	GamePlayed();
	~GamePlayed();
	GamePlayed(KnobPuzzle^ Puzzle);

	void setGame(KnobPuzzle^ Puzzle);
	void setPlayer(System::String^ name) { this->player = name; }

	System::String^ getType() { return this->gameType; }
	System::String^ getName() { return this->gameName; }
	System::String^ getPlayer() { return this->player; }

	int Save();
	

	void setStartTimeToNow(); // tell GamePlayed to pull the current date/time to record as start time
	void setTimeCompletedToNow(); // tell GamePlayed to pull the current date/time to record as end time

	int getTimeForCompletion() { return this->timeForCompletion; }

	double getAverageTimeBetweenPieces() { return this->avgTimeBetweenPieces; }
	DateTime^ getTimeStarted() { return this->timeStarted; }
	List<int>^ getTimesOfPlacement() { return this->timesOfPlacement; }
	List<System::String^>^ getOrderOfPiecesPlayed() { return this->orderOfPiecesPlayed; }
	int getLevelOfDifficulty() { return this->levelOfDifficulty; }

	int compileData(); // pull information from puzzle pieces to fill arrays. Can only do this once
	System::String^ printData();

private:

	KnobPuzzle^ game;		   // class holding all the puzzle data. ONLY HAS KNOBPUZZLE RIGHT NOW
	System::String^ gameType;  // type of game, e.g. knobpuzzle, blockpuzzle, snake...
	System::String^ gameName;  // name of the game. e.g. KNOBPUZZLE1
	System::String^ player;    // this is the name of the player
	int levelOfDifficulty;

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

// Keeps running stats of the whole session ( >= 1 game) or possibly over multiple sessions (future addition)
// Stores data via GamePlayed^ objects
ref class ScoreKeeping 
{
public:
	HANDLE myMutex;
	List<GamePlayed^>^ individualGamesList;

	ScoreKeeping();
	ScoreKeeping^ returnHandle() { return this; }
	void AddNewGame(GamePlayed^ newGame) { this->individualGamesList->Add(newGame); }
	System::String^ showFinalResults();  
	int saveSessionResultsToFile(System::String^ fileName);
	int loadSessionResultsFromFile(System::String^ fileName);

private:
	GamePlayed^ calculateAverageForGame(System::String^ gameName);

};

#endif