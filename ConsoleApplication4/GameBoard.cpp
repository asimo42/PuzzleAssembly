#include "stdafx.h"
#include <Windows.h>
#include <string>
#include <stdio.h>
#include "GameBoard.h"
#include "PuzzlePiece.h"
#include "Functions.h"

using namespace System;
using namespace System::Collections::Generic;

//----------------------------------------------------------------------------------------------------------
// initialize an empty knobpuzzle
KnobPuzzle::KnobPuzzle(void) 
{
	this->Error = false;
	this->puzzleName = gcnew System::String("KNOBPUZZLE");
	this->puzzleType = gcnew System::String("KNOBPUZZLE");
	List<PuzzlePiece^>^ pieceList = gcnew List<PuzzlePiece^>();
	this->numPieces = 0;
}

//----------------------------------------------------------------------------------------------------------
// initialize a knob puzzle to a code. It will look into the game file for the matching code
KnobPuzzle::KnobPuzzle(System::String^ code) 
{
	setGame(code);
}

int KnobPuzzle::setGame(System::String^ code) {
	this->Error = false;
	this->puzzleName = code;
	this->puzzleType = gcnew System::String("KNOBPUZZLE");
	List<PuzzlePiece^>^ pieceList = gcnew List<PuzzlePiece^>();
	LookUpGame(code); // this will fill up the knobpuzzle^ class properties
	if (this->Error) {
		System::Windows::Forms::MessageBox::Show("Couldn't initialize game. Check code and/or game file.");
		return -1;
	}
	return 0;
}
//----------------------------------------------------------------------------------------------------------
// I should really learn how to use destructors. I have no idea what this does.
KnobPuzzle::~KnobPuzzle(void) 
{
}
//----------------------------------------------------------------------------------------------------------
// Look in game input file for knob puzzle matching given code. Pull all game information from file.
//*** CHANGES to input file must be dealt with there ******
void KnobPuzzle::LookUpGame(System::String^ code) 
{
	// get all strings from the code file
	array<System::String^>^ stringArray = getGameFileStrings(code);
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

	// parse information and fill PuzzlePieces^. **THIS IS HARDCODED - changes to input file must be dealt with there
	List<PuzzlePiece^>^ PieceList = gcnew List<PuzzlePiece^>(0);
	System::String^ line = stringArray[index];
	array<System::String^>^ tokens;
	int no_pieces = 0;
	double x, y; 
	int hmin, smin, vmin, hmax, smax, vmax;
	List<Int32>^ HSVmin;
	List<Int32>^ HSVmax;

	// go through each line in our section of input file. 
	while(!line->Contains("----") && index < stringArray->Length) {
		line = stringArray[index++];
		System::Diagnostics::Debug::WriteLine(line);
		if (line->Length == 0) {continue;} // if line empty, continue
		tokens = line->Split();

		// Pull # of pieces
		if (tokens[0]->Equals("NO.PIECES") && tokens->Length == 2) {
			if (!Int32::TryParse(tokens[1], no_pieces)) {
				System::Windows::Forms::MessageBox::Show("Error, NO.PIECES incorrectly formatted");
				this->Error = true;
				return;
			}
		}

		// Pull PuzzlePiece^ information
		if (tokens[0]->Equals("LOC") && tokens[3]->Equals("COLOR") && tokens->Length == 11 ) {
			//Sample Format:::    LOC 1 1 COLOR 100 100 150 200 200 200 SQUARE
			bool try1 = Double::TryParse(tokens[1], x);
			bool try2 = Double::TryParse(tokens[2], y);
			bool try3 = Int32::TryParse(tokens[4], hmin);
			bool try4 = Int32::TryParse(tokens[5], smin);
			bool try5 = Int32::TryParse(tokens[6], vmin);
			bool try6 = Int32::TryParse(tokens[7], hmax);
			bool try7 = Int32::TryParse(tokens[8], smax);
			bool try8 = Int32::TryParse(tokens[9], vmax);
			if (!try1 || !try2 || !try3 || !try4 || !try5 || !try6 || !try7 || !try8) {
				System::String^ tmpString = "Error: An inappropriate HSV value was found in line:\n" + line;
				System::Windows::Forms::MessageBox::Show(tmpString);
				this->Error = true;
				return;
			}
			if (hmin < 0 || smin < 0 || vmin < 0) { 
				System::Windows::Forms::MessageBox::Show("Error: HSV value error - min values must be 0 or greater");
				this->Error = true;
				return;
			}
			if (hmax > 256 || smax > 256 || vmax > 256) {
				System::Windows::Forms::MessageBox::Show("Error: HSV value error - max values must be between 0 and 256");
				this->Error = true;
				return;
			}
			HSVmin = gcnew List<Int32>(3);
			HSVmin->Add(hmin); HSVmin->Add(smin); HSVmin->Add(vmin);
			HSVmax = gcnew List<Int32>(3);
			HSVmax->Add(hmax); HSVmax->Add(smax); HSVmax->Add(vmax);
			PuzzlePiece^ newPiece = gcnew PuzzlePiece(tokens[10], HSVmin, HSVmax);
			newPiece->setDestPos(x,y);
			PieceList->Add(newPiece);
		}
	}

	if (PieceList->Count == 0) {
		System::Windows::Forms::MessageBox::Show("Error: Puzzle doesn't have pieces");
		this->Error = true;
	}
	// load piece data into mother class
	this->pieceList = PieceList;
	this->numPieces = no_pieces;
}