#include "stdafx.h"
#include <string>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>
#include "HandleFlags.h"
#include "Functions.h"

void HandleFlags::InitializeFlags()
{
	HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "FlagHandler");
	VTK_NODE_CHANGED = -1;
	PAUSE_GAME = false;
	START_GAME = false;
	END_GAME = false;
	JunkLine = "THIS IS MY JUNKLINE";
}
//----------------------------------------------------------------------------------------------------------

void HandleFlags::setVTKNodeChanged(int index) {
	WaitForSingleObject(myMutex, INFINITE);
	VTK_NODE_CHANGED = index;
	ReleaseMutex(myMutex);
}
//----------------------------------------------------------------------------------------------------------

void HandleFlags::setPiecePlaced(System::String^ pieceName)
{
	WaitForSingleObject(myMutex, INFINITE);
	this->PIECE_PLACED = pieceName;
	ReleaseMutex(myMutex);
}
//----------------------------------------------------------------------------------------------------------

void HandleFlags::setPiecePlaced(std::string pieceName)
{
	WaitForSingleObject(myMutex, INFINITE);
	this->PIECE_PLACED = stdStringToSystemString(pieceName);
	ReleaseMutex(myMutex);
}

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------