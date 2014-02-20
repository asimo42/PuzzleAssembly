#include "stdafx.h"
#include "TrackedPiece.h"
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>
#include <algorithm>
#include "Shape.h"

TrackedPiece::TrackedPiece(void)
{
	setName("N/A");
	setHSVmin(Scalar(0,0,0));
	setHSVmax(Scalar(0,0,0));
}


TrackedPiece::~TrackedPiece(void)
{
}


TrackedPiece::TrackedPiece(String piece_name)
{
	setName(piece_name);
}

TrackedPiece::TrackedPiece(String piece_name, Scalar HSVmin, Scalar HSVmax)
{
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
}

TrackedPiece::TrackedPiece(String piece_name, Scalar HSVmin, Scalar HSVmax, int xdest, int ydest)
{
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
	setXDest(xdest);
	setYDest(ydest);
}

int TrackedPiece::checkForMovement(bool justMoved)
{
	//Return value tells what all the other pieces should be set to do
	//
	//  0 - Do nothing
	//  1 - Turn On
	//  2 - Turn Off


	// add to movement history
	movementHistory.push_back(justMoved);
	// check if max size reached
	if(movementHistory.size() > MAX_DEQUE_SIZE)
		movementHistory.pop_front();

	// check for consistent movement
	int numTrues = count(movementHistory.begin(), movementHistory.end(), true);
	//cout << "Num trues " << name << ": " << numTrues << endl;

	if(numTrues >= 4 )
	{
		cout << name << " piece being placed." << endl;
		flashing = true;	// starts flashing
		return 1;
	}
	else if (numTrues >= 6)
	{
		cout << name << " piece being placed." << endl;
		flashing = true;
		return 2;
	}
	else
	{
		flashing = false;	// stops flashing
		return 0;
	}

}

void TrackedPiece::toggle(Mat &image)
{
	Shape shapes(&image);
	if(isOn())
	{
		//turn off
		if(name == "Circle")
		{
			shapes.setColor(Scalar(0, 0, 0));
			shapes.Draw_Circle(Point(383, 244), 125, -1);
		} 
		else if(name == "Rectangle")
		{
			shapes.setColor(Scalar(0, 0, 0));
			shapes.Draw_Rectangle(Point(483, 634), 287, 175, -1);
		}
		else if (name == "Pentagon")
		{
			shapes.setColor(Scalar(0, 0, 0));
			shapes.Draw_Pentagon(Point(1056, 585), 173, -1);
		}
		on = false;
	}
	else
	{
		// turn on
		if(name == "Circle")
		{
			shapes.setColor(Scalar(0, 0, 255));
			shapes.Draw_Circle(Point(383, 244), 125, -1);
		} 
		else if(name == "Rectangle")
		{
			shapes.setColor(Scalar(0, 255, 0));
			shapes.Draw_Rectangle(Point(483, 634), 287, 175, -1);
		}
		else if (name == "Pentagon")
		{
			shapes.setColor(Scalar(0, 255, 255));
			shapes.Draw_Pentagon(Point(1056, 585), 173, -1);
		}
		on = true;
	}
	imshow("Puzzle Board Window", image);
}

void TrackedPiece::turnOff(Mat &image)
{
	Shape shapes(&image);
	if(isOn())
	{
		//turn off
		if(name == "Circle")
		{
			shapes.setColor(Scalar(0, 0, 0));
			shapes.Draw_Circle(Point(383, 244), 125, -1);
		} 
		else if(name == "Rectangle")
		{
			shapes.setColor(Scalar(0, 0, 0));
			shapes.Draw_Rectangle(Point(483, 634), 287, 175, -1);
		}
		else if (name == "Pentagon")
		{
			shapes.setColor(Scalar(0, 0, 0));
			shapes.Draw_Pentagon(Point(1056, 585), 173, -1);
		}
		on = false;
	}
	imshow("Puzzle Board Window", image);
}

void TrackedPiece::turnOn(Mat &image)
{
	Shape shapes(&image);
	if(!isOn())
	{
		// turn on
		if(name == "Circle")
		{
			shapes.setColor(Scalar(0, 0, 255));
			shapes.Draw_Circle(Point(383, 244), 125, -1);
		} 
		else if(name == "Rectangle")
		{
			shapes.setColor(Scalar(0, 255, 0));
			shapes.Draw_Rectangle(Point(483, 634), 287, 175, -1);
		}
		else if (name == "Pentagon")
		{
			shapes.setColor(Scalar(0, 255, 255));
			shapes.Draw_Pentagon(Point(1056, 585), 173, -1);
		}
		on = true;
	}
	imshow("Puzzle Board Window", image);
}