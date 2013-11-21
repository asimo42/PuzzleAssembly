/* This file contains the main functions involved with tracking.  The majority of these functions belong to the "RunTracking" class, though that
might be changed back in a while (may decide to go more library style)

The functions used for tracking are primarily based in standard C++
*/

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

using namespace cv;
using namespace std;


#define USEOPENCV


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

void RunTracking::drawObject(vector<TrackedPiece> pieces, Mat &frame){

	for(int i =0; i<pieces.size(); i++){

	cv::circle(frame,cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()),10,cv::Scalar(0,0,255));
	cv::putText(frame,intToStdString(pieces.at(i).getXPos())+ " , " + intToStdString(pieces.at(i).getYPos()),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()+20),1,1,Scalar(0,255,0));
	cv::putText(frame,pieces.at(i).getName(),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()-30),1,2,pieces.at(i).getColor());
	}
}

void RunTracking::trackFilteredObject(TrackedPiece piece, Mat &cameraFeed, Mat &threshold_image){

	vector <TrackedPiece> pieces;

	Mat temp;
	threshold_image.copyTo(temp);
	//these two vectors needed for output of findContours
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	//find contours of filtered image using openCV findContours function
#ifdef USEOPENCV
	findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );
#endif
	//use moments method to find our filtered object
	double refArea = 0;
	bool objectFound = false;
	if (hierarchy.size() > 0) {
		int numObjects = hierarchy.size();
		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
		if(numObjects<MAX_NUM_OBJECTS){
			for (int index = 0; index >= 0; index = hierarchy[index][0]) {

				Moments moment = moments((cv::Mat)contours[index]);
				double area = moment.m00;

				//if the area is less than 20 px by 20px then it is probably just noise
				//if the area is the same as the 3/2 of the image size, probably just a bad filter
				//we only want the object with the largest area so we safe a reference area each
				//iteration and compare it to the area in the next iteration.
				if(area>MIN_OBJECT_AREA){

					TrackedPiece tmp;
					
					tmp.setXPos(moment.m10/area);
					tmp.setYPos(moment.m01/area);
					tmp.setName(piece.getName());
					tmp.setColor(piece.getColor());

					pieces.push_back(tmp);

					objectFound = true;

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

int RunTracking::startTrack()
{
	bool calibrate_mode = true;
	bool STOP = false;
	VideoCapture capture;
	capture.open(0);	//Open default video device
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

	while(!this->STOP)
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
			TrackedPiece red = TrackedPiece("Red", Scalar(156,109,175), Scalar(195,156,256));
			TrackedPiece green = TrackedPiece("Green", Scalar(67,86,167), Scalar(88,121,256));
			TrackedPiece blue = TrackedPiece("Blue", Scalar(77,123,230), Scalar(130,214,256));
			trackTrackedPiece(red, camera_feed, HSV_image, threshold_image);
			trackTrackedPiece(green, camera_feed, HSV_image, threshold_image);
			trackTrackedPiece(blue, camera_feed, HSV_image, threshold_image);
		}
		
		imshow(window1, camera_feed);

		waitKey(30);
	}
	endTrack();
	return 0;
}




