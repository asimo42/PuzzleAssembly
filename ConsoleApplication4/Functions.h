#include "stdafx.h"
#include <opencv2\opencv.hpp>	
#include "HandleVariables.h"
#include "TrackedPiece.h"
#include "PuzzlePiece.h"
#include "Shape.h"
#include "GameBoard.h"
#include "ScoreKeeping.h"
#include "TrackedPiece.h"

#ifndef GUARD_J
#define GUARD_J

using namespace System::Collections::Generic;

// define any constants that will be repeated across multiple files/functions
// or is changeable
class Constants {
public:

	static const int TESTNUMBER = 0;	// chose a test number to run
	static const bool LAURA = false;     // if LAURA == true, 'findcontours' will be skipped in the tracking function

	// location of Laura's codefile (feel free to comment out and add your own if you ever use it)
	//static const std::string CODEFILE = 
	//	"C:/Users/Owner/Documents/401- Senior Design/PuzzleAssembly/PuzzleAssembly/ConsoleApplication4/TestInputForKnobPuzzle.txt";
	// crap this isn't compiling for some reason
};


// starting OpenCV
//int initializeTracking(HandleVariables^ %handleVars, KnobPuzzle^ %Game);
int initializeTracking(HandleVariables^ %handleVars, KnobPuzzle^ %Game, ScoreKeeping^ %ScoreKeeper);

System::String^ searchPuzzleType(System::String^ code);
array<System::String^>^ getCodeStrings(System::String^ code); 
int getCodeLocation(array<System::String^>^ lines, System::String^ code);
std::string intToStdString(int number);
System::String^ stdStringToSystemString(std::string str);
std::string systemStringToStdString(System::String^ str);
int getElapsedSeconds(long startTime);

// OPENCV <--> MANAGED Conversions
List<int>^ scalarToList(cv::Scalar scalar);

// from Tracking.cpp
void on_trackbar( int, void* );  // this one won't compile as part of RunTracking - no idea why


// from logging.cpp
void writeToLog(System::String^ myMessage);




#endif
