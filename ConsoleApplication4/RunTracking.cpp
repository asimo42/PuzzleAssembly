/*  This file includes all the functions that are directly related to the maintenance of the RunTracking class,
e.g. initializing, starting, ending.  Tracking functions are located in "Tracking.cpp"   
*/

#include "stdafx.h"
#include <opencv2\opencv.hpp>        
#include "Functions.h"
#include "RunTracking.h"

// initialize all variables upon creation of class. This is run by an external call to the RunTracking::Start() function
void RunTracking::Initialize() {
		//red_circle = TrackedPiece("Circle", Scalar(165, 107, 25), Scalar(185, 233, 256));
		//green_rectangle = TrackedPiece("Rectangle", Scalar(74, 75, 50), Scalar(88, 214, 256));
		//yellow_pentagon = TrackedPiece("Pentagon", Scalar(16, 47, 47), Scalar(32, 200, 256));

		/*
		 * doing this in Tracking.cpp for now
		 */
		//pieces.push_back(TrackedPiece("Circle", Scalar(165, 107, 25), Scalar(185, 233, 256)));
		//pieces.push_back(TrackedPiece("Rectangle", Scalar(74, 75, 50), Scalar(88, 214, 256)));
		//pieces.push_back(TrackedPiece("Pentagon", Scalar(16, 47, 47), Scalar(32, 200, 256)));

		// SET THIS VARIABLE FOR TEST CASES. 0 = NOT TEST. 1,2,3,4... for different tests. 
		this->TestCase = Constants::TESTNUMBER;

        this->window1 = "Original Capture";
        this->trackbar_window = "Trackbar Window";
        this->window2 = "Filtered Image";
        this->puzzle_window = "Puzzle Board Window";

        //default capture width and height
        this->FRAME_WIDTH = Constants::DEFAULT_FRAME_WIDTH;
        this->FRAME_HEIGHT = Constants::DEFAULT_FRAME_HEIGHT;

        //max number of objects to be detected in frame
        this->MAX_NUM_OBJECTS= Constants::DEFAULT_MAX_OBJECTS_IN_FRAME;

        //minimum and maximum object area
        this->MIN_OBJECT_AREA = Constants::DEFAULT_MIN_OBJECT_AREA;
        this->MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
        this->H_min = Constants::DEFAULT_H_MIN;
        this->H_max = Constants::DEFAULT_H_MAX;
        this->S_min = Constants::DEFAULT_S_MIN;
        this->S_max = Constants::DEFAULT_S_MAX;
        this->V_min = Constants::DEFAULT_V_MIN;
        this->V_max = Constants::DEFAULT_V_MAX;

		// initialize scorekeeping
			
		this->ScoreKeep = gcnew GamePlayed(this->Game); // am currently assuming Game is initialized; need error checking here

		// set up the start time to now. All scores will be measured against this start time
		DateTime tim = DateTime::Now;
		this->ScoreKeep->timeStarted = tim;

		this->STOP = false;
}
//----------------------------------------------------------------------------------------------------------

// start running tracking. This must be called outside the class
void RunTracking::Start() {

        // initialize the class and then start tracking
        Initialize();

		//IF test is selected, go to test
		if (this->TestCase != 0) {
			switch(this->TestCase) {
				case 1:  Test1();	break;
				case 2:  Test2();	break;
				case 3:  Test3();	break;
				case 4:  Test4();	break;
				case 5:  Test5();	break;
				case 6:  Test6();	break;
			    // add more tests here as necessary
				default: 
					System::String^ errorStr = "Error: Cannot find test case " + this->TestCase;
					System::Windows::Forms::MessageBox::Show(errorStr);
			}
		}

		//Otherwise, start tracking
		else { startTrack(); }
}
//----------------------------------------------------------------------------------------------------------

// end tracking, 'clean up' game.  (In progress - will need to parse input from GUI before this becomes useful)
void RunTracking::endTrack() {
        System::Windows::Forms::MessageBox::Show("GAME OVER!");
}

//----------------------------------------------------------------------------------------------------------

gcroot<GamePlayed^> RunTracking::returnScore() {
        return this->ScoreKeep;
}

//----------------------------------------------------------------------------------------------------------
// stop tracking, and compile results data into the GamePlayed instance. 
void RunTracking::Stop() {

	this->STOP = true;
	this->ScoreKeep->setTimeForCompletion(getElapsedSeconds(this->ScoreKeep->timeStarted->Ticks));
	this->ScoreKeep->compileData();
	return;

}

//----------------------------------------------------------------------------------------------------------
// once you've identified which piece was placed, and that it was placed, handle it (IN PROGRESS!!!)
void RunTracking::processPlacementOfPiece(TrackedPiece trackedpiece) 
{
	// first, get the current time
	double placeTime = getElapsedSeconds(this->ScoreKeep->timeStarted->Ticks);
	// then match the tracked piece to it's corresponding PuzzlePiece
	// probably by name
	// then pull the time of placement and give it to the PuzzlePiece
}