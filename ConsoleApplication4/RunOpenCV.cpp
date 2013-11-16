#include "stdafx.h"

#include <opencv2\opencv.hpp>	
#include "Functions.h"
#include "RunOpenCV.h"

void RunOpenCV::Initialize() {
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

void RunOpenCV::Start() {
	Initialize();
	startTrack();
	endTrack();
	System::Diagnostics::Debug::WriteLine("Hey, opencv is done");
	System::Windows::Forms::MessageBox::Show(this->Flags->JunkLine);
}

void RunOpenCV::endTrack() {
	// may want to wait for main GUI to pull all the scorekeeping info first.
	System::Diagnostics::Debug::WriteLine("Hey, opencv is done");
	System::Diagnostics::Debug::WriteLine("GAME OVER!!!");
	System::Windows::Forms::MessageBox::Show(this->Flags->JunkLine);
}
