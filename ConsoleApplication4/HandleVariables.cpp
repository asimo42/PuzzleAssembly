#include "stdafx.h"
#include <string>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include <Windows.h>
#include <list>
#include "HandleVariables.h"
#include "Functions.h"

using namespace System::Collections::Generic;
using namespace System;

void HandleVariables::InitializeFlags()
{
	HANDLE myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "FlagHandler");
	PAUSE_GAME = false;
	START_GAME = false;
	END_GAME = false;
	GAME_OVER = false;
	JunkLine = "THIS IS MY JUNKLINE";
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::setVTKNodeChanged(int index) {
	WaitForSingleObject(myMutex, INFINITE);
	ReleaseMutex(myMutex);
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::setPiecePlaced(System::String^ pieceName)
{
	WaitForSingleObject(myMutex, INFINITE);
	ReleaseMutex(myMutex);
}
//----------------------------------------------------------------------------------------------------------

void HandleVariables::setPiecePlaced(std::string pieceName)
{
	WaitForSingleObject(myMutex, INFINITE);
	this->PIECE_PLACED = stdStringToSystemString(pieceName);
	ReleaseMutex(myMutex);
}

//----------------------------------------------------------------------------------------------------------

void HandleVariables::setGameOver() {
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "GameOver");
	this->GAME_OVER = true;
	ReleaseMutex(myMutex);
}

//----------------------------------------------------------------------------------------------------------
void HandleVariables::resetGameOver() {
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "GameOver");
	this->GAME_OVER = false;
	ReleaseMutex(myMutex);
}
	//
//int HandleVariables::ChangeNode(int Node, double newX, double newY, double newZ) 
//{
//	//create mutex lock
//	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "ChangeNode");
//	WaitForSingleObject(myMutex, INFINITE);
//	// check for index of node
//	int index = FindIndexOfNode(Node);
//	// change node
//	this->OldX = this->XArray[index];
//	this->OldY = this->YArray[index];
//	this->OldZ = this->ZArray[index];
//	this->XArray[index] = newX;
//	this->YArray[index] = newY;
//	this->ZArray[index] = newZ;
//	// release mutex lock
//	ReleaseMutex(myMutex);
//	System::Diagnostics::Debug::WriteLine("HEY YOU CHANGED A NODE:)");
//	return index;
//}
