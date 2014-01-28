#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include "Functions.h"

using namespace System;
using namespace System::Collections::Generic;

GamePlayed::GamePlayed() 
{
	this->gameType = "Unknown";
}
//----------------------------------------------------------------------------------------------------------

GamePlayed::~GamePlayed() 
{
}
//----------------------------------------------------------------------------------------------------------

GamePlayed::GamePlayed(KnobPuzzle^ Puzzle) 
{
	this->game = Puzzle;
	this->gameType = "KnobPuzzle";
	this->name = Puzzle->GetName();
	this->timeStarted = gcnew System::DateTime;
	this->timeStarted = this->timeStarted->Now;
	this->timesBetweenPieces = gcnew List<int>();
	this->orderOfPiecesPlayed = gcnew List<System::String^>();

}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::setGame(KnobPuzzle^ Puzzle)
{
	this->game = Puzzle;
	this->gameType = "KnobPuzzle";
	this->name = Puzzle->GetName();
	this->timeStarted = gcnew System::DateTime;
	this->timeStarted = this->timeStarted->Now;
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
	int sum = 0;
	int newtime = 0;
	for each (int tim in timesBetweenPieces) {
		newtime = tim - sum;
		sum += newtime;
	}
	int average = sum/timesBetweenPieces->Count;
	this->avgTimeBetweenPieces = average;
	return;
}
//----------------------------------------------------------------------------------------------------------

// changing this to make it the order of completion
void GamePlayed::setOrder()
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
ScoreKeeping::ScoreKeeping() {
	this->individualGamesList = gcnew List<GamePlayed^>();
}
//----------------------------------------------------------------------------------------------------------
// Add a new instance of GamePlayed into the ScoreKeeping class
void ScoreKeeping::AddNewGame(GamePlayed^ newGame) 
{
	this->numberOfGamesPlayed = this->numberOfGamesPlayed + 1;
	this->individualGamesList->Add(newGame); 
}
//----------------------------------------------------------------------------------------------------------
System::String^ ScoreKeeping::getGameResults(GamePlayed^ game) 
{
	if (game->orderOfPiecesPlayed->Count == 0)
	{
		return "game not completed";
	}
	System::String^ resultString = "";
	resultString = "Game : " + game->name + "\n";
	System::String^ tim = game->timeStarted->ToString("F");
	resultString = resultString + "Time Started : " + tim + "\n";
	resultString = resultString + "Time for Completion : " + game->timeForCompletion + "\n";
	game->CalcAvgTimeBetweenPieces();
	resultString = resultString + "Average Time Between Pieces: " + game->avgTimeBetweenPieces + "\n";
	for (int i = 0; i < game->orderOfPiecesPlayed->Count; i++) 
	{ 
		resultString = resultString + "Piece : " + game->orderOfPiecesPlayed[i] + 
			"       Time Placed (sec) : " + game->timesBetweenPieces[i] + "\n";
	}

	return resultString;
}

//----------------------------------------------------------------------------------------------------------
// return a string for printing out all results, to be displayed from the GUI.  
// will calculate and all stats for individual games, the session, and through history (future addition)
System::String^ ScoreKeeping::showResults() 
{
	// this might take a while, so lock this thread down
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "compiling results");
	System::String^ finalString = "		Performance and Progress\n";
// will need to add in historical data here, but for now we'll keep it simple and just do one session
	// start off by getting the results for each individual game
	List<System::String^>^ individualGameStrings = gcnew List<System::String^>();  // to hold each game's result string
	System::String^ individualResult = "";
	for each (GamePlayed^ game in this->individualGamesList)
	{
		// will return a string of game results, and tac it into the string list
		individualResult = getGameResults(game);
		individualGameStrings->Add(individualResult);
	}


	// then average stuff out for the whole session, using individualGamesList

	// then pull in historical data and average out some more (FOR NEXT SEMESTER)

	// then cat all the strings together in the desired order, and send back!
	// string results have been held in different arrays so they can be rearranged as desired at the end here.  

	ReleaseMutex(myMutex);
	return finalString;
}
//----------------------------------------------------------------------------------------------------------

// find all games of given type in game list and average the scores
// return in a faux GamePlayed^ instance
GamePlayed^ ScoreKeeping::calculateAveragesByGameType(System::String^ gameType)
{
	// hmm should actually be for game board, not type, if I want to be able to find info about pieces
	for each (GamePlayed^ game in this->individualGamesList) {
		System::String^ listedType = game->getType();
		if (listedType->Equals(gameType)) {
			// here we go off and average the scores
		}
	}
	GamePlayed^ result = gcnew GamePlayed(); //tmp
	return result;
}
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
