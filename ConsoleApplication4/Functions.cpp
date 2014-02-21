#include "stdafx.h"

#include "Functions.h"
#include "RunTracking.h"


using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace cv;

//----------------------------------------------------------------------------------------------------------

// Start tracking via a RunTracking instance. Currently only designed for a KnobPuzzle game
void initializeTracking(KnobPuzzle^ %Game, ScoreKeeping^ %ScoreKeeper)
{
	// Initialize OpenCV running class (RunTracking) and load with handlevars class and puzzle
    RunTracking* newOpenCV = new RunTracking();
    newOpenCV->setGame(Game);
    newOpenCV->Start();

    // Once game is over, pull the game results and add them to the over-arching ScoreKeeper class instance for record-keeping
    MessageBox::Show("Got out of RunTracking");
	GamePlayed^ gameResults = newOpenCV->returnScore();

	// add game results to main scorekeeper instance. Show game results.
	ScoreKeeper->AddNewGame(gameResults);
	System::String^ results = gameResults->printData();	
	MessageBox::Show(results);

	return;
}
//----------------------------------------------------------------------------------------------------------

// match the game code to the type (as a string). Simple matching; game code should always have game type in it
System::String^ searchPuzzleType(System::String^ code)
{
	System::String^ type = "";
	// Here I would search some database/list sort of thing for the type of puzzle. Or it starts the code.  Ex.
	if (code->Contains("KNOBPUZZLE")) {
		type = gcnew System::String("KnobPuzzle");
	}
	if (code->Contains("BLOCKPUZZLE")) {
		type = gcnew System::String("BlockPuzzle");
	}
	if (code->Contains("SNAKE")) {
		type = gcnew System::String("Snake");
	}
	return type;
}


//----------------------------------------------------------------------------------------------------------
// chunk together calibrated input path or default input path
System::String^ getCalibratedInputPath(System::String^ code) { 
				System::String^ str = Constants::GAME_INPUT_DIRECTORY + code + ".txt"; 
				return str; }
System::String^ getDefaultInputPath(System::String^ code) { 
				System::String^ str = Constants::GAME_INPUT_DIRECTORY + code + "_Default" + ".txt"; 
				return str; }
//----------------------------------------------------------------------------------------------------------

// Pull all strings from a file into an array of System::Strings^
array<System::String^>^ getStringArrayFromFile(System::String^ inputFile) {

	array<System::String^>^ lines;
	if (System::IO::File::Exists(inputFile)) { System::Windows::Forms::MessageBox::Show("getStringArrayFromFile: FOUND INPUT FILE"); }
	else {
		lines[0] = gcnew System::String("ERROR");
		return lines;
	}
	// Read in all lines of file into an array 'lines'
	try {
		lines = System::IO::File::ReadAllLines(inputFile);
		System::Windows::Forms::MessageBox::Show("getStringArrayFromFile(): Reading in input file"); 
	}
	// return error if there's a problem
	catch (System::Exception^ e) {
		//System::Diagnostics::Debug::WriteLine(e);
		//lines = gcnew array<System::String^>(1);
		//System::Windows::Forms::MessageBox::Show("Error - can't read file");
		//lines[0] = gcnew System::String("ERROR");

		// for now, we will just hardcode a fake file so we don't get screwed over. CHANGE THIS LATER
		// we aren't actually technically using these values yet anyway
		List<System::String^>^ tmpList = gcnew List<System::String^>();
		tmpList->Add( "KNOBPUZZLE1");
		tmpList->Add( "NO.PIECES 5"); 
		tmpList->Add( "LOC 1 1 COLOR 165 107 25 185 233 256 Circle" );
		tmpList->Add( "LOC 2 2 COLOR 65 23 200 200 200 255 Rectangle" );
		tmpList->Add( "LOC 3 4 COLOR 10 10 10 100 100 100 Square" );
		tmpList->Add( "LOC 5 3 COLOR 90 55 100 100 100 150 Star" );
		tmpList->Add( "LOC 6 7 COLOR 18 130 75 30 256 256 Pentagon" );
		tmpList->Add( "----------------------------------------------------------------");
		tmpList->Add( "** note: LOC xloc yloc COLOR Hmin Smin Vmin Hmax Smax Vmax name");
		lines = gcnew array<System::String^>(tmpList->Count);
		for (int i = 0; i < tmpList->Count; i++) {
			lines[i] = tmpList[i];
		}
		return lines; 
	}
	return lines;
}
//----------------------------------------------------------------------------------------------------------
// write an array of strings to a file **** Currently file is harcoded here - pass as argument in future.
int writeStringArrayToFile(array<System::String^>^ inputArray, System::String^ fileName) {

    // This text is added only once to the file. 
    try 
    {
         System::IO::File::WriteAllLines(fileName, inputArray);
    }
	catch (System::Exception^ e)
	{
		System::Diagnostics::Debug::WriteLine(e);
		//System::Windows::Forms::MessageBox::Show("Error - can't write to file");
		Console::WriteLine("Error - can't write to file:");
		Console::WriteLine(e);
		return -1;
	}

	//System::String^ appendText = "This is extra text";
 //   System::IO::File::AppendAllText(path, appendText);

    // Open the file to read from. 
    array<System::String^>^ lines = System::IO::File::ReadAllLines(fileName);
    for each (System::String^ s in lines)
    {
        Console::WriteLine(s);
    }

	return 0;
}



//----------------------------------------------------------------------------------------------------------
// find the index of the start of the actual puzzle info in the game file strings
// by searching for the code string; this is always at the start of the puzzle info.
int getCodeLocation(array<System::String^>^ lines, System::String^ code)
{
	int index = -1;
	// find location of start of puzzle info
	for each (System::String^ line in lines) {
		if(line->Contains(code)) {
			index = System::Array::IndexOf(lines, line);
			return index;
		}
	}
	// if never found, return error.
	if (index == -1) {
		System::Windows::Forms::MessageBox::Show("Error - cannot find puzzle");
	}
	return -1;

}
//----------------------------------------------------------------------------------------------------------
// convert an integer into a std::string
std::string intToStdString(int number){
	std::stringstream ss;
	ss << number;
	return ss.str();
}
//----------------------------------------------------------------------------------------------------------

// convert std::string to System::String^
System::String^ stdStringToSystemString(std::string str) {
	System::String^ MyString = gcnew System::String(str.c_str());
	return MyString;
}
//----------------------------------------------------------------------------------------------------------

// convert System::String^ to std::string
std::string systemStringToStdString(System::String^ str)
{
	if (str->Equals("")) {
		return "";
	}
     using System::Runtime::InteropServices::Marshal;
     System::IntPtr pointer = Marshal::StringToHGlobalAnsi(str);
     char* charPointer = reinterpret_cast<char*>(pointer.ToPointer());
     std::string returnString(charPointer, str->Length);
     Marshal::FreeHGlobal(pointer);
     return returnString;
}

//----------------------------------------------------------------------------------------------------------
double averageListOfInts(List<int>^ inputList) {
	double sum = 0;
	for each (int num in inputList) {
		sum += num;
	}
	if (inputList->Count != 0) {	
		double average = sum/inputList->Count;
		return average;
	}
	else { return 0; }
}
//----------------------------------------------------------------------------------------------------------
//bool checkBools(bool val, ...) {
//	bool result = true;
//    int i = val;
//    va_list marker;
//
//    va_start( marker, val );
//    while( i != -1 )
//    { 
//	   if (!i) { result = false; }
//       i = va_arg( marker, int);
//    }
//    va_end( marker );
//
//	return result;
//}

//----------------------------------------------------------------------------------------------------------
// convert a cv::scalar into a list of 3 ints (for use in managed code)
List<int>^ scalarToList(cv::Scalar scalar) {
	List<int>^ myList = gcnew List<int>(0);
	myList->Add(scalar[0]); myList->Add(scalar[1]); myList->Add(scalar[2]);
	return myList;
}
//----------------------------------------------------------------------------------------------------------

// get elapsed seconds from a start time based on number of DateTime ticks
double getElapsedSeconds(long startTime) {
	DateTime tim = DateTime::Now;
	long placeTime = tim.Ticks - startTime; // 10,000 ticks in a millisecond, 1000 milliseconds in a second
	TimeSpan^ elapsed = gcnew TimeSpan(placeTime);
	return elapsed->TotalSeconds;
}
//----------------------------------------------------------------------------------------------------------
// Convert a managed PuzzlePiece to an unmanaged TrackedPiece
TrackedPiece puzzlePieceToTrackedPiece(PuzzlePiece^ puzzlePiece) {
	// pull name
	System::String^ name = puzzlePiece->getName();
	// Puzzle piece HSV lists go [H, S, V]
	int H_min = puzzlePiece->getHSVmin()[0];
	int H_max = puzzlePiece->getHSVmax()[0];
	int S_min = puzzlePiece->getHSVmin()[1];
	int S_max = puzzlePiece->getHSVmax()[1];
	int V_min = puzzlePiece->getHSVmin()[2];
	int V_max = puzzlePiece->getHSVmax()[2];
	// create new Tracked Piece with these results and return
	TrackedPiece result = TrackedPiece(systemStringToStdString(name), Scalar(H_min, S_min, V_min), Scalar(H_max, S_max, V_max),puzzlePiece->getXDest(),puzzlePiece->getYDest());

	return result;
}
//----------------------------------------------------------------------------------------------------------
// Convert a managed PuzzlePiece to an unmanaged TrackedPiece
PuzzlePiece^ trackedPieceToPuzzlePiece(TrackedPiece trackedPiece) {
	// pull name
	std::string name = trackedPiece.getName();
	// Tracked piece HSV scalars go [H, S, V]
	int H_min = trackedPiece.getHSVmin()[0];
	int H_max = trackedPiece.getHSVmax()[0];
	int S_min = trackedPiece.getHSVmin()[1];
	int S_max = trackedPiece.getHSVmax()[1];
	int V_min = trackedPiece.getHSVmin()[2];
	int V_max = trackedPiece.getHSVmax()[2];
	List<int>^ HSV_min;
	List<int>^ HSV_max;
	// recreate HSV list<int>^s
	HSV_min->Add(H_min); HSV_min->Add(S_min); HSV_min->Add(V_min);
	HSV_max->Add(H_max); HSV_max->Add(S_max); HSV_max->Add(V_max);
	// create new Puzzle Piece with these results and return
	PuzzlePiece^ result = gcnew PuzzlePiece(stdStringToSystemString(name), HSV_min, HSV_max, trackedPiece.getXDest(), trackedPiece.getYDest());

	return result;
}
//----------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------