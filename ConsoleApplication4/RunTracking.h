/* This class controls the operation of OpenCV.  It starts OpenCV running, monitors/controls tracking, gathers time data, and shuts
OpenCV down once the game is completed or stopped.  An instance of this class is created in "Functions.cpp - initializeTracking()" when the user hits
the Run button on the GUI
*/
#pragma once

#include "stdafx.h"
#include <vcclr.h>
#include <opencv2\opencv.hpp>        //includes all OpenCV headers
#include "Shape.h"

#define _CRTDBG_MAP_ALLOC

class RunTracking
{

  public:

		RunTracking() { Initialize(); }
		~RunTracking() {delete sound_player;}
  
        virtual void Initialize();
        virtual int Start();
        virtual void Stop() { STOP = true; }
        virtual void setGame(KnobPuzzle^ game) {this->Game = game; this->gameRecord->setGame(game);}
		gcroot<KnobPuzzle^> getGame() {return this->Game;}
		bool checkIfAllPiecesCorrect();
		gcroot<GamePlayed^> returnScore() { return this->gameRecord;}

		virtual void setPlayer(System::String^ name) { this->gameRecord->setPlayer(name); }
		int playSoundEffect(string filename);


protected:

		// all the game and piece information is passed in via a KnobPuzzle class instance. 
		// gcroot appears to magically transfer my classes from managed->unmanaged without consequences. Don't ask how.
        gcroot<KnobPuzzle^> Game;

        // when openCV is terminated (gameover), this instance of GamePlayed will be added to the overall scorekeeping class for the gui
        gcroot<GamePlayed^> gameRecord;

        bool STOP;
		Shape shapes;
        
        virtual int startTrack();
        virtual void endTrack();
        virtual void trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);
        virtual void trackFilteredObject(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image);
        void createTrackbarWindow();
		void createTrackbarWindow(TrackedPiece &tmp);
        void erodeAndDilate(Mat &image);
        void drawObject(vector<TrackedPiece> pieces, Mat &frame);
        void drawPuzzleBoard(Mat &image);

		int loadTrackedPieces();

		//handling placement of pieces
		void processPlacementOfPiece(TrackedPiece trackedpiece);

		//// test cases
		//virtual void Test1();
		//virtual void Test2();
		//virtual void Test3();
		//virtual void Test4();
		//virtual void Test5();
		//virtual void Test6();

private:

		// Making global for now, since can't get the timer callback function to work as a member function
		//vector<TrackedPiece> pieces;
		
		long StartTime;

        std::string original_window;
        std::string trackbar_window;
        std::string filtered_window;
        std::string puzzle_window;

		// hard coded test case. 0 = not a test
		//int TestCase;

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
		//static VOID CALLBACK RunTracking::static_timerTick(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime);
		//VOID CALLBACK RunTracking::timerTick(  _In_  HWND hwnd, _In_  UINT uMsg, _In_  UINT_PTR idEvent, _In_  DWORD dwTime);

        RunTracking(const RunTracking&);  // Not implemented.
        void operator=(const RunTracking&);  // Not implemented.

		// Used to play sounds.
		SoundEffectPlayer* sound_player;

		// sound filenames
		string sound_piece_placed1;
		string sound_game_start;
		string sound_game_completed;

};