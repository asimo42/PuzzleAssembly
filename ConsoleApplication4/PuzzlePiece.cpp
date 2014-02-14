#include "stdafx.h"

#include <Windows.h>
#include "PuzzlePiece.h"


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
	timePlaced = 0;
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