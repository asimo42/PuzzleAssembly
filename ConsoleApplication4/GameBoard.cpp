#include "stdafx.h"

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
		System::Windows::Forms::MessageBox::Show("KnobPuzzle::SetGame - Couldn't initialize game. Check code and/or game file.");
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
	// find path for input file from game code
	System::String^ inputFile = getCalibratedInputPath(code);
	System::String^ tmp = "LookUpGame: Calibrated Input File Path : " + inputFile;
	System::Windows::Forms::MessageBox::Show(tmp);
	if (!System::IO::File::Exists(inputFile)) {
		// if can't find calibrated file, then use default file instead
		inputFile = getDefaultInputPath(code);
		// if neither exist, error and exit.
		if (!System::IO::File::Exists(inputFile)) {
			Console::WriteLine("KnobPuzzle::LookUpGame - Could not find game file");
			this->Error = true;
			return;
		}
	}

	// pull all strings from file
	array<System::String^>^ stringArray = getStringArrayFromFile(inputFile);
	if (stringArray[0]->Equals("ERROR")) {
		System::Windows::Forms::MessageBox::Show("KnobPuzzle::LookUpGame -Could not load game file");
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
	int x, y, hmin, smin, vmin, hmax, smax, vmax;
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
		if (tokens[0]->Equals("LOC") && tokens[3]->Equals("COLOR") && tokens->Length >= 11 ) {
			//Sample Format:::    LOC 1 1 COLOR 100 100 150 200 200 200 SQUARE
			bool try1 = Int32::TryParse(tokens[1], x);
			bool try2 = Int32::TryParse(tokens[2], y);
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
			int success = ParseShapeInformation(tokens, newPiece);
			if (success != 0) { 
				System::Windows::Forms::MessageBox::Show("Error: Incorrect shape drawing information");
				this->Error = true;
			}
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

//----------------------------------------------------------------------------------------------------------
// pull shape-drawing information from puzzle file line
int KnobPuzzle::ParseShapeInformation(array<System::String^>^ tokens, PuzzlePiece^ piece) 
{
	int success = 0;
	// NOTE - NEEd to return error values when trying to set shapes
	System::String^ shapeType = piece->getName();
	int point_x, point_y, height, width, length, radius;
	bool try1 = true; bool try2 = true; bool try3 = true; bool try4 = true;
	if (shapeType->Equals("Circle")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		piece->setShapePoint(point_x, point_y);
		bool try3 = Int32::TryParse(tokens[13], radius);
		piece->setShapeRadius(radius);
	}
	if (shapeType->Equals("Rectangle")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		piece->setShapePoint(point_x, point_y);
		bool try3 = Int32::TryParse(tokens[13], width);
		bool try4 = Int32::TryParse(tokens[14], height);
		piece->setShapeHeight(height);
		piece->setShapeWidth(width);
	}
	if (shapeType->Equals("Square")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		piece->setShapePoint(point_x, point_y);
		bool try3 = Int32::TryParse(tokens[13], width);
		piece->setShapeWidth(width);
	}
	if (shapeType->Equals("Triangle") || shapeType->Equals("Pentagon")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		piece->setShapePoint(point_x, point_y);
		bool try4 = Int32::TryParse(tokens[13], length);
		piece->setShapeLength(length);
	}
	if (!try1 || !try2 || !try3 ||!try4) { success = -1; }
	return success;
}
//----------------------------------------------------------------------------------------------------------
// Write the current KnobPuzzle calibration settings to the calibration file. 
int KnobPuzzle::WriteSettingsToFile() {
	System::Diagnostics::Debug::WriteLine("Saving calibration settings to file");
	int success = 0;


	// Find default code file to use as template for changes
	System::String^ inputFile = getDefaultInputPath(this->getName());
	if (!System::IO::File::Exists(inputFile)) {
		System::Windows::Forms::MessageBox::Show("Warning - can't find default input file.");
		inputFile = getCalibratedInputPath(this->getName());
		if (!System::IO::File::Exists(inputFile)) {
			System::Windows::Forms::MessageBox::Show("WriteSettingsToFile(): Could not find original game file");
			this->Error = true;
			return -1;
		}
	}

	// pull in all strings from code file to serve as template for changes
	array<System::String^>^ stringArray = getStringArrayFromFile(inputFile);
	if (stringArray[0]->Equals("ERROR")) {
		System::Windows::Forms::MessageBox::Show("Could not load game file");
		this->Error = true;
		return -1;
	}
		// get starting location of code segment
	int startIndex = getCodeLocation(stringArray, this->puzzleName);
	if (startIndex < 0 || startIndex > stringArray->Length) {
		System::Windows::Forms::MessageBox::Show("Could not find game code in game file");
		this->Error = true;
		return -1;
	}

	// get ending location of code segment
	System::String^ line = stringArray[startIndex];
	int endIndex = startIndex;
	while(!line->Contains("----") && endIndex < stringArray->Length)
	{
		line = stringArray[endIndex++];
	}
	//System::String^ tmp = "Beginning index: " + startIndex + "   End index: " + endIndex;
	//System::Windows::Forms::MessageBox::Show(tmp);

	System::Diagnostics::Debug::WriteLine("Constructing new file strings");
	int puzzlePieceIndex = 0;
	for (int i = startIndex; i < endIndex ; i++) {
		line = stringArray[i];
		//if original line does not begin with LOC , then continue to next line
		if (line->Length < 4 || !line->Substring(0,4)->Equals("LOC ")) {continue;}

		// get the relevent information from the current puzzle piece
		PuzzlePiece^ currentPiece = this->getPieceList()[puzzlePieceIndex];
		int xdest = currentPiece->getXDest();
		int ydest = currentPiece->getYDest();
		List<int>^ HSVmin = currentPiece->getHSVmin();
		List<int>^ HSVmax = currentPiece->getHSVmax();
		int shapePointX = currentPiece->getShapePointX();
		int shapePointY = currentPiece->getShapePointY();
		System::String^ name = currentPiece->getName();

		// cat puzzle piece information together into a single line in the proper format
		System::String^ constructor = "LOC " + xdest + " " + ydest + " COLOR " + HSVmin[0] + " " + HSVmin[1] + " " + HSVmax[2] 
								 + " " + HSVmax[0] + " " + HSVmax[1] + " " + HSVmax[2] + " " + name + " " + shapePointX  + " " + shapePointY;
		if (name->Equals("Circle")) {
			constructor = constructor  + " " + currentPiece->getShapeRadius();
		}
		else if (name->Equals("Square")) {
			constructor = constructor  + " " + currentPiece->getShapeWidth();
		}
		else if (name->Equals("Rectangle")) {
			constructor = constructor  + " " + currentPiece->getShapeWidth() + " " + currentPiece->getShapeHeight();
		}
		else if (name->Equals("Triangle") || name->Equals("Pentagon")) {
			constructor = constructor  + " " + currentPiece->getShapeLength();
		} 
		// copy the line over the old line in the array of file strings
		stringArray[i] = constructor;
		System::Diagnostics::Debug::WriteLine(stringArray[i]);

		// go to next puzzle piece
		puzzlePieceIndex++;
	}

	writeStringArrayToFile(stringArray, getCalibratedInputPath(this->getName()));
	//System::Diagnostics::Debug::WriteLine("NEW FILE NOWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW");
	//// print out whole string array to check
	//for (int i = 0; i < stringArray->Length ; i++) {
	//	System::Diagnostics::Debug::WriteLine(stringArray[i]);

	//}

	return success;
}