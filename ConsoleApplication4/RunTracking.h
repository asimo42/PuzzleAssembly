/* This class controls the operation of OpenCV.  It starts OpenCV running, monitors/controls tracking, gathers time data, and shuts
OpenCV down once the game is completed or stopped.  An instance of this class is created in "StartOpenCV.cpp" when the user hits
the Run button on the GUI
*/

#include "stdafx.h"
#include <vcclr.h>
#include <opencv2\opencv.hpp>	//includes all OpenCV headers
#include "Functions.h"
#include "HandleVariables.h"
#include "HandleVariables.h"
#include "ScoreKeeping.h"

class RunTracking
{

  public:

  //these classes are for communicating between openCV (unmanaged) and the rest of the program
  // gcroot appears to magically transfer my classes from managed->unmanaged without consequences. Don't ask how.
	gcroot<HandleVariables^> Vars;
	gcroot<KnobPuzzle^> Game;

	std::string gameName;


    RunTracking() {};
  
	virtual void Initialize();
	virtual void Start();
	virtual void Stop() { STOP = true; }
	virtual void setGame(KnobPuzzle^ game) {this->Game = game;}
	gcroot<GamePlayed^> returnScore();


protected:

	bool STOP;
	// when openCV is terminated (gameover), this instance of GamePlayed will be added to the overall ScoreKeeping class for the gui
	gcroot<GamePlayed^> ScoreKeep;
	
	virtual int startTrack();
	virtual void endTrack();
	virtual void trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);
	virtual void trackFilteredObject(TrackedPiece piece, Mat &cameraFeed, Mat &threshold_image);
	void createTrackbarWindow();
	void erodeAndDilate(Mat &image);
	void drawObject(vector<TrackedPiece> pieces, Mat &frame);

private:

	std::string window1;
	std::string trackbar_window;
	std::string window2;

	//default capture width and height
	int FRAME_WIDTH;
	int FRAME_HEIGHT;
	//max number of objects to be detected in frame
	int MAX_NUM_OBJECTS;
	//minimum and maximum object area
	int MIN_OBJECT_AREA;
	int MAX_OBJECT_AREA;

	int H_min;
	int H_max;
	int S_min;
	int S_max;
	int V_min;
	int V_max;

	RunTracking(const RunTracking&);  // Not implemented.
	void operator=(const RunTracking&);  // Not implemented.

};
