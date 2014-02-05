#include "stdafx.h"
#include "TrackedPiece.h"
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>
#include <algorithm>

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

bool TrackedPiece::checkForMovement(bool justMoved)
{
	// add to movement history
	movementHistory.push_back(justMoved);
	// check if max size reached
	if(movementHistory.size() > MAX_DEQUE_SIZE)
		movementHistory.pop_front();

	// check for consistent movement
	int numTrues = count(movementHistory.begin(), movementHistory.end(), true);
	//cout << "Num trues " << name << ": " << numTrues << endl;

	if(numTrues >= 6 )
	{
		cout << name << " piece being placed." << endl;
		return true;
	}
	else
		return false;

}