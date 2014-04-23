/* Definitions for functions belonging to the KnobPuzzle and GameBase classes. Ex. initializers, loading the game, writing out 
calibration settings
*/

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
	this->LevelOfDifficulty = 0;
	this->pieceList = gcnew List<PuzzlePiece^>();
	this->myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "KnobPuzzle Class Mutex");
}

//----------------------------------------------------------------------------------------------------------
// initialize an empty knobpuzzle
KnobPuzzle::KnobPuzzle(void) 
{
	Initialize();
}

//----------------------------------------------------------------------------------------------------------
KnobPuzzle::KnobPuzzle(System::String^ code) 
{
	setGame(code);
}

// initialize a knob puzzle to a code. It will look into the game file for the matching code
int KnobPuzzle::setGame(System::String^ code) {

	// lock mutex for loading game data
	WaitForSingleObject(this->myMutex, INFINITE);
	this->Error = false; // if there was an error before, setGame might fix it

	Initialize(); // re-initialize all class data
	this->puzzleName = code; // update puzzle name
	LookUpGame(code); // this will fill up the knobpuzzle^ class properties

	// release mutex
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
	// lock down thread while looking up game - just in case we use more threading in future
	WaitForSingleObject(this->myMutex, INFINITE);

	// find path for input file from game code
	System::String^ calibratedFile = getCalibratedInputPath(code);
	System::String^	defaultFile = getDefaultInputPath(code);
	System::String^ inputFile = calibratedFile;

	Console::WriteLine("KnobPuzzle::LookUpGame(): Calibrated Input File Path : " + calibratedFile + "\n Default Input File Path : " + defaultFile);

	// if can't find calibrated file, then use default file instead
	if (!System::IO::File::Exists(calibratedFile)) {
		// if can't find calibrated file, then use default file instead
		Console::WriteLine("KnobPuzzle::LookUpGame() - Could not find calibrated file. Will use default instead.");
		inputFile = defaultFile;
		if (!System::IO::File::Exists(defaultFile)) {
			Console::WriteLine("KnobPuzzle::LookUpGame() - Could not find either calibrated or default game file");
			this->Error = true;
			ReleaseMutex(myMutex);
			return;
		}
	}

	// pull all strings from file
	array<System::String^>^ stringArray = getStringArrayFromFile(inputFile);
	if (stringArray == nullptr || stringArray[0]->Equals("ERROR")) {
		MessageBox::Show("KnobPuzzle::LookUpGame -Could not pull strings from Game file");
		this->Error = true;
		ReleaseMutex(myMutex);	
		return;
	}

	// Initialize containers 
	List<PuzzlePiece^>^ PieceList = gcnew List<PuzzlePiece^>(0);
	array<System::String^>^ tokens;
	int x, y, hmin, smin, vmin, hmax, smax, vmax;
	List<Int32>^ HSVmin;
	List<Int32>^ HSVmax;

	// go through each line in our section of input file. **THIS IS HARDCODED - changes to input file must be dealt with there
	// **NOTE** level of difficulty is not currently parsed. It's there for the future. 
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
				Console::WriteLine("KnobPuzzle::LookUpGame() : Error: An inappropriate HSV value was found in line:\n" + line);
				this->Error = true;
				ReleaseMutex(myMutex);
				return;
			}
			// check if the HSV values seem reasonable
			if (hmin < 0 || smin < 0 || vmin < 0 || hmax > 256 || smax > 256 || vmax > 256) { 
				MessageBox::Show("Error: HSV value error - min values must be 0 or greater, max values must be between 0 and 256. \n" + line);
				Console::WriteLine("KnobPuzzle::LookUpGame() : Error : HSV value - min values must be 0 or greater, max values must be between 0 and 256.\n" + line);
				this->Error = true;
				ReleaseMutex(myMutex);
				return;
			}
			// plug tracking information into new puzzle piece
			HSVmin = gcnew List<Int32>(3); // HSV min values
			HSVmin->Add(hmin); HSVmin->Add(smin); HSVmin->Add(vmin);
			HSVmax = gcnew List<Int32>(3); // HSV max values
			HSVmax->Add(hmax); HSVmax->Add(smax); HSVmax->Add(vmax);
			PuzzlePiece^ newPiece = gcnew PuzzlePiece(pieceName, HSVmin, HSVmax);
			newPiece->setDestPos(x,y);   // destination location of piece

			// now parse shape drawing information. 
			int success = ParseShapeInformation(tokens, newPiece); // this function automatically adds the shape info to the puzzle piece
			if (success != 0) { 
				Console::WriteLine("KnobPuzzle::LookUpGame() : Error: Incorrect shape drawing information: \n Line: " + line);
				MessageBox::Show("Error: Incorrect shape drawing information");
				this->Error = true;
				ReleaseMutex(myMutex);
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
			ReleaseMutex(myMutex);
			return;
		}
	}

	// if puzzle still has has 0 pieces after reading through file, throw error
	if (PieceList->Count == 0) {
		Console::WriteLine("KnobPuzzle::LookUpGame() : Puzzle doesn't have pieces");
		MessageBox::Show("Error: Puzzle doesn't have pieces");
		this->Error = true;
		ReleaseMutex(myMutex);
		return;
	}

	// load piece data into mother class if all went well
	this->pieceList = PieceList;

	ReleaseMutex(myMutex);
}

//----------------------------------------------------------------------------------------------------------
// pull shape-drawing information from puzzle file line
int KnobPuzzle::ParseShapeInformation(array<System::String^>^ tokens, PuzzlePiece^ piece) 
{
	System::String^ shapeType = piece->getName();
	int point_x, point_y, height, width, length, radius, side_length, bottom_length;
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
	else if (shapeType->Equals("Isosceles")) {
		//bool try1 = Int32::TryParse(tokens[11], point_x);
		//bool try2 = Int32::TryParse(tokens[12], point_y);
		//bool try3 = Int32::TryParse(tokens[13], side_length);
		//bool try4 = Int32::TryParse(tokens[14], bottom_length);
		//if (!try1 || !try2 || !try3 || !try4) {
		//	MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Inappropriate shape drawing information for piece: " + piece->getName());
		//	this->Error = true;
		//	return -1;
		//}
		//piece->setShapePoint(point_x, point_y);
		//piece->setShapeHeight(side_length);
		//piece->setShapeWidth(bottom_length);
	}
	else if (shapeType->Equals("House")) {
		//bool try1 = Int32::TryParse(tokens[11], point_x);
		//bool try2 = Int32::TryParse(tokens[12], point_y);
		//bool try3 = Int32::TryParse(tokens[13], side_length);
		//bool try4 = Int32::TryParse(tokens[14], bottom_length);
		//if (!try1 || !try2 || !try3 || !try4) {
		//	MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Inappropriate shape drawing information for piece: " + piece->getName());
		//	this->Error = true;
		//	return -1;
		//}
		//piece->setShapePoint(point_x, point_y);
		//piece->setShapeHeight(side_length);
		//piece->setShapeWidth(bottom_length);
	}
	else if (shapeType->Equals("Tree")) {
		// CURRENTLY THIS IS HARDCODED INTO THE SHAPE DRAWING FUNCTION
		//bool try1 = Int32::TryParse(tokens[11], point_x);
		//bool try2 = Int32::TryParse(tokens[12], point_y);
		//bool try3 = Int32::TryParse(tokens[13], radius);
		//int corner_x, corner_y;
		////piece->setShapePoint(point_x, point_y);
		//bool try1 = Int32::TryParse(tokens[11], corner_x);
		//bool try2 = Int32::TryParse(tokens[12], corner_y);
		//bool try3 = Int32::TryParse(tokens[13], width);
		//bool try4 = Int32::TryParse(tokens[14], height);
		//if (!try1 || !try2 || !try3 || !try4) {
		//	MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Inappropriate shape drawing information for piece: " + piece->getName());
		//	this->Error = true;
		//	return -1;
		//}
		//piece->setShapePoint(point_x, point_y);
		//piece->setShapeHeight(height);
		//piece->setShapeWidth(width);
	}
	else if (shapeType->Equals("Door")) {
	}
	else if (shapeType->Equals("Sun")) {
	}
	else {
			MessageBox::Show("KnobPuzzle::ParseShapeInformation():: Not a recognized shape: " + piece->getName());
			this->Error = true;
			return -1;
		}
	// if any of the above parsing failed, return an error
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

	// lock everything down to this thread
	myMutex = CreateMutex(NULL, FALSE, (LPCWSTR) "Writing settings to File");
	WaitForSingleObject(myMutex, INFINITE);

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
			ReleaseMutex(myMutex);
			return -1;
		}
	}
	//*** IN FUTURE WOULD LIKE TO HAVE CODE RECONSTRUCT FILE FROM BASE UP; NOT NEED TEMPLATE. That will keep things more consistent
	// pull in all strings from code file to serve as template for changes
	array<System::String^>^ stringArray = getStringArrayFromFile(inputFile);
	if (stringArray[0]->Equals("ERROR")) {
		System::Windows::Forms::MessageBox::Show("KnobPuzzle::WriteSettingsToFile(): Could not load game file");
		this->Error = true;
		ReleaseMutex(myMutex);
		return -1;
	}

	System::String^ line = "";

	System::Diagnostics::Debug::WriteLine("Constructing new file strings");
	Console::WriteLine("Constructing new file strings");
	int puzzlePieceIndex = 0;

	// loop through pieces and write them out
	for (int i = 0; i < stringArray->Length ; i++) {
		line = stringArray[i];
		//if original line does not begin with LOC , then continue to next line
		if (line->Length < 4 || !line->Substring(0,4)->Equals("LOC ")) {continue;}

		// get the relevent information from the current puzzle piece
		PuzzlePiece^ currentPiece = this->getPieceList()[puzzlePieceIndex];
		int xdest = currentPiece->getXDest();
		int ydest = currentPiece->getYDest();
		List<int>^ HSVmin = currentPiece->getHSVmin();
		List<int>^ HSVmax = currentPiece->getHSVmax();
		int Hmin = HSVmin[0];
		int Smin = HSVmin[1];
		int Vmin = HSVmin[2];
		int Hmax = HSVmax[0];
		int Smax = HSVmax[1];
		int Vmax = HSVmax[2];
		int shapePointX = currentPiece->getShapePointX();
		int shapePointY = currentPiece->getShapePointY();
		System::String^ name = currentPiece->getName();

		// cat puzzle piece information together into a single line in the proper format
		System::String^ constructor = "LOC " + xdest + " " + ydest + " COLOR " + Hmin + " " + Smin + " " + Vmin
								 + " " + Hmax + " " + Smax + " " + Vmax + " " + name + " " + shapePointX  + " " + shapePointY;
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
	// write out final string array to calibrated file
	writeStringArrayToFile(stringArray, getCalibratedInputPath(this->getName()));
	Console::WriteLine("GameBoard.cpp::WriteSettingsToFile() : writing new settings to file : " + getCalibratedInputPath(this->getName()));

	// unlock thread
	ReleaseMutex(myMutex);

	return success;
}

//----------------------------------------------------------------------------------------------------------
// Check if the puzzle has been initialized and has pieces and is the right game
bool KnobPuzzle::checkIsInitialized(System::String^ code) {
	// check for errors or no pieces, and make sure name matches
	if (!this->Error && this->pieceList->Count > 0 && this->puzzleName->Equals(code)) { return true; }
	else { return false; }
}
//----------------------------------------------------------------------------------------------------------
// Check if the puzzle has been initialized and has pieces, is the right game and right level
bool KnobPuzzle::checkIsInitialized(System::String^ code, int level) {
	// check for errors or no pieces, and make sure name matches
	if (!this->Error && this->pieceList->Count > 0 && this->puzzleName->Equals(code) && this->getLevelOfDifficulty() == level) { return true; }
	else { return false; }
}

//----------------------------------------------------------------------------------------------------------
// Check if the puzzle has been initialized and has pieces
bool KnobPuzzle::checkIsInitialized() {
	// see if the error is set or if there is 0 pieces (bad)
	if (!this->Error && this->pieceList->Count > 0) { return true; }
	else { return false; }
}