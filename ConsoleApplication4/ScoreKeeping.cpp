#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include "Functions.h"
#include "GameBoard.h"

using namespace System;
using namespace System::Collections::Generic;

void GamePlayed::Initialize() 
{
	this->gameType = "Unknown";
	this->timesOfPlacement = gcnew List<int>();
	this->orderOfPiecesPlayed = gcnew List<System::String^>();
	this->avgTimeBetweenPieces = 0;
	this->timeForCompletion = 0;
	this->game = gcnew KnobPuzzle();
	this->ALREADY_COMPILED = false;
}

GamePlayed::GamePlayed() 
{
	Initialize();
}
//----------------------------------------------------------------------------------------------------------

GamePlayed::~GamePlayed() 
{
}
//----------------------------------------------------------------------------------------------------------

GamePlayed::GamePlayed(KnobPuzzle^ Puzzle) 
{
	Initialize();
	setGame(Puzzle);
}
//----------------------------------------------------------------------------------------------------------

void GamePlayed::setGame(KnobPuzzle^ Puzzle)
{
	// the Input puzzle is just a reference, so it can be changed at any time. This means we should NEVER use 
	// this->game outside of GamePlayed. All data variables should be set once when the game is completed and not touched again
	// if game has already been compiled, return. The KnobPuzzle reference might have changed since then - dangerous. 
	if (ALREADY_COMPILED) {
		Console::WriteLine("GamePlayed.cpp::compileData():: Error - GamePlayed instance has already been compiled - can't change");
		return;
	}
	this->game = Puzzle;
	this->gameType = this->game->getType();
}
//----------------------------------------------------------------------------------------------------------
void GamePlayed::setStartTimeToNow() 
{
	//this->timeStarted = gcnew System::DateTime();
	this->timeStarted = this->timeStarted.Now;
}

//----------------------------------------------------------------------------------------------------------
void GamePlayed::setTimeCompletedToNow() 
{
	//this->timeCompleted = gcnew System::DateTime();
	this->timeCompleted = this->timeCompleted.Now;
}

//----------------------------------------------------------------------------------------------------------
// Call compileData() once directly after completing a game. It will compile the stats, and then prohibit any more changes to class data (read-only).
int GamePlayed::compileData()
{
	// if game has already been compiled, return. The KnobPuzzle reference might have changed since then - dangerous. 
	if (ALREADY_COMPILED) {
		Console::WriteLine("GamePlayed.cpp::compileData():: Error - tried to recompile GamePlayed Data");
		return -1;
	}
	// make sure the knobpuzzle was initialized 
	if (!this->game->checkIsInitialized()) {
		Console::WriteLine("GamePlayed.cpp::compileData():: Error - KnobPuzzle was never initialized in this GamePlayed instance.");
		return -1;
	}
	// check if the start time was successfully recorded
	if (this->timeStarted.Equals(DateTime::MinValue)) {
		Console::WriteLine("GamePlayed.cpp::compileData():: Error - Start time was never recorded for GamePlayed^ instance.");
		return -1;
	}

	// calculate seconds it took to finish the game
	this->timeForCompletion = secondsBetweenTwoDateTimes(this->timeStarted, this->timeCompleted);

	// find times placed information from puzzle pieces
	List<int>^ timesPlaced = gcnew List<int>();
	Dictionary< System::String^, int >^ pieceDict= gcnew Dictionary< System::String^, int >();
	int tim = 0;
	Console::WriteLine("Compiling Data: showing the times that each piece was placed");
	for each (PuzzlePiece^ piece in this->game->getPieceList()) {
		tim = secondsBetweenTwoDateTimes(this->timeStarted, piece->getTimePlaced()); // calc seconds between beginning of game and when piece was placed
		Console::WriteLine(piece->getName() + "   : " + tim);
		timesPlaced->Add(tim);
		pieceDict->Add(piece->getName(),tim); // add piece and time to dictionary (dictionary is for convenience for next step)
	}

	// make two lists to hold sorted time values, and their corresponding piece names
	List<System::String^>^ sortedKeys = gcnew List<System::String^>();
	List<int>^ sortedVals = gcnew List<int>();

	// sort times from smallest to largest
	for (int i = 0; i < timesPlaced->Count; i++) {
		System::String^ minStr = "";
		int minVal = 9999999;

		// find smallest time entry in dictionary
		for each (System::String^ key in pieceDict->Keys) {
			if (pieceDict[key] < minVal) {
				minStr = key;
				minVal = pieceDict[key];
			}
		}
		pieceDict->Remove(minStr); // remove piece from dictionary so that it isn't rerecorded
		sortedKeys->Add(minStr);
		sortedVals->Add(minVal);
	}
	this->orderOfPiecesPlayed = sortedKeys;
	this->timesOfPlacement = sortedVals;

	// now use sorted values to make a 3rd list - the times between each piece and the one before it
	List<int>^ timesBetweenPieces = gcnew List<int>();
	int temp = 0;
	for each (int tim in sortedVals) {
		timesBetweenPieces->Add(tim - temp);
		temp = tim;
	}
	this->timeBetweenPlacements = timesBetweenPieces;

	// calculate average time taken between pieces
	this->avgTimeBetweenPieces = averageListOfInts(timesBetweenPieces);

	Console::WriteLine("Testing the sorted data:");
	for (int i = 0; i < sortedKeys->Count; i++) {
		Console::WriteLine(sortedKeys[i] + "   " + sortedVals[i] + "   time between placement: " + timeBetweenPlacements[i]);
	}
	// set 'already compiled' to true, so that data can never be compiled again.
	ALREADY_COMPILED = true;
	this->game = gcnew KnobPuzzle(); // destroy reference to the input KnobPuzzle just in case
	return 0;
}
//----------------------------------------------------------------------------------------------------------
 //NOT SURE WHERE TO PUT THIS YET
//System::String^ GamePlayed::printData()
//{
//	// if the order hasn't been calculated yet, neet to compile data
//	// wait, why not compile any potentially new data anyway?
//	//if (this->orderOfPiecesPlayed->Count == 0)
//	//{
//		compileData();
//		if (this->timesOfPlacement->Count < this->game->getPieceList()->Count) {
//			System::Windows::Forms::MessageBox::Show(" Not all pieces were placed");
//		}
//		if (this->orderOfPiecesPlayed->Count == 0) { return "game not completed"; }
//	//}
//	System::String^ resultString = "";
//	resultString = "Game : " + game->getName() + "\n";
//	System::String^ tim = this->timeStarted->ToString("F");
//	resultString = resultString + "Time Started : " + tim + "\n";
//	resultString = resultString + "Time for Completion : " + this->timeForCompletion + "\n";
//	resultString = resultString + "Average Time Between Pieces: " + this->avgTimeBetweenPieces + "\n";
//	for (int i = 0; i < this->game->getPieceList()->Count; i++) 
//	{ 
//		resultString = resultString + "Piece : " + this->orderOfPiecesPlayed[i] + 
//			"       Time Placed (sec) : " + this->timesOfPlacement[i] + "\n";
//	}
//
//	return resultString;
//}




// GAMEPLAYED

//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------

// SCOREKEEPING





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
	WaitForSingleObject(myMutex, INFINITE);

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
