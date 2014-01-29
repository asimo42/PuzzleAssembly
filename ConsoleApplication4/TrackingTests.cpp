#include "stdafx.h"

#include <vcclr.h>
#include <iostream>
#include <string>
//#include <opencv2\opencv.hpp>        //includes all OpenCV headers
#include "TrackedPiece.h"
#include "HandleVariables.h"
#include "RunTracking.h"
#include "Functions.h"
#include "Shape.h"

using namespace cv;
using namespace std;
using namespace System::Windows::Forms;
using namespace System::Diagnostics;

// when adding tests, it is desirable to name them Test1, Test2...
// because each test is matched up to an integer, which is used for test selection


void RunTracking::Test1() {
	MessageBox::Show("RUNNING TEST 1: 1 second between each piece placement.");
	int placeTime;
	for each (PuzzlePiece^ piece in this->ScoreKeep->game->pieceList)
	{
		placeTime = getElapsedSeconds(this->StartTime);
		piece->setTimePlaced(placeTime);
		Debug::WriteLine("time is " + placeTime);
		System::Threading::Thread::Sleep(1*1000); // wait for 1 second (1000 ms)
	}

	this->Stop();
}