#pragma once

#include "Functions.h"

#ifndef FILE_G
#define FILE_G

using namespace System;
using namespace System::Collections::Generic;


// Keeps stats of a single game
ref class GamePlayed
{
public:
	System::String^ name;
	int score;
	int timeForCompletion;
	int avgTimeBetweenPieces;
	DateTime^ timeStarted;
	List<int>^ timesBetweenPieces;
	System::String^ gameType;
	KnobPuzzle^ game;
	System::String^ slowestPiece;
	System::String^ fastestPiece;
	List<System::String^>^ orderOfPiecesPlayed;

	GamePlayed();
	~GamePlayed();
	GamePlayed(KnobPuzzle^ Puzzle);
	System::String^ getType() {return this->gameType;}
	void setGame(KnobPuzzle^ Puzzle);
	void setType(System::String^ type) {this->gameType = type;}
	void addNewTimeandPiece(int newTime, System::String^ puzzlePiece);
	void setTimeForCompletion(int newTime);
	void CalcAvgTimeBetweenPieces();
	void setOrder();

};


// Keeps running stats of the whole session (potentially more than one)
ref class ScoreKeeping 
{
public:
	HANDLE myMutex;
	int numberOfGamesPlayed;
	List<System::String^>^ listOfGamesPlayed;
	int totalScore;
	List<GamePlayed^>^ individualGamesList;
	int Improvement;

	ScoreKeeping^ returnHandle() { return this; }
	void AddNewGame(GamePlayed^ newGame);
	System::String^ getGameResults(GamePlayed^ game);
	System::String^ showResults();    

	//void PrintFinalResults();
	//void PrintResultsForGame();

private:
	GamePlayed^ calculateAveragesByGameType(System::String^ gameType);

};




#endif