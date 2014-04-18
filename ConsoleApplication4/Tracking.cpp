// Multiple_Object_Tracking.cpp : Defines the entry point for the console application.
//

// This project has been modified from the original version written by Kyle Hounslow:

//-------------------------------------------------------------------------------------------------------------------------
//Written by  Kyle Hounslow 2013

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
//, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
//and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//-------------------------------------------------------------------------------------------------------------------------

/* This  file defines all of the tracking functions and algorithms used for tracking during normal gameplay (not calibration). Most
functions belong to the RunTracking class.
*/

#include "stdafx.h"

#include <Windows.h>	// for timer
#include <WinBase.h>	//for sleep()
#include <vcclr.h>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2\opencv.hpp>	//includes all OpenCV headers
#include "Functions.h"
#include "Shape.h"
#include "RunTracking.h"
#include <msclr\marshal_cppstd.h> //to convert managed string to std::string


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

using namespace cv;
using namespace std;
using namespace msclr::interop;

//
// Global for now, should not be though
vector<TrackedPiece> pieces;

Mat puzzle_board;				//Puzzle board image for drawing shapes on
int difficulty;					//Difficulty pulled from the gui
								//  there should be a better way to access this but
								//  I'm not sure how to do that.

//----------------------------------------------------------------------------------------------------------
// Plays the audio file 'filename.' The file must be in Sounds which is two levels up from execution directory.
int RunTracking::playSoundEffect(string filename) {
	System::String^ soundfile = System::Windows::Forms::Application::StartupPath + "/../../Sounds/";
	string stdsoundfile = marshal_as<string>(soundfile);
	stdsoundfile += filename;
	sound_player->play_Sound(stdsoundfile);
	return 0;
}

//----------------------------------------------------------------------------------------------------------
void on_trackbar( int, void* )
{//This function gets called whenever a
	// trackbar position is changed
}

//----------------------------------------------------------------------------------------------------------
// load up the tracked pieces vector from the PuzzlePieces imported with the KnobPuzzle
int RunTracking::loadTrackedPieces() {
	pieces.clear();
	// if there are no pieces to load, return an error
	if (this->Game->getPieceList()->Count < 1) {
		Console::WriteLine("RunTracking::loadTrackedPieces(): no pieces to load!");
		return -1;
	}
	// otherwise, convert each PuzzlePiece to a TrackedPiece and push it onto the vector
	 for (int i = 0; i < this->Game->getPieceList()->Count; i++) {
		 pieces.push_back(puzzlePieceToTrackedPiece(this->Game->getPieceList()[i]));
	 }
	 return 0;
 }

//----------------------------------------------------------------------------------------------------------
void RunTracking::createTrackbarWindow()
{
	namedWindow(trackbar_window);
	createTrackbar( "H_MIN", trackbar_window, &H_min, H_max, on_trackbar );
	createTrackbar( "H_MAX", trackbar_window, &H_max, H_max, on_trackbar );
	createTrackbar( "S_MIN", trackbar_window, &S_min, S_max, on_trackbar );
	createTrackbar( "S_MAX", trackbar_window, &S_max, S_max, on_trackbar );
	createTrackbar( "V_MIN", trackbar_window, &V_min, V_max, on_trackbar );
	createTrackbar( "V_MAX", trackbar_window, &V_max, V_max, on_trackbar );
}

//----------------------------------------------------------------------------------------------------------
void RunTracking::erodeAndDilate(Mat &image)
{
	//create structuring element that will be used to "dilate" and "erode" image.
	//the element chosen here is a 3px by 3px rectangle

	Mat erodeElement = getStructuringElement( MORPH_RECT,Size(3,3));
	//dilate with larger element so make sure object is nicely visible
	Mat dilateElement = getStructuringElement( MORPH_RECT,Size(8,8));

	erode(image,image,erodeElement);
	erode(image,image,erodeElement);


	dilate(image,image,dilateElement);
	dilate(image,image,dilateElement);
}

//----------------------------------------------------------------------------------------------------------
void RunTracking::drawObject(vector<TrackedPiece> pieces, Mat &frame){

	for(int i =0; i<pieces.size(); i++){

		cv::circle(frame,cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()),10,cv::Scalar(0,0,255));
		cv::putText(frame,intToStdString(pieces.at(i).getXPos())+ " , " + intToStdString(pieces.at(i).getYPos()),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()+20),1,1,Scalar(0,255,0));
		cv::putText(frame,pieces.at(i).getName(),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()-30),1,2,pieces.at(i).getColor());
	}
}

//----------------------------------------------------------------------------------------------------------
void RunTracking::trackFilteredObject(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image){

	vector <TrackedPiece> pieces; // IS THIS THE SAME AS THE GLOBAL VARIABLE ABOVE???

	Mat temp;
	threshold_image.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
	//use moments method to find our filtered object
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
//		cout << "Num objects: " << numObjects << endl;
//		cout << "Max Num objects: " << MAX_NUM_OBJECTS << endl;
		// threshholed to calculate movement
		const int thresh = 40;
		//saves max area of each contour detected so only the largest one will be tracked
		double maxArea = 0;
		// temporary piece for contours found
		TrackedPiece tmp;

		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if(numObjects < MAX_NUM_OBJECTS){
			// for each object (contour) detected
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				// get the moment of the contour
				Moments moment = moments((cv::Mat)contours[index]);
				// get the area from the moment
				double area = moment.m00;
//				cout << "Area " << index << " is: " << area << endl;
				
				// if the area is less than MIN_OBJECT_AREA then it is probably just noise
				// it must also be large than the max area found so far since we only want the largest area.
				if(area > MIN_OBJECT_AREA && area > maxArea){
					// set new max area
					maxArea = area;
					// Clear previous objects found so only one (the biggest) is detected
					pieces.clear();

					int xPos = moment.m10/area;
					int yPos = moment.m01/area;
					
					tmp.setXPos(xPos);
					tmp.setYPos(yPos);
					tmp.setName(piece.getName());
					tmp.setColor(piece.getColor());

					//cout << piece.getName() << ": x: " << xPos << " y: " << yPos << endl;
					//cout << "LastPos: x: " << piece.getLastxPos() << " y: " << piece.getLastyPos() << endl;

					pieces.push_back(tmp);

					objectFound = true;
				}
			}

			//let user know you found an object and check for movement
			if(objectFound ==true){

				// Update piece location (tmp piece should now be biggest contour found)
				piece.setXPos(tmp.getXPos());
				piece.setYPos(tmp.getYPos());

				/*
				 * Movement checking moved to timerTick
				 *
				// Check for movement (tmp piece should now be biggest contour found)
				if(tmp.getXPos() > (piece.getLastxPos() + thresh) || tmp.getXPos() < (piece.getLastxPos() - thresh))
				{
					piece.setLastxPos(tmp.getXPos());
					cout << piece.getName() << ": X movement" << endl;
				}
				if(tmp.getYPos() > (piece.getLastyPos() + thresh) || tmp.getYPos() < (piece.getLastyPos() - thresh))
				{
					piece.setLastyPos(tmp.getYPos());
					cout << piece.getName() << ": Y movement." << endl;
				}
				*/

				//draw object location on screen
				drawObject(pieces,cameraFeed);}

		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}

//----------------------------------------------------------------------------------------------------------
void RunTracking::trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image)
{
	//convert to binary image with white = in range specified
	inRange(HSV_image, piece.getHSVmin(), piece.getHSVmax(), threshold_image);	
	erodeAndDilate(threshold_image);
	trackFilteredObject(piece, camera_feed, threshold_image);
}

//----------------------------------------------------------------------------------------------------------
// draw the puzzleboard background by pulling shape information from the TrackedPiece vector
void RunTracking::drawPuzzleBoard(Mat &image)
{
	//Shape shapes(&image);
	shapes.setImage(&image);
	shapes.Clear_To_Black(); // Must clear to black first, otherwise get exception
 	shapes.Clear_To_Gray();	
	for (unsigned int i = 0; i < pieces.size(); i++)
	{
		shapes.Draw_Shape(pieces[i], 1);
	}
}

//----------------------------------------------------------------------------------------------------------
// This should probably be a member function of some class, but I wasn't sure where it should go.
bool checkIfAllCorrect()
{
	for(int i = 0; i < pieces.size(); i++)
	{
		// If a piece is found that isn't placed correctly, return false
		if(!pieces[i].getIsPlacedCorrectly())
			return false;
	}
	return true;
}

//----------------------------------------------------------------------------------------------------------
VOID CALLBACK timerTick(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime)
{
	int thresh = 40;

	for(int i = 0; i < pieces.size(); ++i)
		pieces[i].clearStatus();

	for(int i = 0; i < pieces.size(); ++i)
	{	
		int status = 0;
		if(pieces[i].getXPos() > (pieces[i].getLastxPos() + thresh) || pieces[i].getXPos() < (pieces[i].getLastxPos() - thresh))
		{
			pieces[i].setLastxPos(pieces[i].getXPos());
			status = pieces[i].checkForMovement(true);
			//cout << pieces[i].getName() << ": X movement" << endl;
		}	

		else if(pieces[i].getYPos() > (pieces[i].getLastyPos() + thresh) || pieces[i].getYPos() < (pieces[i].getLastyPos() - thresh))
		{
			pieces[i].setLastyPos(pieces[i].getYPos());
			status = pieces[i].checkForMovement(true);
			//cout << pieces[i].getName() << ": Y movement." << endl;
		}

		else { // No movement
			status = pieces[i].checkForMovement(false);
			pieces[i].checkIfPlacedCorrectly();
			bool allCorrect = checkIfAllCorrect();
			if (allCorrect) {
				cout << "All pieces placed correctly!" << endl;
			}
		}

		if (status != 0)
		{
			//EASY
			if(difficulty == 1)
			{
				//Turn off all other pieces
				for(int j = 0; j < pieces.size(); j++)
				if (i != j)
				{
					pieces[j].clearStatus();
					pieces[j].setTurnOff(true);
				}
			}

			//MEDIUM
			if(difficulty == 2)
			{
				//Dim all other pieces
				for(int j = 0; j < pieces.size(); j++)
				if (i != j)
				{
					pieces[j].clearStatus();
					pieces[j].setDimmed(true);
				}
			}

			//HARD
			if(difficulty == 3)
			{
				//I don't think anything has to happen here
			}
		}




		//Depending of the status returned above, this will change 
		//if all the other pieces are turned off, turned on, etc...
		/*
		if (status == 1)
		{
			//Turn on all other pieces
			for(int j = 0; j < pieces.size(); j++)
				if (i != j)
				{
					pieces[j].clearStatus();
				}
		}
		else if (status == 2)
		{
			//Dim all other pieces
			for(int j = 0; j < pieces.size(); j++)
				if (i != j)
				{
					pieces[j].clearStatus();
					pieces[j].setDimmed(true);
				}
		}
		else if (status == 3)
		{
			//Turn off all other pieces
			for(int j = 0; j < pieces.size(); j++)
				if (i != j)
				{
					pieces[j].clearStatus();
					pieces[j].setTurnOff(true);
				}
		}
		*/
	}

	//cout << "Timer tick." << endl;
}

//----------------------------------------------------------------------------------------------------------
VOID CALLBACK timerFlash(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime)
{
	for(int i = 0; i < pieces.size(); ++i)
	{
		//First check if the piece should be flashing
		if (pieces[i].isFlashing())
		{
			pieces[i].toggle(puzzle_board);
		}
		//Then check if it should be dimmed
		else if(pieces[i].isDimmed())
		{
			pieces[i].dim(puzzle_board);
		}
		//Then check if it should be turned off
		else if (pieces[i].isTurnedOff())
		{
			cout << "TURNING OFF " << pieces[i].getName() << endl;
			pieces[i].turnOff(puzzle_board);
		}
		//If its not doing anything special, then make sure that it is turned on
		else
		{
			pieces[i].turnOn(puzzle_board);
		}
	}
}
/*
 * Can't get callback to work as a member function, so making pieces global for now
 *
void* ptr;

VOID CALLBACK RunTracking::static_timerTick(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime)
{
	RunTracking* pThis = reinterpret_cast<RunTracking*>(ptr);
	pThis->timerTick(hwnd, uMsg, idEvent, dwTime);
}
*/

//----------------------------------------------------------------------------------------------------------
int RunTracking::startTrack()
{
	//Get diffculty
	difficulty = this->Game->getLevelOfDifficulty();

	// set timer to periodically check piece movement
	UINT timer_ms = Constants::TIMER_TICK;
	HWND hwnd1 = NULL;
	UINT_PTR myTimer = SetTimer(hwnd1, 1, timer_ms, timerTick);

	// set timer to flash shapes
	UINT timer_flash = Constants::FLASH_DELAY;
	HWND hwnd2 = NULL;
	UINT_PTR myTimer2 = SetTimer(hwnd2, 1, timer_flash, timerFlash);
	//SetTimer(NULL, 1, timer_flash, 2timerFlash);

	// TRYING TO IMPORT CALIBRATED PIECES HERE::
	int loadResult = this->loadTrackedPieces();

	// if import failed, return error
	if (loadResult != 0) {
		Console::WriteLine("RunTracking::startTrack():: loadTrackedPieces() failed. Exiting.");
		return -1;
	}

	VideoCapture capture;
	capture.open(0);	//0 is default video device, 1 is other/USB camera
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
	
	if (!capture.isOpened())
	{
		cout << "RunTracking::startTrack():: Cannot open camera." << endl;
		return -1;
	}
	cout << "RunTracking::startTrack():: Camera opened" << endl;

	Mat camera_feed;		//raw camera image
	Mat HSV_image;			//camera image converted to HSV
	Mat threshold_image;	//image after HSV is filtered and processed
	

	//if (calibrate_mode)
	//{
	//	createTrackbarWindow();
	//}

	// Moved to member variables of RunTracking class
//	TrackedPiece yellow = TrackedPiece("Tennis Ball", Scalar(25,44,160), Scalar(77,95,256));
//	TrackedPiece red_circle = TrackedPiece("Circle", Scalar(165, 107, 25), Scalar(185, 233, 256));
//	TrackedPiece green_rectangle = TrackedPiece("Rectangle", Scalar(74, 75, 50), Scalar(88, 214, 256));
//	TrackedPiece yellow_pentagon = TrackedPiece("Pentagon", Scalar(16, 47, 47), Scalar(32, 200, 256));
//	TrackedPiece white_square = TrackedPiece("Square", Scalar(77, 0, 168), Scalar(158, 63, 256));

	//Mat puzzle;				//Puzzle board image for drawing shapes on

	namedWindow(puzzle_window, WINDOW_NORMAL);
	drawPuzzleBoard(puzzle_board);
	imshow(puzzle_window, puzzle_board);


	// Move puzzle board window to correct position on game board monitor
	// (Puzzle board monitor needs to be set up to the left of first monitor.)
	moveWindow(puzzle_window, -1600, 0);
	cvSetWindowProperty(puzzle_window.c_str(), CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);	// Makes full screen
	moveWindow(original_window, 640, 0);
	moveWindow(filtered_window, 640, 512);

	// go into infinite loop of reading camera input and tracking pieces
	while(1)
	{
		capture.read(camera_feed);

		//namedWindow(original_window);

		//namedWindow(filtered_window);
		try {
			cvtColor(camera_feed, HSV_image, CV_BGR2HSV);
		} catch (System::Exception ^e){
		    System::Console::WriteLine("Tracking.cpp::StartTrack():: Exception " + e->GetType()->ToString() + "  at cvtColor()");
		    return -1;
		}

			for (int i = 0; i < pieces.size(); ++i)
			{
				trackTrackedPiece(pieces[i], camera_feed, HSV_image, threshold_image);
			}
//			imshow(filtered_window, threshold_image);
		
		imshow(original_window, camera_feed);

		waitKey(30);


		// check if individual pieces are placed correctly
		//allCorrect = true;
		// check if all pieces are placed correctly
		bool allCorrect = checkIfAllCorrect();
		if (allCorrect) {
			System::Console::WriteLine("Tracking.cpp::startTrack() : All pieces placed correctly!");
		}

		// ADDED TEMP WORKAROUND - game will end if all pieces have been placed at least once., whether
		// or not they are still correcly placed.
		int numberCorrectlyPlaced = 0;
		for(int i = 0; i < pieces.size(); i++)
		{	
			// if piece is already placed, continue
			if (pieces[i].isTimeLocked()) {
				numberCorrectlyPlaced++;
				continue; 
			}
			if (!pieces[i].isTimeLocked()) { allCorrect = false; }
			// otherwise check. If this is the first time finding it's correct, then process placement
			//TODO: This checkIfPlacedCorrectly should not be called every loop iteration.
			//		It needs to run only on a regular timer to be consistent with how fast it responds.
			bool correct = pieces[i].getIsPlacedCorrectly();
			if (correct && !pieces[i].isTimeLocked()) {
				// Play placed correctly sound here
				playSoundEffect(sound_piece_placed1);

				processPlacementOfPiece(pieces[i]);
				pieces[i].setTimeLock();
			}
		}
		//if (numberCorrectlyPlaced == pieces.size()) { allCorrect = true; }

		if (this->Game->isEndGame() || allCorrect) {
			if(allCorrect)
			{
				//play game completed sound
				this->gameRecord->setTimeCompletedToNow();
				playSoundEffect(sound_game_completed);
			}
			KillTimer(hwnd1, myTimer); // kill the timers
			KillTimer(hwnd2, myTimer2);
			destroyAllWindows(); // shut everything down. 
			endTrack();
			return 0;
		}
	}
	return 0;
}


