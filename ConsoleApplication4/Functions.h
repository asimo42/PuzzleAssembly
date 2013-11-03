#include "stdafx.h"
#include "HandleFlags.h"
#include "HandleVariables.h"
#include "TrackedPiece.h"
#include <opencv2\opencv.hpp>	

#ifndef GUARD_J
#define GUARD_J

using namespace System::Collections::Generic;

// starting OpenCV
int initializeOpenCV(HandleVariables^ %handleVars, HandleFlags^ %Flags);

System::String^ searchPuzzleType(System::String^ code);
array<System::String^>^ getCodeStrings(System::String^ code); 
int getCodeLocation(array<System::String^>^ lines, System::String^ code);
std::string intToStdString(int number);
System::String^ stdStringToSystemString(std::string str);
std::string systemStringToStdString(System::String^ str);

// OPENCV <--> MANAGED Conversions
List<int>^ scalarToList(cv::Scalar scalar);


// From Tracking.cpp
void on_trackbar( int, void* );
void createTrackbarWindow();
void erodeAndDilate(cv::Mat &image);
std::string intToString(int number);
void drawObject(vector<TrackedPiece> pieces, cv::Mat &frame);
void trackFilteredObject(TrackedPiece piece, cv::Mat &cameraFeed, cv::Mat &threshold_image);
void trackTrackedPiece(TrackedPiece &piece, cv::Mat &camera_feed, cv::Mat &HSV_image, cv::Mat &threshold_image);
int startTrack();

#endif
