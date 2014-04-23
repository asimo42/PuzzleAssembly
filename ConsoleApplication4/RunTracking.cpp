/*  This file includes all the functions that are directly related to the maintenance of the RunTracking class,
e.g. initializing, starting, ending.  Tracking functions are located in "Tracking.cpp"   
*/

#include "stdafx.h"

#include <opencv2\opencv.hpp>        
#include "Functions.h"
#include "RunTracking.h"

void RunTracking::Initialize() {

		//this->TestCase = Constants::TESTNUMBER;

        this->original_window = "Original Capture";
        this->trackbar_window = "Trackbar Window";
        this->filtered_window = "Filtered Image";
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

		// initialize gameRecording and set its start time to now. All scores will be measured against this start time
		this->gameRecord = gcnew GamePlayed();
		this->gameRecord->setStartTimeToNow();
		this->STOP = false;

		// sound file names
		sound_game_start = "guitar_start.mp3";
		sound_game_completed = "guitar_end.mp3";

		sound_player = new SoundEffectPlayer();

		//Can play game start sound here
		playSoundEffect(sound_game_start);
		
}
//----------------------------------------------------------------------------------------------------------

// start running opencv
int RunTracking::Start() {

		////IF test is selected, go to test
		//if (this->TestCase != 0) {
		//	switch(this->TestCase) {
		//		case 1:  Test1();	break;
		//		case 2:  Test2();	break;
		//		case 3:  Test3();	break;
		//		case 4:  Test4();	break;
		//		case 5:  Test5();	break;
		//		case 6:  Test6();	break;
		//	    // add more tests here as necessary
		//		default: 
		//			System::String^ errorStr = "Error: Cannot find test case " + this->TestCase;
		//			System::Windows::Forms::MessageBox::Show(errorStr);
		//	}
		//}
		//else { 
		int success = startTrack(); 
		return success;
		//}
}
//----------------------------------------------------------------------------------------------------------

// when tracking is ended, destroy windows and compile data
void RunTracking::endTrack() {

		System::Console::WriteLine("RunTracking::EndTrack() : Exiting RunTracking");
		cv::destroyAllWindows();

		// if game was exited early, tell gameRecord to handle what we have
		if (this->Game->isEndGame()) {
			this->gameRecord->gameEndedEarly();
			return;
		}

		// if game was completed, compile record for game 
        System::Windows::Forms::MessageBox::Show("Congratulations, YOU WON!");
		//this->gameRecord->setTimeCompletedToNow();
		this->gameRecord->compileData();

		return;
}

//----------------------------------------------------------------------------------------------------------
// called when the tracker decides a piece was placed
void RunTracking::processPlacementOfPiece(TrackedPiece trackedpiece) 
{
	// find corresponding PuzzlePiece^ in KnobPuzzleInstance, and set it's time placed to now.
	for each (PuzzlePiece^ piece in this->Game->getPieceList()) {
		if (piece->getName()->Equals(stdStringToSystemString(trackedpiece.getName()))) {
			piece->setTimePlacedToNow();
			Console::WriteLine("RunTracking.cpp: processPlacementOfPiece() : piece placed!! - " + piece->getName());
		}
	}
}
