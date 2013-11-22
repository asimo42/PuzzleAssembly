/*  This file includes all the functions that are directly related to the maintenance of the RunTracking class,
e.g. initializing, starting, ending.  Tracking functions are located in "Tracking.cpp"   
*/

#include "stdafx.h"

#include <opencv2\opencv.hpp>	
#include "Functions.h"
#include "RunTracking.h"

// initialize all variables upon creation of class 
void RunTracking::Initialize() {
	this->window1 = "Original Capture";
	this->trackbar_window = "Trackbar Window";
	this->window2 = "Filtered Image";
	//default capture width and height
	this->FRAME_WIDTH = 640;
	this->FRAME_HEIGHT = 480;
	//max number of objects to be detected in frame
	this->MAX_NUM_OBJECTS=3;
	//minimum and maximum object area
	this->MIN_OBJECT_AREA = 20*20;
	this->MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
	this->H_min = 0;
	this->H_max = 256;
	this->S_min = 0;
	this->S_max = 256;
	this->V_min = 0;
	this->V_max = 256;


}
//----------------------------------------------------------------------------------------------------------

// start running opencv
void RunTracking::Start() {
	// initialize the class and then start tracking
	Initialize();
	startTrack();
}
//----------------------------------------------------------------------------------------------------------

// end tracking, 'clean up' game.  this instance of the class will now end (though that might change in the future)
void RunTracking::endTrack() {
	// **may want to wait for main GUI to pull all the scorekeeping info first.
	System::Diagnostics::Debug::WriteLine("Hey, opencv is done");
	System::Diagnostics::Debug::WriteLine("GAME OVER!!!");
	System::Windows::Forms::MessageBox::Show("GAME OVER!");
}

//----------------------------------------------------------------------------------------------------------

gcroot<GamePlayed^> RunTracking::returnScore() {
	return this->ScoreKeep;
}