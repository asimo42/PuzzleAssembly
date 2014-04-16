/* 
	Definitions for functions belonging to the GamePlayed, GamePlayedData, and ScoreKeeping classes
*/

#include "stdafx.h"
//#include <Windows.h>
//#include <string>
//#include <stack>
//#include <process.h>
//#using <System.dll>
//#include <stdio.h>
#include "Functions.h"
#include "GameBoard.h"

using namespace System;
using namespace System::Collections::Generic;

void GamePlayed::Initialize() 
{
	this->gameType = "Unknown";
	this->gameName = "Unknown";
	this->player = "Unknown";
	this->timesOfPlacement = gcnew List<int>();
	this->orderOfPiecesPlayed = gcnew List<System::String^>();
	this->avgTimeBetweenPieces = 0;
	this->timeForCompletion = 0;
	this->game = gcnew KnobPuzzle();
	this->ALREADY_COMPILED = false;
	this->gameData = gcnew GamePlayedData();
	this->NOT_COMPLETED = false;
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
	// this->game's knobpuzzle outside of GamePlayed. All data variables should be set once when the game is completed and not touched again
	// if game has already been compiled, return. The KnobPuzzle reference might have changed since then - dangerous. 
	if (ALREADY_COMPILED) {
		Console::WriteLine("GamePlayed.cpp::compileData():: Error - GamePlayed instance has already been compiled - can't change");
		return;
	}
	this->game = Puzzle;
	this->gameType = Puzzle->getType();
	this->gameName = Puzzle->getName();
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

	// pull level of difficulty
	this->levelOfDifficulty = this->game->getLevelOfDifficulty();

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
	// set 'already compiled' to true, so that data can never be compiled again. From hereonout, the gameData instance will be returned.
	ALREADY_COMPILED = true;
	this->game = gcnew KnobPuzzle(); // destroy reference to the input KnobPuzzle just in case
	this->game->setError();
	this->gameData = gcnew GamePlayedData(this);
	return 0;
}
//----------------------------------------------------------------------------------------------------------
// if the game was ended early, void out unplaced pieces instead of compiling the data
void GamePlayed::gameEndedEarly() {

	this->NOT_COMPLETED = true;

	List<int>^ timesPlaced = gcnew List<int>();
	Dictionary< System::String^, int >^ pieceDict= gcnew Dictionary< System::String^, int >();
	int tim = 0;
	Console::WriteLine("GamePlayed::gameEndedEarly(): negating time placed information for pieces not placed");
	for each (PuzzlePiece^ piece in this->game->getPieceList()) {
		if (!piece->isPlaced) {
			timesPlaced->Add(-1);
			Console::WriteLine(piece->getName() + "   : NOT PLACED");
			continue;
		}
		// calc seconds between beginning of game and when piece was placed
		tim = secondsBetweenTwoDateTimes(this->timeStarted, piece->getTimePlaced()); 
		Console::WriteLine(piece->getName() + "   : " + tim);
		timesPlaced->Add(tim);
		pieceDict->Add(piece->getName(),tim); // add piece and time to dictionary 
	}
}


//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------


//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------

// GAMEPLAYED DATA
//----------------------------------------------------------------------------------------------------------

GamePlayedData::GamePlayedData() {
	Initialize();
}
//----------------------------------------------------------------------------------------------------------
GamePlayedData::GamePlayedData(GamePlayed^ inputGame) {

	// clear everything out real quick
	Initialize();
	this->NOT_COMPLETED = inputGame->NOT_COMPLETED;

	// copy all data over from GamePlayed^ instance
	this->playerName = inputGame->getPlayer();
	this->gameName = inputGame->getName();
	this->levelOfDifficulty = inputGame->getLevelOfDifficulty();

	DateTime timeStarted = inputGame->getTimeStarted();
	this->month = timeStarted.ToString("MMMM");
	this->day = timeStarted.Day.ToString();
	this->year = timeStarted.Year.ToString();
	this->seconds = timeStarted.Second.ToString();
	this->minutes = timeStarted.Minute.ToString();
	this->hours = timeStarted.Hour.ToString();

	// if the game was not completed, return here, with just the basic start information
	if (this->NOT_COMPLETED) {
		this->isSet = true;
		return;
	}

	this->averageTimeBetweenPieces = inputGame->getAverageTimeBetweenPieces();
	this->timeForCompletion = inputGame->getTimeForCompletion();

	this->timesOfPlacement = inputGame->getTimesOfPlacement();
	this->timeBetweenPlacements = inputGame->getTimesBetweenPlacements();
	this->orderOfPiecesPlayed = inputGame->getOrderOfPiecesPlayed();

	// all set, so be done!
	this->isSet = true;

}
//----------------------------------------------------------------------------------------------------------
// set up all the containers
void GamePlayedData::Initialize() {

	this->isSet = false;
	this->NOT_COMPLETED = false;
	playerName = "";	gameName = "";	levelOfDifficulty = 0;
	averageTimeBetweenPieces = 0; 	timeForCompletion = 0;

	List<int>^ timesOfPlacement = gcnew List<int>(); 
	List<int>^ timeBetweenPlacements = gcnew List<int>(); 
	List<System::String^>^ orderOfPiecesPlayed = gcnew List<System::String^>(); 

	// the following refer to the time the game was started
	month = "";	day = ""; year = ""; seconds = "";	minutes = ""; hours = "";
}
//----------------------------------------------------------------------------------------------------------
System::String^ GamePlayedData::writeOut() {

	if (!this->isSet) {
		Console::WriteLine("GamePlayedData::writeOut(): data hasn't been set yet");
		return "Error";
	}
	if (this->NOT_COMPLETED) {
		Console::WriteLine("GamePlayedData::WriteOut(): Error : game was not completed");
		System::String^ resultString = "";
		resultString = "Player : " + this->playerName + Environment::NewLine + "Game : " + this->gameName + Environment::NewLine;
		System::String^ tim = day + " " + month  + " " + year + " "  + hours + ":" + minutes; 
		resultString = resultString + "Time Started : " + tim + Environment::NewLine;
		resultString = resultString + "GAME NOT COMPLETED";
		return resultString; 
	}

	System::String^ resultString = "";
	resultString = "Player : " + this->playerName + Environment::NewLine + "Game : " + this->gameName + Environment::NewLine;
	resultString = resultString + "Level of Difficulty : " + this->levelOfDifficulty + Environment::NewLine;
	System::String^ tim = day + " " + month  + " " + year + " "  + hours + ":" + minutes; 
	resultString = resultString + "Time Started : " + tim + Environment::NewLine;
	resultString = resultString + "Time for Completion (s): " + this->timeForCompletion+ Environment::NewLine;
	resultString = resultString + "Average Time Between Pieces: " + this->averageTimeBetweenPieces + Environment::NewLine + Environment::NewLine;
	for (int i = 0; i < this->orderOfPiecesPlayed->Count; i++) 
	{ 
		System::String^ val1 = "Piece : " + this->orderOfPiecesPlayed[i] + Environment::NewLine;
		System::String^ val2 = "         Time of Placement (s) :    " + this->timesOfPlacement[i] + Environment::NewLine;
		System::String^ val3 = "         Time it Took to Place (s) : " + this->timeBetweenPlacements[i] + Environment::NewLine;
		resultString = resultString + System::String::Format("{0}{1}{2}", val1, val2, val3);
	}

	return resultString;
}
//----------------------------------------------------------------------------------------------------------
// output file for saved performance data will be labeled: mainpath/PlayerName/PlayerName_GameName_YYYY_MMMM_dd.txt
System::String^ GamePlayedData::buildFileName() {
	if (!isSet) {
		return "Error";
	}
	System::String^ mainString = buildOutputFileName(playerName, gameName, month, day, year);

	return mainString;

}
//----------------------------------------------------------------------------------------------------------
int GamePlayedData::Save() 
{
	// build file name to save to
	System::String^ outputFile = this->buildFileName();
	System::Windows::Forms::MessageBox::Show(outputFile);

	// pull results for this game
	System::String^ finalResults = this->writeOut();
	if (finalResults->Contains("Error")) { return -1; }
	// check if there is already results for that day. If so, append data
	if (System::IO::File::Exists(outputFile)) {
		Console::WriteLine("GamePlayedData::Save(): appending lines to file");
		// add a couple spaces before new results for padding
		finalResults = "\r\n\r\n" + finalResults;
		array<System::String^>^ tmpArray = gcnew array<System::String^>(1); 
		tmpArray[0] = finalResults;
		// append new data to existing file
		int success = appendStringArrayToFile(tmpArray, outputFile);
	}
	// if file doesn't exist yet, create new file with a brief header and put the data there
	if (!System::IO::File::Exists(outputFile)) {
		// pull today's date and construct a header string for the file, with date and Player's name
		DateTime today = DateTime::Now.ToLocalTime();
		System::String^ introString = "Player: " + this->playerName + "\r\nSession: " + month + " " + day + ", " + year + " " + hours + Environment::NewLine;
		// put both strings in an array to write out to file
		array<System::String^>^ tmpArray = gcnew array<System::String^>(2);
		tmpArray[0] = introString; tmpArray[1] = finalResults;
		int success = writeStringArrayToFile(tmpArray, outputFile);
		if (success != 0) {
			Console::WriteLine("GamePlayedData::Save(): Error - couldn't write output to file " + outputFile);
			return -1;
		}
	}
	return 0;
}








//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------


//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------//-------------------------------------

// SCOREKEEPING





// Initialize a blank scorekeeper
//----------------------------------------------------------------------------------------------------------
ScoreKeeping::ScoreKeeping() {
	this->individualGamesList = gcnew List<GamePlayedData^>();
}

//----------------------------------------------------------------------------------------------------------
// return a string for printing out all results, to be displayed from the GUI.  
System::String^ ScoreKeeping::showFinalResults() 
{
	System::String^ finalString = "Performance and Progress\n\n";

	List<System::String^>^ individualGameStrings = gcnew List<System::String^>();  // to hold each game's result string
	System::String^ individualResult = "";

	// print the results for each game and then tack them all together
	for each (GamePlayedData^ game in this->individualGamesList)
	{
		individualResult = game->writeOut();
		if (!individualResult->Contains("Error")) {individualGameStrings->Add(individualResult); }
	}
	finalString = finalString + System::String::Join("\n", individualGameStrings);

	return finalString;
}
//----------------------------------------------------------------------------------------------------------
//// find all of certain game in game list and average the scores
//// return in a faux GamePlayed^ instance
//// technically we don't need matching yet, since we will always be playing the same game
//GamePlayed^ ScoreKeeping::calculateAverageForGame(System::String^ gameName)
//{
//	List<GamePlayed^>^ matchingGames = gcnew List<GamePlayed^>();
//	//for each (GamePlayed^ game in this->individualGamesList) {
//		//System::String^ listedName = game->game->puzzleName();
//		//if (listedName->Equals(gameName)) {
//		//	matchingGames->Add(game);
//		//}
//	//}
//	// if num games is 0 or 1, take the easy route
//	GamePlayed^ result = gcnew GamePlayed(); 
//	//if (matchingGames->Count == 0) {
//	//	return result;
//	//}
//	//if (matchingGames->Count == 1) {
//	//	return matchingGames[0];
//	//}
//
//	//System::String^ pieceName = "";
// //   Dictionary<System::String^, List<int>^>^ dict = gcnew Dictionary<System::String^, List<int>^>();
//	//// otherwise, start averaging via dictionary
//	//for each (GamePlayed^ game in matchingGames) {
//	//	for (int i = 0; i < game->orderOfPiecesPlayed->Count; i++) {
//	//		pieceName = game->orderOfPiecesPlayed[i];
//	//		if (!dict->ContainsKey(pieceName)) { 
//	//			dict[pieceName] = gcnew List<int>();
//	//			dict[pieceName][0] = game->timesBetweenPieces
//
//
//	//	}
//	//}
//
//	return result;
//}
//
//
//////----------------------------------------------------------------------------------------------------------
