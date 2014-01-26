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
#include "TrackedPiece.h"
#include "HandleVariables.h"
#include "RunTracking.h"
#include "Functions.h"
#include "Shape.h"

using namespace cv;
using namespace std;
/*
 * These are now defined in RunTracking.cpp
 *
const std::string window1 = "Original Capture";
const std::string trackbar_window = "Trackbar Window";
const std::string window2 = "Filtered Image";
const std::string puzzle_window = "Puzzle Board Window";

//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;
//max number of objects to be detected in frame
const int MAX_NUM_OBJECTS=10;
//minimum and maximum object area
const int MIN_OBJECT_AREA = 2500;
const int MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;

int H_min = 0;
int H_max = 256;
int S_min = 0;
int S_max = 256;
int V_min = 0;
int V_max = 256;
*/
void on_trackbar( int, void* )
{//This function gets called whenever a
	// trackbar position is changed
}

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

//string intToStdString(int number){
//	std::stringstream ss;
//	ss << number;
//	return ss.str();
//}

void RunTracking::drawObject(vector<TrackedPiece> pieces, Mat &frame){

	for(int i =0; i<pieces.size(); i++){

		cv::circle(frame,cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()),10,cv::Scalar(0,0,255));
		cv::putText(frame,intToStdString(pieces.at(i).getXPos())+ " , " + intToStdString(pieces.at(i).getYPos()),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()+20),1,1,Scalar(0,255,0));
		cv::putText(frame,pieces.at(i).getName(),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()-30),1,2,pieces.at(i).getColor());
	}
}

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

					TrackedPiece tmp;
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

					// Check for movement
					if(xPos > (piece.getLastxPos() + thresh) || xPos < (piece.getLastxPos() - thresh))
					{
						piece.setLastxPos(xPos);
						cout << piece.getName() << ": X movement" << endl;
					}
					if(yPos > (piece.getLastyPos() + thresh) || yPos < (piece.getLastyPos() - thresh))
					{
						piece.setLastyPos(yPos);
						cout << piece.getName() << "Y movement." << endl;
					}

				}else objectFound = false;


			}
			//let user know you found an object
			if(objectFound ==true){
				//draw object location on screen
				drawObject(pieces,cameraFeed);}

		}else putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
	}
}

void RunTracking::trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image)
{
	//convert to binary image with white = in range specified
	inRange(HSV_image, piece.getHSVmin(), piece.getHSVmax(), threshold_image);	
	erodeAndDilate(threshold_image);
	trackFilteredObject(piece, camera_feed, threshold_image);

}

void RunTracking::drawPuzzleBoard(Mat &image)
{
	Shape shapes(&image);
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
}

int RunTracking::startTrack()
{
	bool calibrate_mode = false;

	VideoCapture capture;
	capture.open(1);	//Open default video device
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
	
	if (!capture.isOpened())
	{
		cout << "Cannot open default camera." << endl;
		return -1;
	}
	cout << "Camera opened" << endl;

	Mat camera_feed;		//raw camera image
	Mat HSV_image;			//camera image converted to HSV
	Mat threshold_image;	//image after HSV is filtered and processed
	

	if (calibrate_mode)
	{
		createTrackbarWindow();
	}

//	TrackedPiece yellow = TrackedPiece("Tennis Ball", Scalar(25,44,160), Scalar(77,95,256));
	TrackedPiece red_circle = TrackedPiece("Circle", Scalar(165, 107, 25), Scalar(185, 233, 256));
	TrackedPiece green_rectangle = TrackedPiece("Rectangle", Scalar(74, 75, 50), Scalar(88, 214, 256));
	TrackedPiece yellow_pentagon = TrackedPiece("Pentagon", Scalar(16, 47, 47), Scalar(32, 200, 256));
	TrackedPiece white_square = TrackedPiece("Square", Scalar(77, 0, 168), Scalar(158, 63, 256));

	Mat puzzle;				//Puzzle board image for drawing shapes on
	namedWindow(puzzle_window);
//	namedWindow(puzzle_window, CV_WINDOW_NORMAL);
//	cvSetWindowProperty(puzzle_window.c_str(), CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);	// Makes full screen
	drawPuzzleBoard(puzzle);
	imshow(puzzle_window, puzzle);


	while(1)
	{
		capture.read(camera_feed);

		namedWindow(window1);
//		imshow(window1, camera_feed);

		namedWindow(window2);
		cvtColor(camera_feed, HSV_image, CV_BGR2HSV);

		if(calibrate_mode)
		{
			// Track temp puzzle piece with values from slider
			TrackedPiece tmp = TrackedPiece("temp", Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max));
			trackTrackedPiece(tmp, camera_feed, HSV_image, threshold_image);
			imshow(window2, threshold_image);
		}
		else
		{
//			trackTrackedPiece(yellow, camera_feed, HSV_image, threshold_image);
			trackTrackedPiece(red_circle, camera_feed, HSV_image, threshold_image);
			trackTrackedPiece(green_rectangle, camera_feed, HSV_image, threshold_image);
			trackTrackedPiece(yellow_pentagon, camera_feed, HSV_image, threshold_image);
			trackTrackedPiece(white_square, camera_feed, HSV_image, threshold_image);
			imshow(window2, threshold_image);
		}
		
		imshow(window1, camera_feed);

		waitKey(30);
	}
	
	return 0;
}

