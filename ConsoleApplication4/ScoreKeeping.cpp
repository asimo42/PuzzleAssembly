#include "stdafx.h"
#include "GameBoard.h"
#include "ScoreKeeping.h"
#include <Windows.h>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>

using namespace System;
using namespace System::Collections::Generic;

GamePlayed::GamePlayed() 
{
}
//----------------------------------------------------------------------------------------------------------

GamePlayed::~GamePlayed() 
{
}
//----------------------------------------------------------------------------------------------------------

GamePlayed::GamePlayed(KnobPuzzle^ Puzzle) 
{
	this->game = Puzzle;
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::setGame(KnobPuzzle^ Puzzle)
{
	this->game = Puzzle;
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::addNewTimeandPiece(int newTime, System::String^ puzzlePiece)
{
	this->timesBetweenPieces->Add(newTime);
	this->orderOfPiecesPlayed->Add(puzzlePiece);
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::setTimeForCompletion(int newTime)
{
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::CalcAvgTimeBetweenPieces()
{
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::setFastestSlowest()
{
	int fastest = 0;
	int slowest = 999999999;
	int indexS = 0; int indexF = 0;
	// if no pieces were played (or failed to record) return "N/A"
	if (this->timesBetweenPieces->Count == 0) {
		this->slowestPiece = gcnew System::String("N/A");
		this->fastestPiece = gcnew System::String("N/A");
		return;
	}
	// otherwise, scroll through times, pick fastest and slowest
	for each (int tim in timesBetweenPieces) {
		if (tim < fastest) { fastest = tim; indexF = timesBetweenPieces->IndexOf(tim); }
		if (tim > slowest) { slowest = tim; indexS = timesBetweenPieces->IndexOf(tim); }
	}
	this->slowestPiece = orderOfPiecesPlayed[indexS];
	this->fastestPiece = orderOfPiecesPlayed[indexF];
}
//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
