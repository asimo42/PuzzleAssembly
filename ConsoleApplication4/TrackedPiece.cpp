
#include "stdafx.h"
#include <Windows.h>
#include "TrackedPiece.h"
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <algorithm>
#include "Shape.h"
#include <cmath>

using namespace std;

TrackedPiece::TrackedPiece(void)
{
	setName("N/A");
	setHSVmin(Scalar(0,0,0));
	setHSVmax(Scalar(0,0,0));
	isMoving = false;
	timeLock = false;
}


TrackedPiece::~TrackedPiece(void)
{
}


TrackedPiece::TrackedPiece(std::string piece_name)
{
	setName(piece_name);
	isMoving = false;
	timeLock = false;
}

TrackedPiece::TrackedPiece(std::string piece_name, Scalar HSVmin, Scalar HSVmax)
{
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
	isMoving = false;
	timeLock = false;
}

TrackedPiece::TrackedPiece(std::string piece_name, Scalar HSVmin, Scalar HSVmax, int xdest, int ydest)
{
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
	setXDest(xdest);
	setYDest(ydest);
	isMoving = false;
	timeLock = false;
}

int TrackedPiece::checkForMovement(bool justMoved)
{
	//Return value tells what all the other pieces should be set to do
	//
	//  0 - Do nothing
	//  1 - Turn On
	//  2 - Dim
	//  3 - Turn off


	// add to movement history
	movementHistory.push_back(justMoved);
	// check if max size reached
	if(movementHistory.size() > MAX_DEQUE_SIZE)
		movementHistory.pop_front();

	// check for consistent movement
	int numTrues = count(movementHistory.begin(), movementHistory.end(), true);
	//cout << "Num trues " << name << ": " << numTrues << endl;

	if (numTrues >= 4  )//&& EASY)
	{
		//clearStatus();
		cout << name << " **TURN OFF**" << endl;
		flashing = true;
		return 3;
	}
	else if (numTrues >= 3 )//&& (EASY || MEDIUM))
	{
		//clearStatus();
		cout << name << " **DIM**" << endl;
		flashing = true;
		return 2;
	}
	else if(numTrues >= 2 )
	{
		//clearStatus();
		cout << name << " piece being placed." << endl;
		flashing = true;	// starts flashing
		return 1;
	}
	else
	{
		flashing = false;	// stops flashing
		return 0;
	}

}

bool TrackedPiece::checkIfPlacedCorrectly()
{
	if (abs(x_dest-x_pos) < PLACED_THRESH && abs(y_dest-y_pos) < PLACED_THRESH)
		placementHistory.push_back(true);
	else
		placementHistory.push_back(false);

	// check if max size reached
	if(placementHistory.size() > MAX_PLACEMENT_DEQUE_SIZE)
		placementHistory.pop_front();

	// check for consistent placement in correct position
	int numTrues = count(placementHistory.begin(), placementHistory.end(), true);
	if (numTrues >= 5) {
		isPlacedCorrectly = true;
		cout << name << " placed correctly!" << endl;
		return true;
	} else {
		isPlacedCorrectly = false;
		return false;
	}
	// else placed correctly = false?
	// Once it has been  placed, do we want it to be able to be unplaced?
}

void TrackedPiece::toggle(Mat &image)
{
	Shape shapes(&image);
	if(isOn())
	{
		// turn off
		shapes.Draw_Shape(*this, 0);
		on = false;
	}
	else
	{
		// turn on
		shapes.Draw_Shape(*this, 1);
		on = true;
	}
	imshow("Puzzle Board Window", image);
}

void TrackedPiece::turnOff(Mat &image)
{
	Shape shapes(&image);
	shapes.Draw_Shape(*this, 0);
	on = false;
	imshow("Puzzle Board Window", image);
}

void TrackedPiece::turnOn(Mat &image)
{
	Shape shapes(&image);
	if(!isOn())
	{
		shapes.Draw_Shape(*this, 1);
		on = true;
	}
	imshow("Puzzle Board Window", image);
}

void TrackedPiece::dim(Mat &image)
{
	Shape shapes(&image);
	shapes.Draw_Shape(*this, 0.35);
	on = false;
	imshow("Puzzle Board Window", image);
}

void TrackedPiece::clearStatus()
{
	turn_off = false;
	dimmed = false;
	flashing = false;
}

	//Set Shape Drawing Data
void TrackedPiece::setShapeHeight(int h) { 
		if (this->getName() == "Rectangle") { this->shape_height = h; }
		else { System::Console::WriteLine("Error: TrackedPiece.cpp - Tried to set a height for a non-rectangle"); }
	}
void TrackedPiece::setShapeWidth(int w) { 
		if (this->getName() == "Rectangle" || this->getName() == "Square") { this->shape_width = w; }
		else { System::Console::WriteLine("Error: TrackedPiece.cpp - Tried to set a width for something other than a rectangle or square"); }
	}
void TrackedPiece::setShapeLength(int l) {  
		if (this->getName() == "Triangle" || this->getName() == "Pentagon") { this->shape_length = l; }
		else { System::Console::WriteLine("Error: TrackedPiece.cpp - Tried to set a length for something other than a triangle or pentagon"); }
	}
void TrackedPiece::setShapeRadius(int r) { 
		if (this->getName() == "Circle") { this->shape_radius = r; }
		else { System::Console::WriteLine("Error: TrackedPiece.cpp - Tried to set a radius for a non-circle"); }
	}