/* This class controls the operation of OpenCV tracking.  It starts, monitors & controls tracking, gathers time data, and shuts
tracking down once the game is completed or stopped.  An instance of this class is created in initializeTracking() when the user hits
the Run button on the GUI, and it lasts the duration of a single game
*/

#include "stdafx.h"
#include <vcclr.h>
#include <opencv2\opencv.hpp>
#include "Functions.h"

class RunTracking
{

  public:

  //these classes are for communicating between openCV (unmanaged) and the rest of the program
  // gcroot appears to magically transfer my classes from managed->unmanaged without consequences. Don't ask how.
        gcroot<HandleVariables^> Vars;
        gcroot<KnobPuzzle^> Game;

		RunTracking() { };
        virtual void Initialize();
        virtual void Start();
        virtual void Stop();
        virtual void setGame(KnobPuzzle^ game) {this->Game = game;}
        gcroot<GamePlayed^> returnScore();


protected:

        bool STOP;
        // when openCV is terminated (gameover), this instance of GamePlayed will be added to the overall ScoreKeeping class for the gui
        gcroot<GamePlayed^> ScoreKeep;
        
        virtual int startTrack();
        virtual void endTrack();
        virtual void trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);
        virtual void trackFilteredObject(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image);
        void createTrackbarWindow();
        void erodeAndDilate(Mat &image);
        void drawObject(vector<TrackedPiece> pieces, Mat &frame);
        void drawPuzzleBoard(Mat &image);

		//handling placement of pieces (in progress)
		void processPlacementOfPiece(TrackedPiece trackedpiece);

		// test cases
		virtual void Test1();
		virtual void Test2();
		virtual void Test3();
		virtual void Test4();
		virtual void Test5();
		virtual void Test6();

private:
		// Puzzle pieces (these should probably live in the KnobPuzzle class)
		//TrackedPiece red_circle;
		//TrackedPiece green_rectangle;
		//TrackedPiece yellow_pentagon;

	// Making global for now, since can't get the timer callback function to work as a member function
//		vector<TrackedPiece> pieces;
		
		long StartTime;

        std::string window1;
        std::string trackbar_window;
        std::string window2;
        std::string puzzle_window;

		// hard coded test case - Change this variable in the 'initialize' function to do different test cases. 0 if  not test.
		int TestCase;

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

		// Could not get to work as member variables
//		static VOID CALLBACK RunTracking::static_timerTick(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime);
//		VOID CALLBACK RunTracking::timerTick(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime);

        RunTracking(const RunTracking&);  // Not implemented.
        void operator=(const RunTracking&);  // Not implemented.

};