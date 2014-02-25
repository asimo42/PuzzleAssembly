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

#include "stdafx.h"

#include <vcclr.h>
#include <iostream>
#include <string>
#include <vector>
#include <opencv2\opencv.hpp>	//includes all OpenCV headers
#include "Functions.h"
#include "Shape.h"
#include "RunTracking.h"
#include <Windows.h>	// for timer

using namespace cv;
using namespace std;

//
// Global for now, should not be though
vector<TrackedPiece> pieces;

Mat puzzle_board;				//Puzzle board image for drawing shapes on

void on_trackbar( int, void* )
{//This function gets called whenever a
	// trackbar position is changed
}

//----------------------------------------------------------------------------------------------------------
 void RunTracking::loadTrackedPieces() {
	 for (int i = 0; i < this->Game->getPieceList()->Count; i++) {
		 pieces.push_back(puzzlePieceToTrackedPiece(this->Game->getPieceList()[i]));
	 }
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

	vector <TrackedPiece> pieces;

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
void RunTracking::drawPuzzleBoard(Mat &image)
{
	//Shape shapes(&image);
	shapes.setImage(&image);
	shapes.Clear_To_Black();	// Must clear to black first, otherwise get exception
	// Magic numbers below are coordinates from trail and error on 1280x1024 screen
	shapes.setColor(Scalar(0, 0, 255));
	shapes.Draw_Circle(Point(383, 244), 125, -1);
	shapes.setColor(Scalar(255, 0, 0));
	shapes.Draw_Square(Point(748, 128), 238, -1);
	shapes.setColor(Scalar(255, 0, 255));
	shapes.Draw_Triangle(Point(220, 600), 266, -1);
	shapes.setColor(Scalar(0, 255, 0));
	shapes.Draw_Rectangle(Point(483, 634), 287, 175, -1);
	shapes.setColor(Scalar(0, 255, 255));
	shapes.Draw_Pentagon(Point(1056, 585), 173, -1);
}
//----------------------------------------------------------------------------------------------------------

VOID CALLBACK timerTick(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime)
{
	int thresh = 40;

	int status = 0;
	for(int i = 0; i < pieces.size(); ++i)
	{	
		if(pieces[i].getXPos() > (pieces[i].getLastxPos() + thresh) || pieces[i].getXPos() < (pieces[i].getLastxPos() - thresh))
		{
			pieces[i].setLastxPos(pieces[i].getXPos());
			pieces[i].checkForMovement(true);
			//cout << pieces[i].getName() << ": X movement" << endl;
		}	

		else if(pieces[i].getYPos() > (pieces[i].getLastyPos() + thresh) || pieces[i].getYPos() < (pieces[i].getLastyPos() - thresh))
		{
			pieces[i].setLastyPos(pieces[i].getYPos());
			status = pieces[i].checkForMovement(true);
			//cout << pieces[i].getName() << ": Y movement." << endl;
		}

		else 
			status = pieces[i].checkForMovement(false);

		//Depending of the status returned above, this will change 
		//if all the other pieces are turned off, turned on, etc...
		if (status == 1)
		{
			for(int j = 0; j < pieces.size(); j++)
				if (i != j)
					pieces[j].setTurnOff(false);
		}
		else if (status == 2)
		{
			for(int j = 0; j < pieces.size(); j++)
				if (i != j)
					pieces[j].setDimmed(true);
		}
		else if (status == 3)
		{
			for(int j = 0; j < pieces.size(); j++)
				if (i != j)
					pieces[j].setTurnOff(true);
		}
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
	// set timer to periodically check piece movement
	UINT timer_ms = 500;
	SetTimer(NULL, 1, timer_ms, timerTick);

	// set timer to flash shapes
	UINT timer_flash = 600;
	SetTimer(NULL, 1, timer_flash, timerFlash);
	

	// TRYING TO IMPORT CALIBRATED PIECES HERE::
	this->loadTrackedPieces();
	//pieces.push_back(TrackedPiece("Circle", Scalar(0, 130, 0), Scalar(5, 256, 256)));
	//pieces.push_back(TrackedPiece("Rectangle", Scalar(65, 130, 0), Scalar(82, 256, 256)));
	//pieces.push_back(TrackedPiece("Pentagon", Scalar(18, 130, 75), Scalar(30, 256, 256)));

	//

	bool calibrate_mode = false;

	VideoCapture capture;
	capture.open(1);	//0 is default video device, 1 is other/USB camera
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
	
	if (!capture.isOpened())
	{
		cout << "Cannot open camera." << endl;
		return 1;
	}
	cout << "Camera opened" << endl;

	Mat camera_feed;		//raw camera image
	Mat HSV_image;			//camera image converted to HSV
	Mat threshold_image;	//image after HSV is filtered and processed
	

	if (calibrate_mode)
	{
		createTrackbarWindow();
	}

	// Moved to member variables of RunTracking class
//	TrackedPiece yellow = TrackedPiece("Tennis Ball", Scalar(25,44,160), Scalar(77,95,256));
//	TrackedPiece red_circle = TrackedPiece("Circle", Scalar(165, 107, 25), Scalar(185, 233, 256));
//	TrackedPiece green_rectangle = TrackedPiece("Rectangle", Scalar(74, 75, 50), Scalar(88, 214, 256));
//	TrackedPiece yellow_pentagon = TrackedPiece("Pentagon", Scalar(16, 47, 47), Scalar(32, 200, 256));
//	TrackedPiece white_square = TrackedPiece("Square", Scalar(77, 0, 168), Scalar(158, 63, 256));

	//Mat puzzle;				//Puzzle board image for drawing shapes on

	namedWindow(puzzle_window);
	//	namedWindow(puzzle_window, CV_WINDOW_NORMAL);
	//	cvSetWindowProperty(puzzle_window.c_str(), CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);	// Makes full screen
	drawPuzzleBoard(puzzle_board);
	imshow(puzzle_window, puzzle_board);


	while(1)
	{
		capture.read(camera_feed);

		namedWindow(original_window);
//		imshow(original_window, camera_feed);

		namedWindow(filtered_window);
		cvtColor(camera_feed, HSV_image, CV_BGR2HSV);

		if(calibrate_mode)
		{
			// Track temp puzzle piece with values from slider
			TrackedPiece tmp = TrackedPiece("temp", Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max));
			trackTrackedPiece(tmp, camera_feed, HSV_image, threshold_image);
			imshow(filtered_window, threshold_image);
		}

		else
		{
//			trackTrackedPiece(yellow, camera_feed, HSV_image, threshold_image);
			for (int i = 0; i < pieces.size(); ++i)
			{
				trackTrackedPiece(pieces[i], camera_feed, HSV_image, threshold_image);
			}
//			trackTrackedPiece(white_square, camera_feed, HSV_image, threshold_image);
			imshow(filtered_window, threshold_image);
		}
		
		imshow(original_window, camera_feed);

		waitKey(30);
		if (this->Game->isEndGame()) {
			endTrack();
			return 0;
		}
	}
	destroyAllWindows();
	return 0;
}


