#include "stdafx.h"

#include "Functions.h"
#include "RunTracking.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace cv;

//----------------------------------------------------------------------------------------------------------

// Start tracking via a RunTracking instance, and then return the results of the game. Currently only designed for a KnobPuzzle game
GamePlayedData^ initializeTracking(KnobPuzzle^ %Game, System::String^ userName)
{
	GamePlayedData^ gameResults = gcnew GamePlayedData();
	// Initialize OpenCV running class (RunTracking) and load with puzzle
	{
		RunTracking* newTracker = new RunTracking();
		newTracker->setGame(Game);
		newTracker->setPlayer(userName);
		int success = newTracker->Start();

		// if the game had an error, return an empty GamePlayedData
		if (success != 0) {
			Console::WriteLine("Functions::initializeTracking():: the tracker returned an error.");
			delete newTracker;
			return gameResults;
		}

		// Once game is over, pull the game results
		gameResults = newTracker->returnScore()->getGameData();

		// add game results to main scorekeeper instance. Show game results.
		System::String^ results = gameResults->writeOut();	
		if (results->Contains("Error")) {
			delete newTracker;
			return gameResults;
		}

		MessageBox::Show(results);

		// see if user wants to save results
		System::Windows::Forms::DialogResult dialogResult = MessageBox::Show("Save game results for " + userName + "?", "Warning", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);
		// if user says yes, save the settings to the hardcoded location (user doesn't select)
		if(dialogResult == System::Windows::Forms::DialogResult::Yes)
		{
			gameResults->Save();
		}

		delete newTracker;
	}
	return gameResults;
}
//----------------------------------------------------------------------------------------------------------

// match the game code to the type (as a string). Simple matching; game code should always have game type in it
System::String^ searchPuzzleType(System::String^ code)
{
	System::String^ type = "";
	// Here I would search some database/list sort of thing for the type of puzzle. Or it starts the code.  Ex.
	if (code->Contains("KNOBPUZZLE")) { // tehcnically only knobpuzzles work for the current iteration of the system
		type = gcnew System::String("KnobPuzzle");
	}
	if (code->Contains("BLOCKPUZZLE")) {
		type = gcnew System::String("BlockPuzzle");
	}
	if (code->Contains("SNAKE")) {
		type = gcnew System::String("Snake");
	}
	return type;
}


//----------------------------------------------------------------------------------------------------------
// chunk together calibrated input path or default input path
System::String^ getCalibratedInputPath(System::String^ code) { 
				System::String^ str = Constants::GAME_INPUT_DIRECTORY + code + ".txt"; 
				return str; }
System::String^ getDefaultInputPath(System::String^ code) { 
				System::String^ str = Constants::GAME_INPUT_DIRECTORY + code + "_Default" + ".txt"; 
				return str; }

//----------------------------------------------------------------------------------------------------------
// Pull all strings from a file into an array of System::Strings^
array<System::String^>^ getStringArrayFromFile(System::String^ inputFile) {

	array<System::String^>^ lines;
	if (System::IO::File::Exists(inputFile)) { Console::WriteLine("Functions: getStringArrayFromFile(): Found File: \n" + inputFile); }
	else {
		lines[0] = gcnew System::String("ERROR");
		return lines;
	}
	// Read in all lines of file into an array 'lines'
	try {
		lines = System::IO::File::ReadAllLines(inputFile);
		Console::WriteLine("getStringArrayFromFile(): Reading in input file \n" + inputFile); 
	}
	// return error if there's a problem
	catch (System::Exception^ e) {
		Console::WriteLine("getStringArrayFromFile(): Error reading input file: \n" + inputFile);
		System::Diagnostics::Debug::WriteLine(e);
		Console::WriteLine(e);
		lines = gcnew array<System::String^>(1);
		lines[0] = gcnew System::String("ERROR");
		return lines;
	}
	return lines;

}
//---------------------------------------------------------------------------------------------------------
// quick function to see if a file already exists. If it doesn't, try to create it. 
int checkOrCreateFile(System::String^ fileName) {
	// if file doesn't exist yet, create it
	if (!System::IO::File::Exists(fileName)) {
		try { 
			System::IO::FileStream^ fs = System::IO::File::Create(fileName); 
			fs->Close();
		}

		catch (System::Exception^ e) {
			Console::WriteLine("checkOrCreateFile(): Error creating file " + fileName);
			return -1; 
		}
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------
// append an array of strings to a file
int appendStringArrayToFile(array<System::String^>^ inputArray, System::String^ fileName) {

	// make sure file is created
	if (checkOrCreateFile(fileName) != 0) {
		Console::WriteLine("writeStringArrayToFile(): file was not created : " + fileName);
		return -1;
	}

    // Add all new text onto end of file
    try 
    {
         System::IO::File::AppendAllLines(fileName, inputArray);
    }
	catch (System::Exception^ e)
	{
		System::Diagnostics::Debug::WriteLine(e);
		Console::WriteLine("writeStringArrayToFile(): Error - can't write lines to file:");
		Console::WriteLine(e);
		return -1;
	}

	return 0;
}
//----------------------------------------------------------------------------------------------------------
// write an array of strings to a given file 
int writeStringArrayToFile(array<System::String^>^ inputArray, System::String^ fileName) {

	// make sure file is created
	if (checkOrCreateFile(fileName) != 0) {
		Console::WriteLine("writeStringArrayToFile(): file was not created : " + fileName);
		return -1;
	}

    // Write all lines to file
    try 
    {
         System::IO::File::WriteAllLines(fileName, inputArray);
    }
	catch (System::Exception^ e)
	{
		System::Diagnostics::Debug::WriteLine(e);
		Console::WriteLine("writeStringArrayToFile(): Error - can't write lines to file:");
		Console::WriteLine(e);
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------
// convert an integer into a std::string
std::string intToStdString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}
//----------------------------------------------------------------------------------------------------------

// convert std::string to System::String^
System::String^ stdStringToSystemString(std::string str) {
	System::String^ MyString = gcnew System::String(str.c_str());
	return MyString;
}
//----------------------------------------------------------------------------------------------------------

// convert System::String^ to std::string
std::string systemStringToStdString(System::String^ str)
{
	if (str->Equals("")) {
		return "";
	}
     using System::Runtime::InteropServices::Marshal;
     System::IntPtr pointer = Marshal::StringToHGlobalAnsi(str);
     char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
     std::string returnString(charPointer, str->Length);
     Marshal::FreeHGlobal(pointer);
     return returnString;
}

//----------------------------------------------------------------------------------------------------------

// take average of a list of ints. If no integers given, will return 0
double averageListOfInts(List<int>^ inputList) {
	double sum = 0;
	for each (int num in inputList) {
		sum += num;
	}
	if (inputList->Count != 0) {	
		double average = sum/inputList->Count;
		return average;
	}
	else { return 0; }
}

//----------------------------------------------------------------------------------------------------------
// convert a cv::scalar into a list of 3 ints (for use in managed code)
List<int>^ scalarToList(cv::Scalar scalar) {
	List<int>^ myList = gcnew List<int>(0);
	myList->Add(scalar[0]); myList->Add(scalar[1]); myList->Add(scalar[2]);
	return myList;
}
//----------------------------------------------------------------------------------------------------------

//// get elapsed seconds from a start time based on number of DateTime ticks
//double getElapsedSeconds(long startTime) {
//	DateTime tim = DateTime::Now;
//	long placeTime = tim.Ticks - startTime; // 10,000 ticks in a millisecond, 1000 milliseconds in a second
//	TimeSpan^ elapsed = gcnew TimeSpan(placeTime);
//	return elapsed->TotalSeconds;
//}

//----------------------------------------------------------------------------------------------------------

// get elapsed seconds between two DateTimes
int secondsBetweenTwoDateTimes(DateTime startTime, DateTime endTime) {
	TimeSpan span = endTime.Subtract(startTime);
	return span.Seconds;
}

//----------------------------------------------------------------------------------------------------------
// Convert a managed PuzzlePiece to an unmanaged TrackedPiece
TrackedPiece puzzlePieceToTrackedPiece(PuzzlePiece^ puzzlePiece) {
	// pull name
	System::String^ name = puzzlePiece->getName();
	// Puzzle piece HSV lists go [H, S, V]
	int H_min = puzzlePiece->getHSVmin()[0];
	int H_max = puzzlePiece->getHSVmax()[0];
	int S_min = puzzlePiece->getHSVmin()[1];
	int S_max = puzzlePiece->getHSVmax()[1];
	int V_min = puzzlePiece->getHSVmin()[2];
	int V_max = puzzlePiece->getHSVmax()[2];
	// create new Tracked Piece with these results and return
	TrackedPiece result = TrackedPiece(systemStringToStdString(name), Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max),puzzlePiece->getXDest(),puzzlePiece->getYDest());

	// set all drawing data
	result.setShapePoint(puzzlePiece->getShapePointX(), puzzlePiece->getShapePointY()); 
	if (name->Equals("Square") || name->Equals("Rectangle")) 
			{ result.setShapeWidth(puzzlePiece->getShapeWidth()); }
	if (name->Equals("Rectangle"))                           
			{ result.setShapeHeight(puzzlePiece->getShapeHeight()); }
	if (name->Equals("Pentagon") || name->Equals("Triangle"))	
			{ result.setShapeLength(puzzlePiece->getShapeLength()); }
	if (name->Equals("Circle")) 
			{ result.setShapeRadius(puzzlePiece->getShapeRadius()); }

	return result;
}
//----------------------------------------------------------------------------------------------------------
// Convert a managed PuzzlePiece to an unmanaged TrackedPiece
PuzzlePiece^ trackedPieceToPuzzlePiece(TrackedPiece trackedPiece) {
	// pull name
	std::string name = trackedPiece.getName();
	// Tracked piece HSV scalars go [H, S, V]
	int H_min = trackedPiece.getHSVmin()[0];
	int H_max = trackedPiece.getHSVmax()[0];
	int S_min = trackedPiece.getHSVmin()[1];
	int S_max = trackedPiece.getHSVmax()[1];
	int V_min = trackedPiece.getHSVmin()[2];
	int V_max = trackedPiece.getHSVmax()[2];
	List<int>^ HSV_min;
	List<int>^ HSV_max;
	// recreate HSV list<int>^s
	HSV_min->Add(H_min); HSV_min->Add(S_min); HSV_min->Add(V_min);
	HSV_max->Add(H_max); HSV_max->Add(S_max); HSV_max->Add(V_max);
	// create new Puzzle Piece with these results and return
	PuzzlePiece^ result = gcnew PuzzlePiece(stdStringToSystemString(name), HSV_min, HSV_max, trackedPiece.getXDest(), trackedPiece.getYDest());

	// set all drawing data
	result->setShapePoint(trackedPiece.getShapePointX(), trackedPiece.getShapePointY()); 
	if (name == "Circle") { result->setShapeRadius(trackedPiece.getShapeRadius()); }
	if (name == "Square" || name == "Rectangle") { result->setShapeWidth(trackedPiece.getShapeWidth()); }
	if (name == "Rectangle") { result->setShapeHeight(trackedPiece.getShapeHeight()); }
	if (name == "Pentagon" || name == "Triangle" ) { result->setShapeLength(trackedPiece.getShapeLength()); }

	return result;
}
//----------------------------------------------------------------------------------------------------------
// build the path to the performance data file for a given player, game and date
System::String^ buildOutputFileName(System::String^ player, System::String^ game, System::String^ month, System::String^ day, System::String^ year) {
	// build path
	System::String^ pathStr = Constants::RESULTS_DIRECTORY + player + "\\";
	// build filename
	System::String^ fileStr = player + "_" + game + "_" + year + "_" + month + "_" + day + ".txt";
	System::String^ mainString = pathStr + fileStr;
	return mainString;
}

//----------------------------------------------------------------------------------------------------------
// find all files matching the given player, game, and date
List<System::String^>^ findRecordFiles(System::String^ player, System::String^ game, array<System::String^>^ days) {

	// find player's results directory
	List<System::String^>^ results = gcnew List<System::String^>();
	System::String^ dirPath = Constants::RESULTS_DIRECTORY + player;
	if (!System::IO::Directory::Exists(dirPath)) {
		Console::WriteLine("Functions::findRecordFiles():: could not find directory for " + player);
		return results;
	}

	System::String^ delimStr = "_";
	array<Char>^ delimiter = delimStr->ToCharArray( );
	System::String^ month; System::String^ da; System::String^ year;

	// construct each file path for each date and check if the file exists
	for each (System::String^ day in days) {
		array<System::String^>^ tokens = day->Split(); // break up date string
		if (tokens->Length < 3) { 
			Console::WriteLine("Functions::findRecordFiles():: date incorrectly formatted : " + day);
			continue; }  // if there aren't 3 parts (month day year) to date, continue
		month = tokens[0];
		da = tokens[1];
		year = tokens[2];
		
		// reconstruct file path
		System::String^ finalPath = buildOutputFileName(player, game, month, da, year); 
			Console::WriteLine("Functions::findRecordFiles():: looking for file " + finalPath);
		// check if it exists
		if (System::IO::File::Exists(finalPath)) {   // check if it exists
			Console::WriteLine("Functions::findRecordFiles():: found file " + finalPath);
			results->Add(finalPath);
		}
	}
	return results;
}
//----------------------------------------------------------------------------------------------------------
// Parse given file lines into a GamePlayed^ instance
GamePlayed^ fileLinesToGamePlayed(array<System::String^>^ fileLines) {

	GamePlayed^ result = gcnew GamePlayed();

		System::String^ line = fileLines[0];
		System::String^ gameName = "";
		System::String^ playerName = "";
		System::String^ timeForCompletion;
		System::String^ averageTimeForPieces;
		System::String^ month;
		System::String^ year;
		System::String^ day;
		System::String^ tim;
		List<System::String^>^ pieceNames = gcnew List<System::String^>();
		List<System::String^>^ timesToPlace = gcnew List<System::String^>();
		List<System::String^>^ timesOfPlacement = gcnew List<System::String^>();

		int index = 0;
		while(index < fileLines->Length) {
			line = fileLines[index++]; 
			Console::WriteLine(line);
			if (line->Contains("Game:")) {
				array<System::String^>^ tokens = line->Split();
				gameName = tokens[-1];
			}
			if (line->Contains("Player:") ) {
				array<System::String^>^ tokens = line->Split();
				playerName = tokens[-1];
			}
			if (line->Contains("Time for Completion (s):")) {
				array<System::String^>^ tokens = line->Split();
				timeForCompletion = tokens[-1];
			}
			if (line->Contains("Average Time")) {
				array<System::String^>^ tokens = line->Split();
				averageTimeForPieces = tokens[-1];
			}
			if (line->Contains("Time Started:")) {
				array<System::String^>^ tokens = line->Split();
				tim = tokens[-1];
				year = tokens[-2];
				day = tokens[-3];
				month = tokens[-4];
			}
			if (line->Contains("Piece")) {
				// pull piece name
				array<System::String^>^ tokens = line->Split();
				pieceNames->Add(tokens[-1]);
				// move ot next line and pull time of placement
				line = fileLines[index++]; 
				tokens = line->Split();
				timesOfPlacement->Add(tokens[-1]);
				// move to next line and pull time to place
				line = fileLines[index++]; 
				tokens = line->Split();
				timesToPlace->Add(tokens[-1]);
			}
		}
		return result;
}

// construct and display the puzzle board background using the vector of TrackedPieces
cv::Mat displayPuzzleBoard(cv::Mat matName, vector<TrackedPiece> pieces) {

	Shape shapes;
	shapes.setImage(&matName);
	shapes.Clear_To_Black(); // Must clear to black first, otherwise get exception
	shapes.Clear_To_Gray();	// then turn it all gray
	// now draw out each piece
	for (unsigned int i = 0; i < pieces.size(); i++)
	{
		shapes.Draw_Shape(pieces[i], 1);
	}
	return matName;
}