#include "stdafx.h"
#include "TrackedPiece.h"
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>

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