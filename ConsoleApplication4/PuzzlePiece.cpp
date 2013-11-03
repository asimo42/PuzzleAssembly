#include "stdafx.h"
#include "PuzzlePiece.h"
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>

PuzzlePiece::PuzzlePiece(void)
{
	setName("N/A");
	array<int>^ input = { 0,0,0 };
	List<int>^ HSVmintmp = gcnew List<int>((IEnumerable<int>^) input);
	List<int>^ HSVmaxtmp = gcnew List<int>((IEnumerable<int>^) input);
	setHSVmin(HSVmintmp);
	setHSVmax(HSVmaxtmp);

}

PuzzlePiece::~PuzzlePiece(void)
{
}

PuzzlePiece::PuzzlePiece(System::String^ piece_name)
{
	setName(piece_name);
}

PuzzlePiece::PuzzlePiece(System::String^ piece_name, List<int>^ HSVmin, List<int>^ HSVmax)
{
	setName(piece_name);
	setHSVmin(HSVmin);
	setHSVmax(HSVmax);
}