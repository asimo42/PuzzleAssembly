#pragma once

#using <System.dll>
#include <Windows.h>

using namespace System;
using namespace System::Collections::Generic;

public ref class PuzzlePiece
{
private:

	HANDLE myMutex;
	int x_pos, y_pos;
	int x_dest, y_dest;
	List<int>^ HSV_min;
	List<int>^ HSV_max;

	// shape drawing data (add as necessary)
	int shape_point_x; 
	int shape_point_y;
	int shape_width;
	int shape_height;
	int shape_length;
	int shape_radius;

	void Initialize();

public:

	DateTime timePlaced;
	System::String^ name;

	PuzzlePiece(void);
	PuzzlePiece(System::String^ piece_name);
	PuzzlePiece(System::String^ piece_name, List<int>^ HSVmin, List<int>^ HSVmax);
	PuzzlePiece(System::String^ piece_name, List<int>^ HSVmin, List<int>^ HSVmax, int xdest, int ydest);

	~PuzzlePiece(void);

	// Get and Set Timing/Gameplay Data

	void setTimePlacedToNow();
	DateTime getTimePlaced() { return timePlaced; }


	// Get and Set Tracking Data

	int getXPos()        {return x_pos;}
	int getXDest()       { return x_dest;}
	void setXPos(int x)  {x_pos = x;}
	void setXDest(int x) {x_dest = x;}

	int getYPos()        {return y_pos;}
	int getYDest()    { return y_dest;}
	void setYPos(int y)  {y_pos = y;}
	void setYDest(int y) {y_dest = y;}

	void setPos(int x, int y)     { x_pos = x; y_pos = y; }
	void setDestPos(int x, int y) { x_dest = x; y_dest = y; }

	List<int>^ getHSVmin()         {return HSV_min;}
	void setHSVmin(List<int>^ min) {HSV_min = min;}

	List<int>^ getHSVmax()         {return HSV_max;}
	void setHSVmax(List<int>^ max) {HSV_max = max;}

	System::String^ getName()       {return name;}
	void setName(System::String^ t) {name = t;}

	// Get and Set Shape Drawing Data

	void setShapePoint(int x, int y) { shape_point_x = x; shape_point_y = y; }
	int getShapePointX()   { return shape_point_x; }
	int getShapePointY()   { return shape_point_y; }
	 
	void setShapeHeight(int h);
	void setShapeWidth(int w);
	void setShapeLength(int l);
	void setShapeRadius(int r);
	int getShapeHeight() { return shape_height; }
	int getShapeWidth()  { return shape_width;  }
	int getShapeLength() { return shape_length; }
	int getShapeRadius() { return shape_radius; }
};

