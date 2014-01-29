/*  This file includes all the functions that are directly related to the maintenance of the RunTracking class,
e.g. initializing, starting, ending.  Tracking functions are located in "Tracking.cpp"   
*/

#include "stdafx.h"

#include <opencv2\opencv.hpp>        
#include "Functions.h"
#include "RunTracking.h"

// initialize all variables upon creation of class 
void RunTracking::Initialize() {

		// SET THIS VARIABLE FOR TEST CASES. 0 = NOT TEST. 1,2,3,4... for different tests. 
		this->TestCase = Constants::TESTNUMBER;
        this->window1 = "Original Capture";
        this->trackbar_window = "Trackbar Window";
        this->window2 = "Filtered Image";
        this->puzzle_window = "Puzzle Board Window";
        //default capture width and height
        this->FRAME_WIDTH = 640;
        this->FRAME_HEIGHT = 480;
        //max number of objects to be detected in frame
        this->MAX_NUM_OBJECTS=20;
        //minimum and maximum object area
        this->MIN_OBJECT_AREA = 2500;
        this->MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
        this->H_min = 0;
        this->H_max = 256;
        this->S_min = 0;
        this->S_max = 256;
        this->V_min = 0;
        this->V_max = 256;

		this->ScoreKeep = gcnew GamePlayed(this->Game);

		DateTime tim = DateTime::Now;
		this->StartTime = tim.Ticks; 
		this->ScoreKeep->timeStarted = tim;


}
//----------------------------------------------------------------------------------------------------------

// start running opencv
void RunTracking::Start() {
        // initialize the class and then start tracking
        Initialize();
		//IF test is selected, go to test
		if (this->TestCase != 0) {
			switch(this->TestCase) {
				case 1:  Test1();	break;
				case 2:  //Test2();	break;
				case 3: //Test3();	break;
				case 4: //Test4();	break;
				case 5: //Test5();	break;
				case 6: //Test6();	break;
			    // need to modify this in order to add more tests
				default: 
					System::String^ errorStr = "Error: Cannot find test case " + this->TestCase;
					System::Windows::Forms::MessageBox::Show(errorStr);
			}
		}
		//Otherwise, start tracking
		else { startTrack(); }
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

//----------------------------------------------------------------------------------------------------------

void RunTracking::Stop() {
	this->STOP = true;
	this->ScoreKeep->setTimeForCompletion(getElapsedSeconds(this->StartTime));
	this->ScoreKeep->compileData();
	System::Windows::Forms::MessageBox::Show(this->ScoreKeep->printData());
	return;
}