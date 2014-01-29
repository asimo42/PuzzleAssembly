#include "stdafx.h"
#include "GameBoard.h"

#ifndef FILE_G
#define FILE_G

using namespace System;
using namespace System::Collections::Generic;


// Keeps stats of a single game
ref class GamePlayed
{
public:

	System::String^ gameType;
	KnobPuzzle^ game;

	int timeForCompletion;
	double avgTimeBetweenPieces;
	DateTime^ timeStarted;
	List<int>^ timesOfPlacement;
	List<System::String^>^ orderOfPiecesPlayed;

	GamePlayed();
	~GamePlayed();
	GamePlayed(KnobPuzzle^ Puzzle);
	System::String^ getType() {return this->gameType;}
	void setGame(KnobPuzzle^ Puzzle);
	void setType(System::String^ type) {this->gameType = type;}
	void setTimeForCompletion(int newTime) {this->timeForCompletion = newTime; }
	void compileData();
	System::String^ printData();

private:
	void CalcAvgTimeBetweenPieces();
	void findOrderOfPieces();
	void findSortedTimes();
};


// Keeps running stats of the whole session ( >= 1 game) or possibly over multiple sessions (future addition)
ref class ScoreKeeping 
{
public:
	HANDLE myMutex;
	List<GamePlayed^>^ individualGamesList;

	ScoreKeeping();
	ScoreKeeping^ returnHandle() { return this; }
	void AddNewGame(GamePlayed^ newGame);
	System::String^ showFinalResults();    

private:
	GamePlayed^ calculateAverageForGame(System::String^ gameName);

};

#endif