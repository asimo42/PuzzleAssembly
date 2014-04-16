#pragma once 

#include "stdafx.h"

#include <opencv2\opencv.hpp>	
#include "TrackedPiece.h"
#include "PuzzlePiece.h"
#include "GameBoard.h"
#include "ScoreKeeping.h"

#ifndef GUARD_J
#define GUARD_J

using namespace System;
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

	// shape drawing stuff
	static const int BACKGROUND_COLOR = 60;
	static const int SHAPE_LINE_WIDTH = 15;

	// Hardcoded file paths
	static System::String^ GAME_INPUT_DIRECTORY = System::Windows::Forms::Application::StartupPath + "/../";
	static System::String^ HELP_FILE = System::Windows::Forms::Application::StartupPath + "/../Help.txt";
	static System::String^ CALIBRATION_HELP_FILE = System::Windows::Forms::Application::StartupPath + "/../CalibrationHelp.txt";
	static System::String^ RESULTS_DIRECTORY = System::Windows::Forms::Application::StartupPath + "/PatientPerformanceData/";

};


//--- FROM FUNCTIONS.CPP----

// Start up a game using RunTracking
GamePlayedData^ initializeTracking(KnobPuzzle^ %Game, System::String^ userName);

// display the puzzle board background
cv::Mat displayPuzzleBoard(cv::Mat matName, vector<TrackedPiece>);

// Unmanaged <--> Managed Conversions
List<int>^ scalarToList(cv::Scalar scalar);
TrackedPiece puzzlePieceToTrackedPiece(PuzzlePiece^ puzzlePiece);
PuzzlePiece^ trackedPieceToPuzzlePiece(TrackedPiece trackedPiece);

// Game code input/puzzle class functions
System::String^ searchPuzzleType(System::String^ code);
array<System::String^>^ getStringArrayFromFile(System::String^ inputFile); 
int checkOrCreateFile(System::String^ fileName);
int writeStringArrayToFile(array<System::String^>^ inputArrray, System::String^ fileName);
int appendStringArrayToFile(array<System::String^>^ inputArray, System::String^ fileName);

System::String^ getCalibratedInputPath(System::String^ code);
System::String^ getDefaultInputPath(System::String^ code);

// Timekeeping
int secondsBetweenTwoDateTimes(DateTime startTime, DateTime endTime);
//double getElapsedSeconds(long startTime);

// performance data IO
List<System::String^>^ findRecordFiles(System::String^ player, System::String^ game, array<System::String^>^ days);
GamePlayed^ fileLinesToGamePlayed(array<System::String^>^ fileLines);
System::String^ buildOutputFileName(System::String^ player, System::String^ game, System::String^ month, System::String^ day, System::String^ year);

// Miscellaneous
std::string intToStdString(int number);
System::String^ stdStringToSystemString(std::string str);
std::string systemStringToStdString(System::String^ str);
double averageListOfInts(List<int>^ inputList);

// workaround hack to declare a thread as a global variable in a form
ref class ThreadShell {
public: 
	ThreadShell() { Started = false; }
	bool Started;
	System::Threading::Thread^ myThread;
};

// ---FROM TRACKING.CPP----

void on_trackbar( int, void* );  // this one won't compile as part of RunTracking - no idea why


#endif
