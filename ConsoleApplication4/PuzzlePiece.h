#pragma once
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>

using namespace System;
//using namespace cv;
using namespace System::Collections::Generic;

ref class PuzzlePiece
{
private:

	HANDLE myMutex;
	System::String^ name;
	int x_pos, y_pos;
	double x_dest, y_dest;
	List<int>^ HSV_min;
	List<int>^ HSV_max;

public:

	PuzzlePiece(void);

	PuzzlePiece(System::String^);
	PuzzlePiece(System::String^, List<int>^, List<int>^ Scalar);

	~PuzzlePiece(void);


	int getXPos() {return x_pos;}
	double getXDestX() { return x_dest;}
	void setXPos(int x) {x_pos = x;}

	int getYPos() {return y_pos;}
	double getYDest() { return y_dest;}
	void setYPos(int y) {y_pos = y;}


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

