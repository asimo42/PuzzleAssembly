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

// Define any constants that will be repeated or that may be changed. EX) int x = Constants::CONSTANT_X
ref class Constants {
public:
	static const int TESTNUMBER = 0;	// chose a test number to run. 0 = not a test

	//OPENCV related defaults ---

	//OpenCV default capture width and height
	static const int DEFAULT_FRAME_WIDTH = 640;
	static const int DEFAULT_FRAME_HEIGHT = 480;
	
    //max number of objects to be detected in frame
    static const int DEFAULT_MAX_OBJECTS_IN_FRAME =20;
    //minimum and maximum object area
    static const int DEFAULT_MIN_OBJECT_AREA = 2500;

	// HSV default values (0-256)
    static const int DEFAULT_H_MIN = 0;
    static const int DEFAULT_H_MAX = 256;
    static const int DEFAULT_S_MIN = 0;
    static const int DEFAULT_S_MAX = 256;
    static const int DEFAULT_V_MIN = 0;
    static const int DEFAULT_V_MAX= 256;

	// don't worry about this path yet; I hardcoded it's contents in "Functions.cpp getGameFileStrings()" for now
	static System::String^ GAME_INPUT_FILE = "C:/Users/Owner/Documents/401- Senior Design/PuzzleAssembly/PuzzleAssembly/ConsoleApplication4/TestInputForKnobPuzzle.txt";
;
};


//--- FROM FUNCTIONS.CPP----

// starting OpenCV
void initializeTracking(HandleVariables^ %handleVars, KnobPuzzle^ %Game, ScoreKeeping^ %ScoreKeeper);

// Unmanaged <--> Managed Conversions
List<int>^ scalarToList(cv::Scalar scalar);

// game code input/puzzle class functions
System::String^ searchPuzzleType(System::String^ code);
array<System::String^>^ getGameFileStrings(System::String^ code); 
int getCodeLocation(array<System::String^>^ lines, System::String^ code);

// misc.
std::string intToStdString(int number);
System::String^ stdStringToSystemString(std::string str);
std::string systemStringToStdString(System::String^ str);
double getElapsedSeconds(long startTime);



// ---FROM TRACKING.CPP----

void on_trackbar( int, void* );  // this one won't compile as part of RunTracking - no idea why



// from LOGGING.CPP (not currently used)----

void writeToLog(System::String^ myMessage);




#endif
