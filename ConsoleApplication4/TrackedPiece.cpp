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

using namespace std;

TrackedPiece::TrackedPiece(void)
{
	setName("N/A");
	setHSVmin(Scalar(0,0,0));
	setHSVmax(Scalar(0,0,0));
}


TrackedPiece::~TrackedPiece(void)
{
}


TrackedPiece::TrackedPiece(std::string piece_name)
{
	setName(piece_name);
}

TrackedPiece::TrackedPiece(std::string piece_name, Scalar HSVmin, Scalar HSVmax)
{
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
}

TrackedPiece::TrackedPiece(std::string piece_name, Scalar HSVmin, Scalar HSVmax, int xdest, int ydest)
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

	if (numTrues >= 7)
	{
		//clearStatus();
		cout << name << " **TURN OFF**" << endl;
		flashing = true;
		return 3;
	}
	else if (numTrues >= 6)
	{
		//clearStatus();
		cout << name << " **DIM**" << endl;
		flashing = true;
		return 2;
	}
	else if(numTrues >= 4 )
	{
		//clearStatus();
		cout << name << " piece being placed." << endl;
		flashing = true;	// starts flashing
		return 1;
	}
	else
	{
		clearStatus();
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

void TrackedPiece::dim(Mat &image)
{
	Shape shapes(&image);
	if(!isDimmed())
	{
		// dim
		if(name == "Circle")
		{
			shapes.setColor(Scalar(0, 0, 125));
			shapes.Draw_Circle(Point(383, 244), 125, -1);
		} 
		else if(name == "Rectangle")
		{
			shapes.setColor(Scalar(0, 125, 0));
			shapes.Draw_Rectangle(Point(483, 634), 287, 175, -1);
		}
		else if (name == "Pentagon")
		{
			shapes.setColor(Scalar(0, 125, 125));
			shapes.Draw_Pentagon(Point(1056, 585), 173, -1);
		}
		on = true;
	}
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