#include "stdafx.h"
#include "HandleFlags.h"
#include "HandleVariables.h"
#include "TrackedPiece.h"
#include <opencv2\opencv.hpp>	


#ifndef GUARD_J
#define GUARD_J

using namespace System::Collections::Generic;

// starting OpenCV
int initializeOpenCV(HandleVariables^ %handleVars, HandleFlags^ %Flags, KnobPuzzle^ %Game);

System::String^ searchPuzzleType(System::String^ code);
array<System::String^>^ getCodeStrings(System::String^ code); 
int getCodeLocation(array<System::String^>^ lines, System::String^ code);
std::string intToStdString(int number);
System::String^ stdStringToSystemString(std::string str);
std::string systemStringToStdString(System::String^ str);

// OPENCV <--> MANAGED Conversions
List<int>^ scalarToList(cv::Scalar scalar);

void on_trackbar( int, void* );

#endif
