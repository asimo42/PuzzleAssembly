/*  This file includes all the functions that are directly related to the maintenance of the CalibrationTracking class,
e.g. initializing, starting, ending.  Tracking functions are located in "Tracking.cpp"   
*/

#include "stdafx.h"

#include <opencv2\opencv.hpp>        
#include <vcclr.h>
#include <iostream>
#include <string>
#include <vector>
#include "TrackedPiece.h"
#include "Functions.h"
#include "CalibrationTracking.h"

using namespace cv;
using namespace std;


// initialize all variables upon creation of class 
void CalibrationTracking::Initialize() {

		// window names
        this->original_window = "Original Capture";
        this->trackbar_window = "Trackbar Window";
        this->filtered_window = "Filtered Image";
        this->puzzle_window = "Puzzle Board Window";

        //default capture width and height
        this->FRAME_WIDTH = Constants::DEFAULT_FRAME_WIDTH;
        this->FRAME_HEIGHT = Constants::DEFAULT_FRAME_HEIGHT;

        //max number of objects to be detected in frame
        this->MAX_NUM_OBJECTS= Constants::DEFAULT_MAX_OBJECTS_IN_FRAME;

        //minimum and maximum object area & HSV
        this->MIN_OBJECT_AREA = Constants::DEFAULT_MIN_OBJECT_AREA;
        this->MAX_OBJECT_AREA = FRAME_HEIGHT*FRAME_WIDTH/1.5;
        this->H_min = Constants::DEFAULT_H_MIN;
        this->H_max = Constants::DEFAULT_H_MAX;
        this->S_min = Constants::DEFAULT_S_MIN;
        this->S_max = Constants::DEFAULT_S_MAX;
        this->V_min = Constants::DEFAULT_V_MIN;
        this->V_max = Constants::DEFAULT_V_MAX;

		// holder for temporary HSV trackbar values
        this->calibrate_H_min = Constants::DEFAULT_H_MIN;
        this->calibrate_H_max = Constants::DEFAULT_H_MAX;
        this->calibrate_S_min = Constants::DEFAULT_S_MIN;
        this->calibrate_S_max = Constants::DEFAULT_S_MAX;
        this->calibrate_V_min = Constants::DEFAULT_V_MIN;
        this->calibrate_V_max = Constants::DEFAULT_V_MAX;

		// management variables
		this->STOP = false;
		this->NEXT = false;
		this->iterator = 0;
		this->waitingForUserToPlacePieces = false;
		this->doneWithLocationTracking = false;


		this->myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "calibration");
}
//----------------------------------------------------------------------------------------------------------

// start color tracking algorithm
void CalibrationTracking::Start() {
	// lets lock onto this thread just for safety sake
	startTrackColor();
}


//----------------------------------------------------------------------------------------------------------

// start location tracking algorithm
void CalibrationTracking::startLocationCalibration() {

	// display the puzzle board
	cv::Mat board = displayPuzzleBoard();
	imshow("game_board", board);
	moveWindow("game_board", -1600, 0);

	// wait for user to place pieces (gui form will send signal when done)
	while (this->waitingForUserToPlacePieces) {
		waitKey(70);
		if (this->STOP) {
			endTrack();
			return;
		}
	}

	// track locations
	startTrackLocation();
	cv::destroyAllWindows();
}
//----------------------------------------------------------------------------------------------------------

void CalibrationTracking::savePieceInformation() {

		// changing global data here, so lock down thread
		WaitForSingleObject(myMutex, INFINITE);

		// pull data from the calibration values and plug back into puzzle piece
		List<int>^ HSV_min_list = gcnew List<int>();
		List<int>^ HSV_max_list = gcnew List<int>();
		HSV_min_list->Add(this->calibrate_H_min); HSV_min_list->Add(this->calibrate_S_min); HSV_min_list->Add(this->calibrate_V_min); 
		HSV_max_list->Add(this->calibrate_H_max); HSV_max_list->Add(this->calibrate_S_max); HSV_max_list->Add(this->calibrate_V_max); 
		this->Game->getPieceList()[this->iterator]->setHSVmin(HSV_min_list);
		this->Game->getPieceList()[this->iterator]->setHSVmax(HSV_max_list);
		
		// done changing global vars; release mutex
		ReleaseMutex(myMutex);
}

// move to the next piece for calibration
void CalibrationTracking::nextPiece() {

		//destroy old trackbar window
		destroyWindow(systemStringToStdString(trackbar_window));

		// update iterator. If iterator has passed the # of pieces, end calibration
		this->iterator = this->iterator + 1;
		if (this->iterator >= this->Game->getPieceList()->Count) {
			endTrack();
			return;
		}

		// pull new piece and convert to trackedpiece
		TrackedPiece tmp = puzzlePieceToTrackedPiece(this->Game->getPieceList()[this->iterator]);
		createTrackbarWindow(tmp);		// create new trackbar window based on new initial values
		this->NEXT = false;
}

//----------------------------------------------------------------------------------------------------------

// end tracking, 'clean up' game.  this instance of the class will now end (though that might change in the future)
void CalibrationTracking::endTrack() {
		System::Console::WriteLine("CalibrationTracking::EndTrack() : Exiting CalibrationTracking");
		cv::destroyAllWindows();
		destroyWindow(systemStringToStdString(original_window));
		destroyWindow(systemStringToStdString(trackbar_window));
		destroyWindow(systemStringToStdString(filtered_window));
		destroyWindow(systemStringToStdString(puzzle_window));
		this->IS_STOPPED = true;
}


////----------------------------------------------------------------------------------------------------------

void CalibrationTracking::createTrackbarWindow(TrackedPiece &tmp)
{
	std::string trackbarwindow = systemStringToStdString(trackbar_window);
	// Create trackbar window as resizable
	namedWindow(trackbarwindow, WINDOW_NORMAL);
	resizeWindow(trackbarwindow, 640, 320);
	moveWindow(trackbarwindow, 0, 600);
        this->calibrate_H_min = tmp.getHSVmin()[0];
        this->calibrate_H_max = tmp.getHSVmax()[0];
        this->calibrate_S_min = tmp.getHSVmin()[1];
        this->calibrate_S_max = tmp.getHSVmax()[1];
        this->calibrate_V_min = tmp.getHSVmin()[2];
        this->calibrate_V_max = tmp.getHSVmax()[2];

		// now have to cast everything back to int* (I DO NOT TRUST THIS COMPLETELY; I FEAR IT MIGHT CAUSE CRASHES OR MEMORY LEAKS)
		pin_ptr<int> pinned_H_min = &this->calibrate_H_min;
		pin_ptr<int> pinned_H_max = &this->calibrate_H_max;
		pin_ptr<int> pinned_S_min = &this->calibrate_S_min;
		pin_ptr<int> pinned_S_max = &this->calibrate_S_max;
		pin_ptr<int> pinned_V_min = &this->calibrate_V_min;
		pin_ptr<int> pinned_V_max = &this->calibrate_V_max;
		//System::String^ values = H_min2 + " " + H_max2 + " " + S_min2 + " " + S_max2 + " " + V_min2 + " " + V_max2;
		// int createTrackbar(const string& trackbarname, const string& winname, int* value, int count, TrackbarCallback onChange=0, void* userdata=0)
		// value is the the location of the sliding thing, and count is the max value of the whole slider (min is always 0)
		createTrackbar( "H_MIN", systemStringToStdString(trackbar_window),  pinned_H_min, H_max, on_trackbar );
		createTrackbar( "H_MAX", systemStringToStdString(trackbar_window),  pinned_H_max, H_max, on_trackbar );
		createTrackbar( "S_MIN", systemStringToStdString(trackbar_window),  pinned_S_min, S_max, on_trackbar );
		createTrackbar( "S_MAX", systemStringToStdString(trackbar_window), pinned_S_max, S_max, on_trackbar );
		createTrackbar( "V_MIN", systemStringToStdString(trackbar_window), pinned_V_min, V_max, on_trackbar );
		createTrackbar( "V_MAX", systemStringToStdString(trackbar_window), pinned_V_max, V_max, on_trackbar );
}


////----------------------------------------------------------------------------------------------------------
// this can be combined with the runtracking version
void CalibrationTracking::erodeAndDilate(Mat &image)
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

////----------------------------------------------------------------------------------------------------------

void CalibrationTracking::drawObject(vector<TrackedPiece> pieces, Mat &frame){

	for(int i =0; i<pieces.size(); i++){

		cv::circle(frame,cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()),10,cv::Scalar(0,0,255));
		cv::putText(frame,intToStdString(pieces.at(i).getXPos())+ " , " + intToStdString(pieces.at(i).getYPos()),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()+20),1,1,Scalar(0,255,0));
		cv::putText(frame,pieces.at(i).getName(),cv::Point(pieces.at(i).getXPos(),pieces.at(i).getYPos()-30),1,2,pieces.at(i).getColor());
	}
}

////----------------------------------------------------------------------------------------------------------

List<int>^ CalibrationTracking::trackFilteredObject(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image){

	vector <TrackedPiece> pieces;
	List<int>^ returnList = gcnew List<int>;
	//returnList->Add(0); returnList->Add(0);
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
					returnList->Add(xPos);
					returnList->Add(yPos);	

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

				//draw object location on screen
				drawObject(pieces,cameraFeed);}

		}else 
		{
			putText(cameraFeed,"TOO MUCH NOISE! ADJUST FILTER",Point(0,50),1,2,Scalar(0,0,255),2);
		}
	}
	return returnList;
}

////----------------------------------------------------------------------------------------------------------

void CalibrationTracking::trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image)
{
	//convert to binary image with white = in range specified
	inRange(HSV_image, piece.getHSVmin(), piece.getHSVmax(), threshold_image);	
	erodeAndDilate(threshold_image);
	trackFilteredObject(piece, camera_feed, threshold_image);

}

////----------------------------------------------------------------------------------------------------------

List<int>^ CalibrationTracking::findPieceLocation(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image)
{
	//convert to binary image with white = in range specified
	inRange(HSV_image, piece.getHSVmin(), piece.getHSVmax(), threshold_image);	
	erodeAndDilate(threshold_image);
	List<int>^ returnedList = trackFilteredObject(piece, camera_feed, threshold_image);
	//System::String^ tmp = returnedList[0] + " " + returnedList[1];
	//System::Windows::Forms::MessageBox::Show(tmp);
	return returnedList;

}

////----------------------------------------------------------------------------------------------------------

int CalibrationTracking::startTrackLocation() 
{

	VideoCapture capture;
	capture.open(0);	//0 is default video device, 1 is other/USB camera
	//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);
	
	if (!capture.isOpened())
	{
		Console::WriteLine("CalibrationTracking::startTrackLocation():: Error - Cannot open camera.");
		return 1;
	}
	Console::WriteLine("CalibrationTracking::startTrackLocation():: Camera Opened");

	//// set up filtered and original windows
	namedWindow(systemStringToStdString(original_window));
	namedWindow(systemStringToStdString(filtered_window));

	Mat camera_feed;		//raw camera image
	Mat HSV_image;			//camera image converted to HSV
	Mat threshold_image;	//image after HSV is filtered and processed


	List<int>^ Xcoords;
	List<int>^ Ycoords;

	// loop through each puzzle piece individually
	for each (PuzzlePiece^ currentPiece in this->Game->getPieceList()) {
		Xcoords = gcnew List<int>();
		Ycoords = gcnew List<int>();
		
		// for each puzzle piece, find location coordinates 20 times
		for (int i = 0; i < 20; i++) 
		{
			capture.read(camera_feed);

			cvtColor(camera_feed, HSV_image, CV_BGR2HSV);

			// track for calibration
			TrackedPiece tmp = puzzlePieceToTrackedPiece(currentPiece);
			List<int>^ tmpList = findPieceLocation(tmp, camera_feed, HSV_image, threshold_image);
			if (tmpList->Count == 2) {
				Xcoords->Add(tmpList[0]);
				Ycoords->Add(tmpList[1]);
			}
			
			// show updated windows
			imshow(systemStringToStdString(filtered_window), threshold_image);
			imshow(systemStringToStdString(original_window), camera_feed);

			waitKey(30);
		}
		// average those coordinates
		// if no coordinates were found, will return (0,0)
		if (Xcoords->Count !=0 && Ycoords->Count != 0) {
			double x = averageListOfInts(Xcoords);
			double y = averageListOfInts(Ycoords);
			// now set the X and Y destinations of that piece using these averaged coordinates
			currentPiece->setDestPos(x,y);
		}
		else {
			currentPiece->setDestPos(0,0);
		}
	}

	// release unmanaged components (I'm not sure if this actually works)
	cv::destroyAllWindows();
	endTrack();
	camera_feed.release();
	HSV_image.release();
	threshold_image.release();
	capture.release();

	return 0;
}


////----------------------------------------------------------------------------------------------------------

int CalibrationTracking::startTrackColor()
{

	VideoCapture capture;
	capture.open(0);	//0 is default video device, 1 is other/USB camera
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
	
	TrackedPiece tmp = puzzlePieceToTrackedPiece(this->Game->getPieceList()[this->iterator]);
	createTrackbarWindow(tmp);

	cv::Mat board = displayPuzzleBoard();

	namedWindow("game_board", WINDOW_NORMAL);
	imshow("game_board", board);
	// Move puzzle board window to correct position on game board monitor
	// (Puzzle board monitor needs to be set up to the left of first monitor.)
	moveWindow("game_board", -1600, 0);
	cvSetWindowProperty("game_board", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);	// Makes full screen

	this->iterator = 0;

	//// set up filtered and original windows
	std::string originalwindow = systemStringToStdString(original_window);
	std::string filteredwindow = systemStringToStdString(filtered_window);
	namedWindow(originalwindow);
	moveWindow(originalwindow, 640, 0);
	namedWindow(filteredwindow);
	moveWindow(filteredwindow, 640, 512);

	while(1)
	{
		capture.read(camera_feed);

		cvtColor(camera_feed, HSV_image, CV_BGR2HSV);

		// track for calibration
		TrackedPiece tmp = TrackedPiece(systemStringToStdString(this->Game->getPieceList()[this->iterator]->getName()), Scalar(calibrate_H_min, calibrate_S_min, calibrate_V_min), Scalar(calibrate_H_max, calibrate_S_max, calibrate_V_max));
		trackTrackedPiece(tmp, camera_feed, HSV_image, threshold_image);
		imshow(systemStringToStdString(filtered_window), threshold_image);
		
		imshow(systemStringToStdString(original_window), camera_feed);

		waitKey(30);
		if (STOP) {
			savePieceInformation();
			endTrack();
			cv::destroyAllWindows();
			camera_feed.release();
			HSV_image.release();
			threshold_image.release();
			capture.release();
			break;
		}
		if (NEXT) {
			savePieceInformation();
			nextPiece();
		}
	}
	cv::destroyAllWindows();
	camera_feed.release();
	HSV_image.release();
	threshold_image.release();
	capture.release();
	return 0;
}



