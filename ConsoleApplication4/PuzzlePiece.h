#pragma once

#using <System.dll>
#include <Windows.h>

using namespace System;
using namespace System::Collections::Generic;

ref class PuzzlePiece
{
private:

	HANDLE myMutex;
	int x_pos, y_pos;
	double x_dest, y_dest;
	List<int>^ HSV_min;
	List<int>^ HSV_max;

	void Initialize();

public:

	int timePlaced;
	System::String^ name;

	PuzzlePiece(void);
	PuzzlePiece(System::String^ piece_name);
	PuzzlePiece(System::String^ piece_name, List<int>^ HSVmin, List<int>^ HSVmax);
	PuzzlePiece(System::String^ piece_name, List<int>^ HSVmin, List<int>^ HSVmax, int xdest, int ydest);

	~PuzzlePiece(void);

	void setTimePlaced(int tim) {timePlaced = tim;} 
	int getTimePlaced() { return timePlaced; }

	int getXPos() {return x_pos;}
	double getXDest() { return x_dest;}
	void setXPos(int x) {x_pos = x;}
	void setXDest(int x) {x_dest = x;}

	int getYPos() {return y_pos;}
	double getYDest() { return y_dest;}
	void setYPos(int y) {y_pos = y;}
	void setYDest(int y) {y_dest = y;}

	void setPos(int x, int y) { x_pos = x; y_pos = y; }
	void setDestPos(int x, int y) { x_dest = x; y_dest = y; }

	List<int>^ getHSVmin() {return HSV_min;}
	void setHSVmin(List<int>^ min) {HSV_min = min;}

	List<int>^ getHSVmax() {return HSV_max;}
	void setHSVmax(List<int>^ max) {HSV_max = max;}

	System::String^ getName(){return name;}
	void setName(System::String^ t) {name = t;}

	//List<int>^ getColor() {return color;}
	//void setColor(Scalar c) {color = c;}
};

