#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <stack>
#include <process.h>
#using <System.dll>
#include <stdio.h>
#include "GameBoard.h"
#include "PuzzlePiece.h"
#include "Functions.h"

using namespace System;
using namespace System::Collections::Generic;


KnobPuzzle::KnobPuzzle(void) 
{
	this->Started = false; this->Completed = false; this->Cancelled = false;
	this->puzzleName = gcnew System::String("KNOBPUZZLE 1");
	this->puzzleType = gcnew System::String("KNOBPUZZLE");
	this->numPieces = 0;
}
//----------------------------------------------------------------------------------------------------------
KnobPuzzle::KnobPuzzle(System::String^ code) 
{
	LookUpGame(code);
	if (this->Error) {
		return;
	}
}
//----------------------------------------------------------------------------------------------------------
KnobPuzzle::~KnobPuzzle(void) 
{
}
//----------------------------------------------------------------------------------------------------------

void KnobPuzzle::LookUpGame(System::String^ code) 
{
	// get all strings from the code file
	array<System::String^>^ stringArray = getCodeStrings(code);
	if (stringArray[0]->Equals("ERROR")) {
		System::Windows::Forms::MessageBox::Show("Could not load game file");
		this->Error = true;
		return;
	}
	// get location of our code
	int index = getCodeLocation(stringArray, code);
	if (index < 0 || index > stringArray->Length) {
		System::Windows::Forms::MessageBox::Show("Could not find game code in game file");
		this->Error = true;
		return;
	}

	List<PuzzlePiece^>^ PieceList = gcnew List<PuzzlePiece^>(0);
	System::String^ line = stringArray[index];
	array<System::String^>^ tokens;
	int no_pieces = 0;
	double x, y; 
	int hmin, smin, vmin, hmax, smax, vmax;
	List<Int32>^ HSVmin;
	List<Int32>^ HSVmax;
	// start processing our code lines
	while(!line->Contains("----") && index < stringArray->Length) {
		line = stringArray[index++];
		System::Diagnostics::Debug::WriteLine(line);
		if (line->Length == 0) {continue;}
		tokens = line->Split();
		if (tokens[0]->Equals("NO.PIECES") && tokens->Length == 2) {
			if (!Int32::TryParse(tokens[1], no_pieces)) {
				System::Windows::Forms::MessageBox::Show("Error, NO.PIECES incorrectly formatted");
				this->Error = true;
				return;
			}
		}
		if (tokens[0]->Equals("LOC") && tokens[3]->Equals("COLOR") && tokens->Length == 11 ) {
			//Sample Format:::    LOC 1 1 COLOR 100 100 150 200 200 200 SQUARE
			Double::TryParse(tokens[1], x);
			Double::TryParse(tokens[2], y);
			Int32::TryParse(tokens[4], hmin);
			Int32::TryParse(tokens[5], smin);
			Int32::TryParse(tokens[6], vmin);
			Int32::TryParse(tokens[7], hmax);
			Int32::TryParse(tokens[8], smax);
			Int32::TryParse(tokens[9], vmax);
			HSVmin = gcnew List<Int32>(3);
			HSVmax = gcnew List<Int32>(3);
			PuzzlePiece^ newPiece = gcnew PuzzlePiece(tokens[10], HSVmin, HSVmax);
			newPiece->setDestPos(x,y);
			PieceList->Add(newPiece);
		}
	}
	System::String^ testOutput = "Loaded file " + code + PieceList[3]->getYDest();
	System::Windows::Forms::MessageBox::Show(testOutput);

	// load piece data into mother class
	this->pieceList = PieceList;
	this->numPieces = no_pieces;
}