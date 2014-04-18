#pragma once
#include <Windows.h>
#include <string>
#include <opencv2\opencv.hpp>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <deque>
#include <vcclr.h>


using namespace std;
using namespace cv;

class TrackedPiece
{
public: bool timeLock;
		bool isTimeLocked() { return timeLock; }
		void setTimeLock() { timeLock = true; }
private:

	HANDLE myMutex;
	std::string name;
	int x_pos, y_pos;
	int x_dest, y_dest;
	int lastxPos, lastyPos;
	Scalar HSV_min, HSV_max;
	Scalar color;

	// drawing data
	int shape_point_x; 
	int shape_point_y;
	int shape_width;
	int shape_height;
	int shape_length;
	int shape_radius;

	// Set to true when piece has consistently moved recently. 
	// i.e. the user has picked up and is trying to place the piece.
	bool isMoving;

	bool isPlacedCorrectly;

	// Set to true when piece should be flashing on screen
	bool flashing;

	// Set true when piece should be turned off.
	bool turn_off;

	bool dimmed;



	// max number of values allowed in movementHistory deque
	static const unsigned int MAX_DEQUE_SIZE = 6;
	// number of tiemr ticks that piece has been moving to trigger a flashing hint
	static const unsigned int NUM_TRUES_TRIGGER_FLASH = 2;
	// max number of values allowed in placementHistory deque
	static const unsigned int MAX_PLACEMENT_DEQUE_SIZE = 8;
	// number of timer ticks that piece was detected in the right spot to trigger that it
	// has been placed correctly
	static const unsigned int NUM_TRUES_PLACED_CORRECTLY = 3;

	static const unsigned int PLACED_THRESH = 15;

	// Holds movement history of pieces each time the timer checks for movement.
	// Holds a max of MAX_DEQUE_SIZE elements
	deque<bool> movementHistory;

	// Holds a history of if the piece is sitting in its correct x,y location on the puzzle board
	deque<bool> placementHistory;

public:
	// position of shape on screen
	int xScreenPos;
	int yScreenPos;

	// True when piece is drawn on screen, false when it is not (for flashing shape)
	bool on;

	TrackedPiece(void);

	TrackedPiece(std::string);
	TrackedPiece(std::string, Scalar, Scalar);
	TrackedPiece(std::string, Scalar, Scalar, int, int); // (name, HSVmin, HSVmac, Xdest, Ydest)

	~TrackedPiece(void);

	// Used for setting the isMoving boolean.
	// Returns true if if the piece has moved (according to movement threshold value) several
	// times in the last several timer ticks. This should tell that the user has picked up a piece
	// and is trying to place it.
	// returns false if there has not been consistent recent movement.
	int checkForMovement(bool justMoved);

	// Checks if piece has consistently been sitting in correct x,y position. If so, sets isPlacedCorrectly boolean to true.
	bool checkIfPlacedCorrectly();

	bool getIsPlacedCorrectly() {return isPlacedCorrectly;}

	void toggle(Mat &image);
	void dim(Mat &image);
	void turnOff(Mat &image);
	void turnOn(Mat &image);

	bool isFlashing() {return flashing;}
	bool isTurnedOff() {return turn_off;}
	bool isTurnedOn() {return !turn_off;}
	bool isDimmed() {return dimmed;}

	bool isOn() {return on;}

	void clearStatus();
	void setTurnOff(bool value) {turn_off = value;}
	void setDimmed(bool value) {dimmed = value;}

	int getXPos() {return x_pos;}
	void setXPos(int x) {x_pos = x;}

	int getXDest() {return x_dest;}
	void setXDest(int x) {x_dest = x;}

	int getYPos() {return y_pos;}
	void setYPos(int y) {y_pos = y;}

	int getYDest() {return y_dest;}
	void setYDest(int y) {y_dest = y;}

	int setPos(int x, int y) { x_pos = x; y_pos = y; }
	int setDest(int x, int y) { x_dest = x; y_dest = y; }

	int getLastxPos() {return lastxPos;}
	void setLastxPos(int pos) {lastxPos = pos;}

	int getLastyPos() {return lastyPos;}
	void setLastyPos(int pos) {lastyPos = pos;}

	Scalar getHSVmin() {return HSV_min;}
	void setHSVmin(Scalar min) {HSV_min = min;}

	Scalar getHSVmax() {return HSV_max;}
	void setHSVmax(Scalar max) {HSV_max = max;}

	std::string getName(){return name;}
	void setName(std::string t){name = t;}

	Scalar getColor() {return color;}
	void setColor(Scalar c) {color = c;}

	// shape drawing variables
	void setShapePoint(int x, int y) { this->shape_point_x = x; this->shape_point_y = y; }
	int getShapePointX()   { return shape_point_x; }
	int getShapePointY()   { return shape_point_y; }
	 
	void setShapeHeight(int h);
	void setShapeWidth(int w);
	void setShapeLength(int l);
	void setShapeRadius(int r);
	int getShapeHeight() { return shape_height; }
	int getShapeWidth()  { return shape_width;  }
	int getShapeLength() { return shape_length; }
	int getShapeRadius() { return shape_radius; }

};

//void on_trackbar( int, void* );
//void createTrackbarWindow();
//void erodeAndDilate(Mat &image);
//string intToStdString(int number);
//void drawObject(vector<TrackedPiece> pieces, Mat &frame);
//void trackFilteredObject(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image);
//void trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);
//int startTrack();