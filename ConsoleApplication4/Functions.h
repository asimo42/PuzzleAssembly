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
void on_trackbar( int, void* );
//void createTrackbarWindow();
//void erodeAndDilate(Mat &image);
//void drawObject(vector<TrackedPiece> pieces, Mat &frame);
//void  trackFilteredObject(TrackedPiece piece, Mat &cameraFeed, Mat &threshold_image);
//void  trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);

// from logging.cpp
void writeToLog(System::String^ myMessage);

#endif
