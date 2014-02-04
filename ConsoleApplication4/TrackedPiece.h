#pragma once
#include <string>
#include <opencv2\opencv.hpp>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>

using namespace std;
using namespace cv;

class TrackedPiece
{
private:

	HANDLE myMutex;
	std::string name;
	int x_pos, y_pos;
	int lastxPos, lastyPos;
	Scalar HSV_min, HSV_max;
	Scalar color;

	// Set to true when piece has consistently moved recently. 
	// i.e. the user has picked up and is trying to place the piece.
	bool isMoving;

public:

	TrackedPiece(void);

	TrackedPiece(std::string);
	TrackedPiece(std::string, Scalar, Scalar);

	~TrackedPiece(void);


	int getXPos() {return x_pos;}
	void setXPos(int x) {x_pos = x;}

	int getYPos() {return y_pos;}
	void setYPos(int y) {y_pos = y;}

	int setPos(int x, int y) { x_pos = x; y_pos = y; }

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
};

void on_trackbar( int, void* );
void createTrackbarWindow();
void erodeAndDilate(Mat &image);
string intToStdString(int number);
void drawObject(vector<TrackedPiece> pieces, Mat &frame);
void trackFilteredObject(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image);
void trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);
int startTrack();