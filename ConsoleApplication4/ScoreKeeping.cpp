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
	this->timeStarted = gcnew System::DateTime;
	this->timeStarted = this->timeStarted->Now;
	//this->timesBetweenPieces = gcnew List<int>();
	this->timesOfPlacement = gcnew List<int>();
	this->orderOfPiecesPlayed = gcnew List<System::String^>();
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::setGame(KnobPuzzle^ Puzzle)
{
	this->game = Puzzle;
	this->gameType = "KnobPuzzle";
	this->timeStarted = gcnew System::DateTime;
	this->timeStarted = this->timeStarted->Now;
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::CalcAvgTimeBetweenPieces()
{
	int sum = 0;
	int newtime = 0;

	// calculate the average
	for (int i = 0; i < this->timesOfPlacement->Count; i++) {
		newtime = this->timesOfPlacement[i] - sum;
		sum += newtime;
	}
	double average = sum/this->timesOfPlacement->Count;
	this->avgTimeBetweenPieces = average;
	return;
}
//----------------------------------------------------------------------------------------------------------
void GamePlayed::findSortedTimes() {

	List<int>^ sortedList = gcnew List<int>();
	for each (PuzzlePiece^ piece in this->game->pieceList) {
		sortedList->Add(piece->timePlaced);
	}
	sortedList->Sort();
	this->timesOfPlacement = sortedList;

}
//----------------------------------------------------------------------------------------------------------
void GamePlayed::findOrderOfPieces() {
	List<System::String^>^ orderedList = gcnew List<System::String^>();
	for (int i = 0; i < this->timesOfPlacement->Count; i++) {
		for each (PuzzlePiece^ piece in this->game->pieceList) {
			if (piece->timePlaced == this->timesOfPlacement[i] && !orderedList->Contains(piece->getName())) { 
				orderedList->Add(piece->getName()); 
			}
		}
	}
	this->orderOfPiecesPlayed = orderedList;
}
//----------------------------------------------------------------------------------------------------------

// changing this to make it the order of completion
void GamePlayed::compileData()
{
	findSortedTimes();
	CalcAvgTimeBetweenPieces();
	findOrderOfPieces();
	return;
}
//----------------------------------------------------------------------------------------------------------

System::String^ GamePlayed::printData()
{
	if (this->orderOfPiecesPlayed->Count == 0)
	{
		compileData();
		if (this->orderOfPiecesPlayed->Count == 0) { return "game not completed"; }
	}
	System::String^ resultString = "";
	resultString = "Game : " + game->puzzleName + "\n";
	System::String^ tim = this->timeStarted->ToString("F");
	resultString = resultString + "Time Started : " + tim + "\n";
	resultString = resultString + "Time for Completion : " + this->timeForCompletion + "\n";
	resultString = resultString + "Average Time Between Pieces: " + this->avgTimeBetweenPieces + "\n";
	for (int i = 0; i < this->game->pieceList->Count; i++) 
	{ 
		resultString = resultString + "Piece : " + this->orderOfPiecesPlayed[i] + 
			"       Time Placed (sec) : " + this->timesOfPlacement[i] + "\n";
	}

	return resultString;
}


// Initialize a blank scorekeeper
//----------------------------------------------------------------------------------------------------------
ScoreKeeping::ScoreKeeping() {
	this->individualGamesList = gcnew List<GamePlayed^>();
}

//----------------------------------------------------------------------------------------------------------
// return a string for printing out all results, to be displayed from the GUI.  
// will calculate and all stats for individual games, the session, and through history (future addition)
System::String^ ScoreKeeping::showFinalResults() 
{
	// Lock thread
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "compiling results");
	System::String^ finalString = "Performance and Progress\n\n";

	// start off by getting the results for each individual game
	List<System::String^>^ individualGameStrings = gcnew List<System::String^>();  // to hold each game's result string
	System::String^ individualResult = "";

	// print the results for each game and then tack them all together
	for each (GamePlayed^ game in this->individualGamesList)
	{
		individualResult = game->printData();
		individualGameStrings->Add(individualResult);
	}
	finalString = finalString + System::String::Join("\n", individualGameStrings);

	// then average stuff out for the whole session, using individualGamesList


	// then pull in historical data and average out some more

	// then cat all the strings together in the desired order, and send back!
	// string results have been held in different arrays so they can be rearranged as desired at the end here.  

	// unlock thread and return final string
	ReleaseMutex(myMutex);
	return finalString;
}
//----------------------------------------------------------------------------------------------------------
// find all of certain game in game list and average the scores
// return in a faux GamePlayed^ instance
// technically we don't need matching yet, since we will always be playing the same game
GamePlayed^ ScoreKeeping::calculateAverageForGame(System::String^ gameName)
{
	List<GamePlayed^>^ matchingGames = gcnew List<GamePlayed^>();
	//for each (GamePlayed^ game in this->individualGamesList) {
		//System::String^ listedName = game->game->puzzleName();
		//if (listedName->Equals(gameName)) {
		//	matchingGames->Add(game);
		//}
	//}
	// if num games is 0 or 1, take the easy route
	GamePlayed^ result = gcnew GamePlayed(); 
	//if (matchingGames->Count == 0) {
	//	return result;
	//}
	//if (matchingGames->Count == 1) {
	//	return matchingGames[0];
	//}

	//System::String^ pieceName = "";
 //   Dictionary<System::String^, List<int>^>^ dict = gcnew Dictionary<System::String^, List<int>^>();
	//// otherwise, start averaging via dictionary
	//for each (GamePlayed^ game in matchingGames) {
	//	for (int i = 0; i < game->orderOfPiecesPlayed->Count; i++) {
	//		pieceName = game->orderOfPiecesPlayed[i];
	//		if (!dict->ContainsKey(pieceName)) { 
	//			dict[pieceName] = gcnew List<int>();
	//			dict[pieceName][0] = game->timesBetweenPieces


	//	}
	//}

	return result;
}


//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
