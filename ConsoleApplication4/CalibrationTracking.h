/* This class controls the operation of OpenCV.  It starts OpenCV running, monitors/controls tracking, gathers time data, and shuts
OpenCV down once the game is completed or stopped.  An instance of this class is created in "StartOpenCV.cpp" when the user hits
the Run button on the GUI
*/
#pragma once

#include "stdafx.h"
#include <vcclr.h>
#include <opencv2\opencv.hpp>        //includes all OpenCV headers
#include "GameBoard.h"
#include "Functions.h"

ref class CalibrationTracking
{

  public:

		bool IS_STOPPED;

		CalibrationTracking() { Initialize(); }
  
		CalibrationTracking^ returnHandle() { return this; }
        virtual void Initialize();
        virtual void Start();
		virtual void startLocationCalibration();
        virtual void Stop() { STOP = true; }
		virtual void Next() { NEXT = true; }
        virtual void setGame(KnobPuzzle^ game) {this->Game = game;}

protected:

        bool STOP;
		bool NEXT;
		int iterator;
		bool COLOR_CALIBRATION;
		bool LOCATION_CALIBRATION;
        KnobPuzzle^ Game;

		virtual int startTrackColor();
		virtual int startTrackLocation();
        virtual void endTrack();
		virtual void nextPiece();
        virtual void trackTrackedPiece(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);
        virtual List<int>^ findPieceLocation(TrackedPiece &piece, Mat &camera_feed, Mat &HSV_image, Mat &threshold_image);
        virtual List<int>^ trackFilteredObject(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image);
        //virtual List<int>^ trackFilteredObject2(TrackedPiece &piece, Mat &cameraFeed, Mat &threshold_image);
		void createTrackbarWindow(TrackedPiece &tmp);
        void erodeAndDilate(Mat &image);
        void drawObject(vector<TrackedPiece> pieces, Mat &frame);


private:

		HANDLE myMutex;

		// window names
        System::String^ original_window;
        System::String^ trackbar_window;
        System::String^ filtered_window;
        System::String^ puzzle_window;

        //default capture width and height
        int FRAME_WIDTH;
        int FRAME_HEIGHT;
        //max number of objects to be detected in frame
        int MAX_NUM_OBJECTS;
        //minimum and maximum object area
        int MIN_OBJECT_AREA;
        int MAX_OBJECT_AREA;

		// min&max calibration values
        int H_min;
        int H_max;
        int S_min;
        int S_max;
        int V_min;
        int V_max;

		// temporary calibration values
		int calibrate_H_min;
        int calibrate_H_max;
        int calibrate_S_min;
        int calibrate_S_max;
        int calibrate_V_min;
        int calibrate_V_max;

};