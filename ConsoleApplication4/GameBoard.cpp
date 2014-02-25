#include "stdafx.h"

#include "Functions.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

//----------------------------------------------------------------------------------------------------------
// set initial values for knob puzzle so we don't run into errors
void KnobPuzzle::Initialize() 
{
	this->Error = false;  // error boolean will be set if something goes wrong somewhere
	this->puzzleName = gcnew System::String("KNOBPUZZLE");
	this->puzzleType = gcnew System::String("KNOBPUZZLE");
	this->errorString = gcnew System::String("");
	this->pieceList = gcnew List<PuzzlePiece^>();
}

//----------------------------------------------------------------------------------------------------------
// initialize an empty knobpuzzle
KnobPuzzle::KnobPuzzle(void) 
{
	Initialize();
}

//----------------------------------------------------------------------------------------------------------
// initialize a knob puzzle to a code. It will look into the game file for the matching code
KnobPuzzle::KnobPuzzle(System::String^ code) 
{
	setGame(code);
}

int KnobPuzzle::setGame(System::String^ code) {

	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "Knobpuzzle::setGame()");

	Initialize();
	this->puzzleName = code; // update puzzle name
	LookUpGame(code); // this will fill up the knobpuzzle^ class properties

	ReleaseMutex(myMutex);

	if (this->Error) {
		MessageBox::Show("KnobPuzzle::SetGame() - Couldn't initialize game. Check code and/or game file.");
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
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "LookupGame()");

	// find path for input file from game code
	System::String^ inputFile = getCalibratedInputPath(code);
	System::String^	defaultFile = getDefaultInputPath(code);
	//System::String^ tmp = "KnobPuzzle::LookUpGame(): Calibrated Input File Path : " + inputFile + "\n Default Input File Path : " + defaultFile;
	Console::WriteLine("KnobPuzzle::LookUpGame(): Calibrated Input File Path : " + inputFile + "\n Default Input File Path : " + defaultFile);

	// if can't find calibrated file, then use default file instead
	if (!System::IO::File::Exists(inputFile)) {
		// if can't find calibrated file, then use default file instead
		Console::WriteLine("KnobPuzzle::LookUpGame() - Could not find calibrated file. Will use default instead.");
		inputFile = defaultFile;
		// if neither exist, error and exit.
		if (!System::IO::File::Exists(inputFile)) {
			Console::WriteLine("KnobPuzzle::LookUpGame() - Could not find either calibrated or default game file");
			this->Error = true;
			return;
		}
	}

	// pull all strings from file
	array<System::String^>^ stringArray = getStringArrayFromFile(inputFile);
	if (stringArray == nullptr || stringArray[0]->Equals("ERROR")) {
		MessageBox::Show("KnobPuzzle::LookUpGame -Could not pull strings from Game file");
		this->Error = true;
		return;
	}

	// Initialize containers 
	List<PuzzlePiece^>^ PieceList = gcnew List<PuzzlePiece^>(0);
	array<System::String^>^ tokens;
	int x, y, hmin, smin, vmin, hmax, smax, vmax;
	List<Int32>^ HSVmin;
	List<Int32>^ HSVmax;

	// go through each line in our section of input file. **THIS IS HARDCODED - changes to input file must be dealt with there
	int index = 0;
	System::String^ line = stringArray[index];
	Console::WriteLine("KnobPuzzle::LookUpGame() : parsing puzzle pieces from input file");
	while(!line->Contains("----") && index < stringArray->Length) {
		line = stringArray[index++]; 
		Console::WriteLine(line);
		if (line->Length == 0) {continue;} // if line empty, continue
		tokens = line->Split(); // break line into words

		// Pull PuzzlePiece^ tracking information 
		if (tokens[0]->Equals("LOC") && tokens[3]->Equals("COLOR") && tokens->Length >= 11 ) {
			//Sample Format:::    LOC 1 1 COLOR 100 100 150 200 200 200 SQUARE
			System::String^ pieceName = tokens[10];
			bool try1 = Int32::TryParse(tokens[1], x);
			bool try2 = Int32::TryParse(tokens[2], y);
			bool try3 = Int32::TryParse(tokens[4], hmin);
			bool try4 = Int32::TryParse(tokens[5], smin);
			bool try5 = Int32::TryParse(tokens[6], vmin);
			bool try6 = Int32::TryParse(tokens[7], hmax);
			bool try7 = Int32::TryParse(tokens[8], smax);
			bool try8 = Int32::TryParse(tokens[9], vmax);
			// check if the parsing worked
			if (!try1 || !try2 || !try3 || !try4 || !try5 || !try6 || !try7 || !try8) {
				MessageBox::Show("Error: An inappropriate HSV value was found in line:\n" + line);
				this->Error = true;
				return;
			}
			// check if the HSV values seem reasonable
			if (hmin < 0 || smin < 0 || vmin < 0 || hmax > 256 || smax > 256 || vmax > 256) { 
				MessageBox::Show("Error: HSV value error - min values must be 0 or greater, max values must be between 0 and 256. \n" + line);
				this->Error = true;
				return;
			}
			// plug tracking information into new puzzle piece
			HSVmin = gcnew List<Int32>(3);
			HSVmin->Add(hmin); HSVmin->Add(smin); HSVmin->Add(vmin);
			HSVmax = gcnew List<Int32>(3);
			HSVmax->Add(hmax); HSVmax->Add(smax); HSVmax->Add(vmax);
			PuzzlePiece^ newPiece = gcnew PuzzlePiece(pieceName, HSVmin, HSVmax);
			newPiece->setDestPos(x,y);

			// now parse shape drawing information
			int success = ParseShapeInformation(tokens, newPiece);
			if (success != 0) { 
				Console::WriteLine("KnobPuzzle::LookUpGame() : Error: Incorrect shape drawing information: \n Line: " + line);
				MessageBox::Show("Error: Incorrect shape drawing information");
				this->Error = true;
				return;
			}

			// if all went well, add new piece to pieceList
			PieceList->Add(newPiece);
		}

		// if the input line was missing values, throw error
		else if (tokens[0]->Equals("LOC") && tokens[3]->Equals("COLOR") && tokens->Length < 11 ) {
			Console::WriteLine("KnobPuzzle::LookUpGame() : Error: Incomplete piece information: \n Line: " + line);
			MessageBox::Show("Error: Incomplete piece information: \n Line: " + line);
			this->Error = true;
			return;
		}
	}

	// if puzzle has 0 pieces, throw error
	if (PieceList->Count == 0) {
		Console::WriteLine("KnobPuzzle::LookUpGame() : Puzzle doesn't have pieces");
		MessageBox::Show("Error: Puzzle doesn't have pieces");
		this->Error = true;
		return;
	}

	// load piece data into mother class
	this->pieceList = PieceList;

	ReleaseMutex(myMutex);
}

//----------------------------------------------------------------------------------------------------------
// pull shape-drawing information from puzzle file line
int KnobPuzzle::ParseShapeInformation(array<System::String^>^ tokens, PuzzlePiece^ piece) 
{
	//**Need way to not repeat the bool check in each if statement
	System::String^ shapeType = piece->getName();
	int point_x, point_y, height, width, length, radius;
	bool try1 = true; bool try2 = true; bool try3 = true; bool try4 = true;

	if (shapeType->Equals("Circle")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		bool try3 = Int32::TryParse(tokens[13], radius);
		if (!try1 || !try2 || !try3 || !try4) {
			MessageBox::Show("KnobPuzzle::ParseShapeInformation(): Inappropriate shape drawing information for piece: " + piece->getName());
			this->Error = true;
			return -1;
		}
		piece->setShapePoint(point_x, point_y);
		piece->setShapeRadius(radius);
	}
	else if (shapeType->Equals("Rectangle")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		bool try3 = Int32::TryParse(tokens[13], width);
		bool try4 = Int32::TryParse(tokens[14], height);
		if (!try1 || !try2 || !try3 || !try4) {
			MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Inappropriate shape drawing information for piece: " + piece->getName());
			this->Error = true;
			return -1;
		}
		piece->setShapePoint(point_x, point_y);
		piece->setShapeHeight(height);
		piece->setShapeWidth(width);
	}
	else if (shapeType->Equals("Square")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		bool try3 = Int32::TryParse(tokens[13], width);
		if (!try1 || !try2 || !try3 || !try4) {
			MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Inappropriate shape drawing information for piece: " + piece->getName());
			this->Error = true;
			return -1;
		}
		piece->setShapePoint(point_x, point_y);
		piece->setShapeWidth(width);
	}
	else if (shapeType->Equals("Triangle") || shapeType->Equals("Pentagon")) {
		bool try1 = Int32::TryParse(tokens[11], point_x);
		bool try2 = Int32::TryParse(tokens[12], point_y);
		bool try3 = Int32::TryParse(tokens[13], length);
		if (!try1 || !try2 || !try3 || !try4) {
			MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Inappropriate shape drawing information for piece: " + piece->getName());
			this->Error = true;
			return -1;
		}
		piece->setShapePoint(point_x, point_y);
		piece->setShapeLength(length);
	}
	else {
			MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Not a recognized shape: " + piece->getName());
			this->Error = true;
			return -1;
		}
	if (!try1 || !try2 || !try3 ||!try4) { return -1; }

	return 0;
}
//----------------------------------------------------------------------------------------------------------// 
// user saves calibration settings
int KnobPuzzle::SaveCalibrationSettings() { 
	int success = WriteSettingsToFile(); 
	return success;
}
//----------------------------------------------------------------------------------------------------------
// Write the current KnobPuzzle calibration settings to the calibration file. THIS FUNCTION NEEDS TO BE REVAMPED TO CONSTRUCT NEW FILES WITHOUT TEMPLATE
int KnobPuzzle::WriteSettingsToFile() {

	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "Writing settings to File");

	System::Diagnostics::Debug::WriteLine("Saving calibration settings to file");
	Console::WriteLine("KnobPuzzle::WriteSettingsToFile(): Saving calibration settings to file");
	int success = 0;

	// Find default code file to use as template for changes
	System::String^ inputFile = getDefaultInputPath(this->getName());
	// if default code file is missing, use calibrated as template instead
	if (!System::IO::File::Exists(inputFile)) {
		System::Windows::Forms::MessageBox::Show("KnobPuzzle::WriteSettingsToFile(): Warning - can't find default input file.");
		inputFile = getCalibratedInputPath(this->getName());
		if (!System::IO::File::Exists(inputFile)) {
			System::Windows::Forms::MessageBox::Show("KnobPuzzle::WriteSettingsToFile(): Could not find calibrated or default game file");
			this->Error = true;
			return -1;
		}
	}
	//*** IN FUTURE WOULD LIKE TO HAVE CODE RECONSTRUCT FILE FROM BASE UP; NOT NEED TEMPLATE. That will keep things more consistent
	// pull in all strings from code file to serve as template for changes
	array<System::String^>^ stringArray = getStringArrayFromFile(inputFile);
	if (stringArray[0]->Equals("ERROR")) {
		System::Windows::Forms::MessageBox::Show("KnobPuzzle::WriteSettingsToFile(): Could not load game file");
		this->Error = true;
		return -1;
	}
	//	// get starting location of code segment
	//int startIndex = getCodeLocation(stringArray, this->puzzleName);
	//if (startIndex < 0 || startIndex > stringArray->Length) {
	//	System::Windows::Forms::MessageBox::Show("Could not find game code in game file");
	//	this->Error = true;
	//	return -1;
	//}

	int startIndex = 0;
	// get ending location of code segment
	System::String^ line = stringArray[startIndex];
	int endIndex = startIndex;
	while(!line->Contains("----") && endIndex < stringArray->Length)
	{
		line = stringArray[endIndex++];
	}

	System::Diagnostics::Debug::WriteLine("Constructing new file strings");
	Console::WriteLine("Constructing new file strings");
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

	ReleaseMutex(myMutex);

	return success;
}

//----------------------------------------------------------------------------------------------------------
// Check if the puzzle has been initialized and has pieces. THIS NEEDS TO BE MORE COMPREHENSIVE
bool KnobPuzzle::checkIsInitialized(System::String^ code) {
	if (!this->Error && this->pieceList->Count > 0 && this->puzzleName->Equals(code)) { return true; }
	else { return false; }
}