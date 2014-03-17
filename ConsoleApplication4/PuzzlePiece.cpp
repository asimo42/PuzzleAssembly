#include "stdafx.h"

#include "PuzzlePiece.h"


using namespace System;

PuzzlePiece::PuzzlePiece(void)
{
	Initialize();

}

void PuzzlePiece::Initialize() 
{
	setName("N/A");
	array<int>^ input = { 0,0,0 };
	List<int>^ HSVmintmp = gcnew List<int>((IEnumerable<int>^) input);
	List<int>^ HSVmaxtmp = gcnew List<int>((IEnumerable<int>^) input);
	setHSVmin(HSVmintmp);
	setHSVmax(HSVmaxtmp);
	//timePlaced = gcnew DateTime(); 
	shape_point_x = 0; 
	shape_point_y = 0;
	shape_width = 0;
	shape_height = 0;
	shape_length = 0;
	shape_radius = 0;
}

PuzzlePiece::~PuzzlePiece(void)
{
}

PuzzlePiece::PuzzlePiece(System::String^ piece_name)
{
	Initialize();
	setName(piece_name);
}

PuzzlePiece::PuzzlePiece(System::String^ piece_name, List<int>^ HSVmin, List<int>^ HSVmax)
{
	Initialize();
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
}

PuzzlePiece::PuzzlePiece(System::String^ piece_name, List<int>^ HSVmin, List<int>^ HSVmax, int xdest, int ydest)
{
	Initialize();
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
	setXDest(xdest);
	setYDest(ydest);
}

void PuzzlePiece::setTimePlacedToNow()
{
	//this->timePlaced = gcnew System::DateTime;
	this->timePlaced = this->timePlaced.Now;
}

	//Set Shape Drawing Data
void PuzzlePiece::setShapeHeight(int h) { 
		if (this->getName()->Equals("Rectangle")) { this->shape_height = h; }
		else { System::Console::WriteLine("Error: PuzzlePiece.h - Tried to set a height for a non-rectangle"); }
	}
void PuzzlePiece::setShapeWidth(int w) { 
		if (this->getName()->Equals("Rectangle") || this->getName()->Equals("Square")) { this->shape_width = w; }
		else { System::Console::WriteLine("Error: PuzzlePiece.h - Tried to set a width for something other than a rectangle or square"); }
	}
void PuzzlePiece::setShapeLength(int l) {  
		if (this->getName()->Equals("Triangle") || this->getName()->Equals("Pentagon")) { this->shape_length = l; }
		else { System::Console::WriteLine("Error: PuzzlePiece.h - Tried to set a length for something other than a triangle or pentagon"); }
	}
void PuzzlePiece::setShapeRadius(int r) { 
		if (this->getName()->Equals("Circle")) { this->shape_radius = r; }
		else { System::Console::WriteLine("Error: PuzzlePiece.h - Tried to set a radius for a non-circle"); }
	}