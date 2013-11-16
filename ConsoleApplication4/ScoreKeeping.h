#pragma once
#include <string>
#include <Windows.h>
#include <opencv2\opencv.hpp>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include "PuzzlePiece.h"
#include "GameBoard.h"
#include "Functions.h"

#ifndef FILE_G
#define FILE_G

using namespace System;
using namespace cv;
using namespace System::Collections::Generic;

// Keeps stats of a single game
ref class GamePlayed
{
	int score;
	int timeForCompletion;
	KnobPuzzle^ game;
	List<int>^ timesBetweenPieces;
	int avgTimeBetweenPieces;
	System::String^ slowestPiece;
	System::String^ fastestPiece;
	List<System::String^>^ orderOfPiecesPlayed;
public:
	GamePlayed();
	~GamePlayed();
	GamePlayed(KnobPuzzle^ Puzzle);
	void setGame(KnobPuzzle^ Puzzle);
	void addNewTimeandPiece(int newTime, System::String^ puzzlePiece);
	void setTimeForCompletion(int newTime);
	void CalcAvgTimeBetweenPieces();
	void setFastestSlowest();

};

// Keeps running stats of the whole session (potentially more than one)
ref class ScoreKeeping 
{
public:
	HANDLE myMutex;
	List<System::String^>^ listOfGamesPlayed;
	int totalScore;
	List<GamePlayed^>^ individualGamesList;
	int Improvement;

	//void AddNewGame(GamePlayed^ newGame);
	//void PrintFinalResults();
	//void PrintResultsForGame();

private:
	//int CalculateImprovement();

};
#endif